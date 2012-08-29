// ***************************************************************
//  HumanView   version:  1.0   Ankur Sheel  date: 2011/05/02
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "HumanView.h"
#include "DxBase.hxx"
#include "ProcessManager.hxx"
#include "BaseApp.hxx"
#include "Font.hxx"
#include "Sprite.hxx"
#include "myString.h"
#include "ScreenElement.hxx"
#include "BaseControl.hxx"
#include "MainWindow.hxx"
#include "Vector3.h"

using namespace GameBase;
using namespace Utilities;
using namespace Graphics;
using namespace Base;

// ***************************************************************
cHumanView::cHumanView()
: m_bRunFullSpeed(true)
, m_pProcessManager(NULL)
, m_pParentControl(NULL) 
{
	memset(m_bLockedKeys, 0, sizeof(m_bLockedKeys));
}

// ***************************************************************
cHumanView::~cHumanView()
{
	VOnDestroyDevice();
}

// ***************************************************************
void cHumanView::VOnCreateDevice( const HINSTANCE hInst, const HWND hWnd, 
								 int iClientWidth, int iClientHeight)
{
	m_pParentControl = IBaseControl::CreateWindowControl(WT_DESKTOP, "", true);
	m_pParentControl->VSetSize(iClientWidth, iClientHeight);
	m_pParentControl->VSetPosition(D3DXVECTOR3(0.f, 0.f, 0.f));

// 	m_pCursorSprite = ISprite::CreateSprite();
// 	m_pCursorSprite->Init(IDXBase::GetInstance()->VGetDevice(), 
// 		"Sprites\\cursor.png");
// 	m_pCursorSprite->SetSize((float)iClientWidth/30, (float)iClientHeight/30);
// 	m_pCursorSprite->SetFlags(D3DXSPRITE_ALPHABLEND);

	m_pFont = IFont::CreateMyFont();
	m_pFont->InitFont(IDXBase::GetInstance()->VGetDevice(), 14, 14, 20, false, 
		DEFAULT_CHARSET, "Arial") ;

	RECT boundingRect;
	boundingRect.left = iClientWidth/2- 75;
	boundingRect.right = boundingRect.left + 150;
	boundingRect.top  = 10;
	boundingRect.bottom = boundingRect.top + 30;
	m_pFont->SetRect(boundingRect);

	m_pFont->SetFormat(DT_LEFT | DT_TOP);
	m_pFont->SetTextColor(WHITE);
}

// ***************************************************************
void cHumanView::VOnUpdate(const int iDeltaMilliSeconds)
{
	if(m_pProcessManager)
	{
		m_pProcessManager->UpdateProcesses(iDeltaMilliSeconds);
	}
}

// ***************************************************************
void cHumanView::VOnRender(TICK tickCurrent, float fElapsedTime)
{
	HRESULT hr;
	hr = OnBeginRender(tickCurrent);
	RenderPrivate(hr);
	if (SUCCEEDED(hr))
	{
		OnEndRender(hr);
	}
}

// ***************************************************************
void cHumanView::VOnLostDevice()
{
	AppMsg appMsg;
	appMsg.m_uMsg = WM_DEVICELOST;
	appMsg.m_lParam = 0;
	appMsg.m_wParam = 0;

	if (m_pParentControl)
	{
		m_pParentControl->VPostMsg(appMsg);
	}

	for(ScreenElementList::iterator i = m_pElementList.begin(); i != m_pElementList.end(); ++i)
	{
		(*i)->VOnLostDevice();
	}
	//m_pCursorSprite->OnLostDevice();
	
	if (m_pFont)
	{
		m_pFont->VOnLostDevice();
	}
}

// ***************************************************************
HRESULT cHumanView::VOnResetDevice()
{
	LPDIRECT3DDEVICE9 pDevice = IDXBase::GetInstance()->VGetDevice();
	AppMsg appMsg;
	appMsg.m_uMsg = WM_DEVICERESET;
	appMsg.m_lParam = 0;
	appMsg.m_wParam = 0;

	if (m_pParentControl)
	{
		m_pParentControl->VPostMsg(appMsg);
	}

	HRESULT hr = S_OK;
	if (pDevice)
	{
		for(ScreenElementList::iterator i=m_pElementList.begin(); i!=m_pElementList.end(); ++i)
		{
			(*i)->VOnResetDevice();
		}
		//m_pCursorSprite->OnResetDevice();

		if (m_pFont)
		{
			m_pFont->VOnResetDevice();
		}
	}
	return hr;
}

// ***************************************************************
void cHumanView::VOnDestroyDevice()
{
	SAFE_DELETE(m_pParentControl);
	RemoveElements();

	//SAFE_DELETE(m_pCursorSprite);
}

