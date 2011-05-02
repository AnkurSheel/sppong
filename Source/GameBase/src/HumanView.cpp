#pragma once

#include "stdafx.h"
#include "HumanView.h"
#include "DxBase.hxx"
#include "ProcessManager.hxx"
#include "BaseApp.hxx"
#include "Input.hxx"
#include "FPS.hxx"

using namespace GameBase;
using namespace Utilities;
using namespace Graphics;

cHumanView::cHumanView() :
m_bRunFullSpeed(false)
//  m_pGameApp(pGameApp)
//, m_pFPS(NULL)
//, m_pInput(NULL)
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
		/*if (m_pGameApp)
		{
			m_pGameApp->OnResetDevice() ;
		}

		if (m_pFPS)
		{
			m_pFPS->OnResetDevice(pDevice);
		}*/
	}
	return hr;
}

HRESULT cHumanView::OnBeginRender(TICK tickCurrent)
{
	m_tickCurrent = tickCurrent; 

	if (m_tickCurrent == m_tickLastDraw) 
	{
		return false; 
	}

	// check if the device is available
	HRESULT hr = IDXBase::GetInstance()->IsAvailable() ;

	if(hr == D3DERR_DEVICELOST || hr == D3DERR_DEVICENOTRESET)
	{
		HandleLostDevice(hr) ;
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
	return false;
}

void cHumanView::OnEndRender(const HRESULT hr)
{
	m_tickLastDraw = m_tickCurrent; 

	IDXBase::GetInstance()->EndRender(hr);
}

void cHumanView::OnRender(TICK fTime, float fElapsedTime)
{

	// process the user inputs according to game logic
	//m_pGameApp->ProcessInput(m_pInput->GetMouseXDelta(), m_pInput->GetMouseYDelta(), m_pInput->GetMouseZDelta(), m_pInput->GetPressedKeys(), m_pInput->GetPressedButtons(), fElapsedTime) ;

	// render the game graphics
//	m_pGameApp->Render();
	
	/*CDXUTTextHelper txtHelper( m_pFont, m_pTextSprite, 15 ); 
VRenderText(txtHelper); 

m_ScreenElements.sort( SortBy_SharedPtr_Content<IScreenElement>()); 
for(ScreenElementList::iterator i=m_ScreenElements.begin(); i!=m_ScreenElements.end(); ++i)
{ 
	if ( (*i)->VIsVisible() ) 
	{ (*i)->VOnRender(fTime, fElapsedTime); 
	} 
}*/
}

void cHumanView::OnCreateDevice( const HINSTANCE hInst, const HWND hWnd, int iClientWidth, int iClientHeight)
{
	//m_pInput = IInput::CreateInputDevice();
	//m_pInput->Init(hInst, hWnd, iClientWidth, iClientHeight);

	//m_pFPS = IFPS::CreateFPS();
	//m_pFPS->Init(IDXBase::GetInstance()->GetDevice(), D3DXVECTOR3((float)iClientWidth/2, 10.0f, 0.0f));

}

void cHumanView::OnLostDevice()
{
	/*if (m_pGameApp)
	{
	m_pGameApp->OnLostDevice();
	}

	if (m_pFPS)
	{
	m_pFPS->OnLostDevice();
	}*/

}

void cHumanView::OnDestroyDevice()
{
	// delete the input handler
	//SAFE_DELETE(m_pInput);

	//SAFE_DELETE(m_pFPS);

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

void cHumanView::PushElement(Graphics::ISprite * pScreenElement)
{
	m_pElementList.push_front(pScreenElement);
}

void cHumanView::PopElement(Graphics::ISprite * pScreenElement)
{
	m_pElementList.remove(pScreenElement);
}

void cHumanView::OnUpdate( int deltaMilliseconds )
{
	m_pProcessManager->UpdateProcesses(deltaMilliseconds);
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
	//m_pInput->DetectKeys();
	//m_pInput->DetectMouseMovement();
}
// ***************************************************************
