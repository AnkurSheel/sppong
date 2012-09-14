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
#include "GraphicsClass.hxx"
#include "ProcessManager.hxx"
#include "BaseApp.hxx"
//#include "Font.hxx"
//#include "Sprite.hxx"
//#include "ScreenElement.hxx"
//#include "BaseControl.hxx"
#include "MainWindow.hxx"
#include "Vector3.h"
//#include "vertexstruct.h"
#include "Color.h"

using namespace Utilities;
using namespace Graphics;
using namespace Base;

// ***************************************************************
GameBase::cHumanView::cHumanView()
: m_bRunFullSpeed(true)
, m_pProcessManager(NULL)
//, m_pParentControl(NULL) 
{
	memset(m_bLockedKeys, 0, sizeof(m_bLockedKeys));
}

// ***************************************************************
GameBase::cHumanView::~cHumanView()
{
	VOnDestroyDevice();
}

// ***************************************************************
void GameBase::cHumanView::VOnCreateDevice(IBaseApp * pGame, const HINSTANCE hInst, const HWND hWnd, 
								 int iClientWidth, int iClientHeight)
{
	/*m_pParentControl = IBaseControl::CreateWindowControl(WT_DESKTOP, "", true);
	m_pParentControl->VSetSize(iClientWidth, iClientHeight);
	m_pParentControl->VSetPosition(cVector3(0.f, 0.f, 0.f));
*/
// 	m_pCursorSprite = ISprite::CreateSprite();
// 	m_pCursorSprite->Init(IDXBase::GetInstance()->VGetDevice(), 
// 		"Sprites\\cursor.png");
// 	m_pCursorSprite->SetSize((float)iClientWidth/30, (float)iClientHeight/30);
// 	m_pCursorSprite->SetFlags(D3DXSPRITE_ALPHABLEND);

	//m_pFont = IFont::CreateMyFont();
	//m_pFont->InitFont(14, 14, 20, false, DEFAULT_CHARSET, "Arial") ;

	RECT boundingRect;
	boundingRect.left = iClientWidth/2- 75;
	boundingRect.right = boundingRect.left + 150;
	boundingRect.top  = 10;
	boundingRect.bottom = boundingRect.top + 30;
	//m_pFont->SetRect(boundingRect);

	//m_pFont->SetFormat(DT_LEFT | DT_TOP);
	//m_pFont->SetTextColor(cColor::WHITE.GetColor());
}

// ***************************************************************
void GameBase::cHumanView::VOnUpdate(const TICK tickCurrent, const float fElapsedTime)
{
	if(m_pProcessManager)
	{
		m_pProcessManager->UpdateProcesses(tickCurrent);
	}
}

// ***************************************************************
void GameBase::cHumanView::VOnRender(const TICK tickCurrent, const float fElapsedTime)
{
	HRESULT hr;
	hr = OnBeginRender(tickCurrent);
	if(SUCCEEDED(hr))
	{
		VRenderPrivate();
		OnEndRender(hr);
	}
}

// ***************************************************************
void GameBase::cHumanView::VOnLostDevice()
{
	AppMsg appMsg;
	appMsg.m_uMsg = WM_DEVICELOST;
	appMsg.m_lParam = 0;
	appMsg.m_wParam = 0;

	/*if (m_pParentControl)
	{
		m_pParentControl->VPostMsg(appMsg);
	}
	*/
	/*for(ScreenElementList::iterator i = m_pElementList.begin(); i != m_pElementList.end(); ++i)
	{
		(*i)->VOnLostDevice();
	}*/
	//m_pCursorSprite->OnLostDevice();
	
	/*if (m_pFont)
	{
		m_pFont->VOnLostDevice();
	}*/
}

// ***************************************************************
HRESULT GameBase::cHumanView::VOnResetDevice()
{
	AppMsg appMsg;
	appMsg.m_uMsg = WM_DEVICERESET;
	appMsg.m_lParam = 0;
	appMsg.m_wParam = 0;

	/*if (m_pParentControl)
	{
		m_pParentControl->VPostMsg(appMsg);
	}*/

	HRESULT hr = S_OK;
	/*for(ScreenElementList::iterator i=m_pElementList.begin(); i!=m_pElementList.end(); ++i)
	{
		(*i)->VOnResetDevice();
	}*/
	//m_pCursorSprite->OnResetDevice();

	/*if (m_pFont)
	{
		m_pFont->VOnResetDevice();
	}*/
	return hr;
}

// ***************************************************************
void GameBase::cHumanView::VOnDestroyDevice()
{
	//SAFE_DELETE(m_pParentControl);
	RemoveElements();

	//SAFE_DELETE(m_pCursorSprite);
}

// ***************************************************************
bool GameBase::cHumanView::VOnMsgProc( const Base::AppMsg & msg )
{
	bool bHandled = false;
	switch(msg.m_uMsg)
	{
	case WM_CHAR:
		/*if (m_pParentControl)
		{
			bHandled = m_pParentControl->VPostMsg(msg);
		}*/
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
		/*if (m_pParentControl)
		{
			bHandled = m_pParentControl->VPostMsg(msg);
		}*/
		break;
	}
	return bHandled;
}