// ***************************************************************
bool cHumanView::VOnMsgProc( const Graphics::AppMsg & msg )
{
	bool bHandled = false;
	switch(msg.m_uMsg)
	{
	case WM_CHAR:
		if (m_pParentControl)
		{
			bHandled = m_pParentControl->VPostMsg(msg);
		}
		if(!bHandled)
		{
			switch (msg.m_wParam)
			{ 
			case VK_SPACE:
				IMainWindow::GetInstance()->VToggleFullScreen();
				Log_Write_L3(ILogger::LT_DEBUG, "Toggled FullScreen");
			}
		}
		break;
	case WM_MOUSEMOVE:
	case WM_LBUTTONUP:
	case WM_LBUTTONDOWN:
	case WM_KEYUP:
	case WM_KEYDOWN:
		if (m_pParentControl)
		{
			bHandled = m_pParentControl->VPostMsg(msg);
		}
		break;
	}
	return bHandled;
}

// ***************************************************************
IGameView::GAMEVIEWTYPE cHumanView::VGetType()
{
	return GV_HUMAN;
}

// ***************************************************************
GameViewId cHumanView::VGetId() const
{
	return -1;
}

// ***************************************************************
void cHumanView::VOnAttach(GameViewId id)
{
	m_idView = id;
}

// ***************************************************************
HRESULT cHumanView::OnBeginRender(TICK tickCurrent)
{
	m_tickCurrent = tickCurrent; 

	// check if the device is available
	HRESULT hr = IDXBase::GetInstance()->VIsAvailable() ;

	if(hr == D3DERR_DEVICELOST || hr == D3DERR_DEVICENOTRESET)
	{
		HandleLostDevice(hr) ;
		return S_FALSE;
	}

	if(SUCCEEDED(hr))
	{
		// It is time to draw ? 
		if( m_bRunFullSpeed || ( (m_tickCurrent - m_tickLastDraw) > SCREEN_REFRESH_RATE) ) 
		{ 
			hr = IDXBase::GetInstance()->VBeginRender();
			if (SUCCEEDED(hr))
			{
				return hr;
			}
		}
	}
	return S_FALSE;
}

// ***************************************************************
HRESULT cHumanView::RenderPrivate( HRESULT & hr )
{
	if (FAILED(hr))
	{
		VOnResetDevice();
	}
	if(SUCCEEDED(hr))
	{
		AppMsg appMsg;
		appMsg.m_uMsg = WM_RENDER;
		appMsg.m_lParam = 0;
		appMsg.m_wParam = 0;

		if (m_pParentControl)
		{
			m_pParentControl->VPostMsg(appMsg);
		}

		AppMsg msg;
		for(ScreenElementList::iterator i=m_pElementList.begin(); i!=m_pElementList.end(); ++i)
		{
			if ((*i)->VIsVisible())
			{
				(*i)->VOnRender(msg);
			}
		}
// 		if (m_pCursorSprite->IsVisible())
// 		{
// 			m_pCursorSprite->SetPosition(D3DXVECTOR3((float)m_pInput->GetX(), (float)m_pInput->GetY(), 0.0f));
// 			m_pCursorSprite->OnRender(IDXBase::GetInstance()->VGetDevice());
// 		}
	}
	return hr;
}

// ***************************************************************
void cHumanView::OnEndRender(const HRESULT hr)
{
	m_tickLastDraw = m_tickCurrent; 

	IDXBase::GetInstance()->VEndRender(hr);
}

// ***************************************************************
void cHumanView::PushElement(shared_ptr<IScreenElement> pScreenElement)
{
	m_pElementList.push_back(pScreenElement);
}

// ***************************************************************
void cHumanView::PopElement(shared_ptr<IScreenElement> pScreenElement)
{
	m_pElementList.remove(pScreenElement);
}

// ***************************************************************
void cHumanView::RemoveElements()
{
	while (!m_pElementList.empty())
	{
		m_pElementList.pop_front();
	}
}

// ***************************************************************
// Tries to restore a lost device
// ***************************************************************
void cHumanView::HandleLostDevice(HRESULT hr)
{
	if(hr == D3DERR_DEVICELOST)
	{
		Sleep(50);
		return;
	}
	else 
	{
		if(hr == D3DERR_DEVICENOTRESET) 
		{
			VOnLostDevice();
			hr = IDXBase::GetInstance()->VOnResetDevice() ;

			VOnResetDevice();
		}
	}
}

bool cHumanView::IsKeyLocked( const DWORD dwKey )  const
{
	return m_bLockedKeys[dwKey];
}

// ***************************************************************
// Locks the key on the keyboard
// ***************************************************************
void cHumanView::LockKey( const DWORD dwKey ) 
{
	m_bLockedKeys[dwKey] = true;
}

void cHumanView::UnlockKey( const DWORD dwKey ) 
{
	m_bLockedKeys[dwKey] = false;
}

// ***************************************************************
void cHumanView::SetCursorVisible( bool bVisible )
{
// 	if (m_pCursorSprite)
// 	{
// 		m_pCursorSprite->SetVisible(bVisible);
// 	}
}
