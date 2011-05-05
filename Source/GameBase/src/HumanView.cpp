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
#include "Input.hxx"
#include "FPS.hxx"
#include "Sprite.hxx"
#include "MouseZone.hxx"
#include "myString.h"
#include "ScreenElement.hxx"

using namespace GameBase;
using namespace Utilities;
using namespace Graphics;
using namespace Base;

cHumanView::cHumanView() :
m_bRunFullSpeed(true)
, m_pFPS(NULL)
, m_pInput(NULL)
, m_pMouseZones(NULL)
, m_pProcessManager(NULL)
{
}

cHumanView::~cHumanView()
{
}

HRESULT cHumanView::OnResetDevice()
{
	LPDIRECT3DDEVICE9 pDevice = IDXBase::GetInstance()->GetDevice();
	HRESULT hr = S_FALSE;
	if (pDevice)
	{
		hr = IDXBase::GetInstance()->ResetDevice();

		for(ScreenElementList::iterator i=m_pElementList.begin(); i!=m_pElementList.end(); ++i)
		{
			(*i)->OnResetDevice();
		}
		m_pCursorSprite->OnResetDevice();

		if (m_pFPS)
		{
			m_pFPS->OnResetDevice(pDevice);
		}
	}
	return hr;
}

HRESULT cHumanView::OnBeginRender(TICK tickCurrent)
{
	m_tickCurrent = tickCurrent; 

	// check if the device is available
	HRESULT hr = IDXBase::GetInstance()->IsAvailable() ;

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
			hr = IDXBase::GetInstance()->BeginRender();
			if (SUCCEEDED(hr))
			{
				return hr;
			}
		}
	}
	return S_FALSE;
}

void cHumanView::OnEndRender(const HRESULT hr)
{
	m_tickLastDraw = m_tickCurrent; 

	IDXBase::GetInstance()->EndRender(hr);
}

HRESULT cHumanView::RenderPrivate( HRESULT & hr )
{
	if (FAILED(hr))
	{
		OnResetDevice();
	}
	if(SUCCEEDED(hr))
	{
		for(ScreenElementList::iterator i=m_pElementList.begin(); i!=m_pElementList.end(); ++i)
		{
			if ((*i)->IsVisible())
			{
				(*i)->Render(IDXBase::GetInstance()->GetDevice());
			}
		}
		if (m_pCursorSprite->IsVisible())
		{
			m_pCursorSprite->SetPosition(D3DXVECTOR3((float)m_pInput->GetX(), (float)m_pInput->GetY(), 0.0f));
			m_pCursorSprite->Render(IDXBase::GetInstance()->GetDevice());
		}
	}
	return hr;
}

void cHumanView::OnRender(TICK tickCurrent, float fElapsedTime)
{
	HRESULT hr;
	hr = OnBeginRender(tickCurrent);
	RenderPrivate(hr);
	if (SUCCEEDED(hr))
	{
		OnEndRender(hr);
	}
}

void cHumanView::OnCreateDevice( const HINSTANCE hInst, const HWND hWnd, int iClientWidth, int iClientHeight)
{
	m_pInput = IInput::CreateInputDevice();
	m_pInput->Init(hInst, hWnd, iClientWidth, iClientHeight);

	m_pMouseZones = IMouseZone::CreateMouseZone();

	m_pCursorSprite = ISprite::CreateSprite();
	m_pCursorSprite->Init(IDXBase::GetInstance()->GetDevice(), "resources\\Sprites\\cursor.png");
	m_pCursorSprite->SetSize((float)iClientWidth/30, (float)iClientHeight/30);
	m_pCursorSprite->SetFlags(D3DXSPRITE_ALPHABLEND);

	m_pFPS = IFPS::CreateFPS();
	m_pFPS->Init(IDXBase::GetInstance()->GetDevice(), D3DXVECTOR3((float)iClientWidth/2, 10.0f, 0.0f), BLACK);
}

void cHumanView::OnLostDevice()
{
	for(ScreenElementList::iterator i = m_pElementList.begin(); i != m_pElementList.end(); ++i)
	{
		(*i)->OnLostDevice();
	}
	m_pCursorSprite->OnLostDevice();
	
	if (m_pFPS)
	{
		m_pFPS->OnLostDevice();
	}
}

void cHumanView::OnDestroyDevice()
{
	RemoveElements();
	FreeZones();

	// delete the input handler
	SAFE_DELETE(m_pInput);

	SAFE_DELETE(m_pCursorSprite);
	SAFE_DELETE(m_pMouseZones);

	SAFE_DELETE(m_pFPS);

}
// ***************************************************************

IGameView::GAMEVIEWTYPE cHumanView::GetType()
{
	return GV_HUMAN;
}

GameViewId cHumanView::GetId() const
{
	return -1;
}

void cHumanView::OnAttach(GameViewId id)
{
	m_idView = id;
}

void cHumanView::PushElement(IScreenElement * pScreenElement, const cString & strZoneName)
{
	m_pElementList.push_back(pScreenElement);
	if(!strZoneName.IsEmpty())
	{
		ISprite * pSprite = dynamic_cast<ISprite *>(pScreenElement);
		if(pSprite)
		{
			m_pMouseZones->AddZone(strZoneName,
									(int)pSprite->GetPosition().x,
									(int)pSprite->GetPosition().y,
									pSprite->GetScaledWidth(),
									pSprite->GetScaledHeight(),
									LEFTBUTTON);
		}
	}
}

void cHumanView::PopElement(IScreenElement * pScreenElement)
{
	m_pElementList.remove(pScreenElement);
}

void cHumanView::RemoveElements()
{
	while (!m_pElementList.empty())
	{
		IScreenElement * pScreenElement = m_pElementList.front();
		SAFE_DELETE(pScreenElement);
		m_pElementList.pop_front();
	}
}

void cHumanView::FreeZones()
{
	if (m_pMouseZones)
	{
		m_pMouseZones->FreeZones();
	}
}

bool cHumanView::CheckZones(cString & strHitZoneName )
{
	return(m_pMouseZones->CheckZones(m_pInput->GetX(), 
									m_pInput->GetY(), 
									m_pInput->GetPressedButtons(), 
									strHitZoneName));
}

void cHumanView::OnUpdate(float fElapsedTime)
{
	GetInput();
	if(m_pProcessManager)
	{
		m_pProcessManager->UpdateProcesses(fElapsedTime);
	}
}

void cHumanView::RenderText()
{
	//m_pFPS->Render(IDXBase::GetInstance()->GetDevice(), m_pGameTimer->GetFPS());
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
			OnLostDevice();
			hr = IDXBase::GetInstance()->ResetDevice() ;

			OnResetDevice();
		}
	}
}
// ***************************************************************

// ***************************************************************
// Gets User Inputs 
// ***************************************************************
void cHumanView::GetInput() const
{
	m_pInput->DetectKeys();
	m_pInput->DetectMouseMovement();
}
// ***************************************************************

// ***************************************************************
// Locks the key on the keyboard
// ***************************************************************
void cHumanView::LockKey( const DWORD dwKey ) 
{
	m_pInput->LockKey(dwKey);
}

void cHumanView::SetCursorVisible( bool bVisible )
{
	if (m_pCursorSprite)
	{
		m_pCursorSprite->SetVisible(bVisible);
	}
}