// ***************************************************************
GameBase::IGameView::GAMEVIEWTYPE GameBase::cHumanView::VGetType()
{
	return GV_HUMAN;
}

// ***************************************************************
GameBase::GameViewId GameBase::cHumanView::VGetId() const
{
	return -1;
}

// ***************************************************************
void GameBase::cHumanView::VOnAttach(GameViewId id)
{
	m_idView = id;
}

// ***************************************************************
HRESULT GameBase::cHumanView::OnBeginRender(TICK tickCurrent)
{
	m_tickCurrent = tickCurrent; 
	HRESULT hr = S_OK;
	IGraphicsClass::GetInstance()->VBeginRender();
	// check if the device is available
	/*HRESULT hr = IDXBase::GetInstance()->VIsAvailable() ;

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
		}
	}
	if (FAILED(hr))
	{
		VOnResetDevice();
	}
*/
	return hr;
}

// ***************************************************************
void GameBase::cHumanView::VRenderPrivate()
{
	AppMsg appMsg;
	appMsg.m_uMsg = WM_RENDER;
	appMsg.m_lParam = 0;
	appMsg.m_wParam = 0;

	/*if (m_pParentControl)
	{
		m_pParentControl->VPostMsg(appMsg);
	}*/

	/*for(ScreenElementList::iterator i=m_pElementList.begin(); i!=m_pElementList.end(); ++i)
	{
		if ((*i)->VIsVisible())
		{
			(*i)->VOnRender(appMsg);
		}
	}*/
// 		if (m_pCursorSprite->IsVisible())
// 		{
// 			m_pCursorSprite->SetPosition(D3DXVECTOR3((float)m_pInput->GetX(), (float)m_pInput->GetY(), 0.0f));
// 			m_pCursorSprite->OnRender(IDXBase::GetInstance()->VGetDevice());
// 		}
}

// ***************************************************************
void GameBase::cHumanView::OnEndRender(const HRESULT hr)
{
	m_tickLastDraw = m_tickCurrent; 
	IGraphicsClass::GetInstance()->VEndRender();
}

// ***************************************************************
void GameBase::cHumanView::PushElement(shared_ptr<IScreenElement> pScreenElement)
{
	//m_pElementList.push_back(pScreenElement);
}

// ***************************************************************
void GameBase::cHumanView::PopElement(shared_ptr<IScreenElement> pScreenElement)
{
	//m_pElementList.remove(pScreenElement);
}

// ***************************************************************
void GameBase::cHumanView::RemoveElements()
{
	/*while (!m_pElementList.empty())
	{
		m_pElementList.pop_front();
	}*/
}

// ***************************************************************
// Tries to restore a lost device
// ***************************************************************
void GameBase::cHumanView::HandleLostDevice(HRESULT hr)
{
	/*if(hr == D3DERR_DEVICELOST)
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
	}*/
}

bool GameBase::cHumanView::IsKeyLocked( const DWORD dwKey )  const
{
	return m_bLockedKeys[dwKey];
}

// ***************************************************************
// Locks the key on the keyboard
// ***************************************************************
void GameBase::cHumanView::LockKey( const DWORD dwKey ) 
{
	m_bLockedKeys[dwKey] = true;
}

void GameBase::cHumanView::UnlockKey( const DWORD dwKey ) 
{
	m_bLockedKeys[dwKey] = false;
}

// ***************************************************************
void GameBase::cHumanView::SetCursorVisible( bool bVisible )
{
// 	if (m_pCursorSprite)
// 	{
// 		m_pCursorSprite->SetVisible(bVisible);
// 	}
}

// ***************************************************************
//void GameBase::cHumanView::ShowPointList(const cVertex * const pData, const UINT iPrimitiveCount)
//{
//	IDXBase::GetInstance()->VDrawVertexPrimitiveUP(D3DPT_POINTLIST, iPrimitiveCount, pData);
//}
//
//// ***************************************************************
//void GameBase::cHumanView::ShowLineList( const Graphics::cVertex * const pData, const UINT iPrimitiveCount )
//{
//	IDXBase::GetInstance()->VDrawVertexPrimitiveUP(D3DPT_LINELIST, iPrimitiveCount, pData);
//}
//
//// ***************************************************************
//GAMEBASE_API void GameBase::cHumanView::ShowLineStrip( const Graphics::cVertex * const pData, const UINT iPrimitiveCount )
//{
//	IDXBase::GetInstance()->VDrawVertexPrimitiveUP(D3DPT_LINESTRIP, iPrimitiveCount, pData);
//}
//
//// ***************************************************************
//void GameBase::cHumanView::ShowTriangleList( const Graphics::cVertex * const pData, const UINT iPrimitiveCount )
//{
//	IDXBase::GetInstance()->VDrawVertexPrimitiveUP(D3DPT_TRIANGLELIST, iPrimitiveCount, pData);
//}

float GameBase::cHumanView::GetWidth()
{
	//return m_pParentControl->VGetWidth();
	return 0;
}

float GameBase::cHumanView::GetHeight()
{
	//return m_pParentControl->VGetHeight();
	return 0;
}