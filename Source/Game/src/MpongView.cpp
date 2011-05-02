#pragma once

#include "stdafx.h"
#include "MpongView.h"
#include "Sprite.hxx"
#include "DxBase.hxx"

using namespace Utilities;
using namespace Graphics;
using namespace GameBase;

cMPongView::cMPongView()
{
}

cMPongView::~cMPongView()
{
}


void cMPongView::OnRender(TICK tickCurrent, float fElapsedTime)
{
	HRESULT hr = OnBeginRender(tickCurrent);
	if(SUCCEEDED(hr))
	{
		for(ScreenElementList::iterator i=m_pElementList.begin(); i!=m_pElementList.end(); ++i)
		{
			(*i)->DrawSprite(IDXBase::GetInstance()->GetDevice(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXSPRITE_ALPHABLEND);
		}
		//pGame->m_pCursorSprite->DrawSprite(pGame->m_pD3dDevice, D3DXVECTOR3((float)IMainWindow::TheWindow()->GetAbsXMousePos(), (float)IMainWindow::TheWindow()->GetAbsYMousePos(), 0.0f), D3DXSPRITE_ALPHABLEND);

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

		OnEndRender(hr);
	}

}

HRESULT cMPongView::OnResetDevice()
{
	HRESULT hr = cHumanView::OnResetDevice();
	if(SUCCEEDED(hr))
	{
		/*if (m_pGameApp)
		{
		m_pGameApp->OnResetDevice() ;
		}*/
	}
	return hr;
}

void cMPongView::OnLostDevice()
{
	cHumanView::OnLostDevice();
	/*if (m_pGameApp)
	{
	m_pGameApp->OnLostDevice();
	}*/
}

void cMPongView::OnUpdate( int deltaMilliseconds )
{
	//m_pProcessManager->UpdateProcesses(deltaMilliseconds);
}

