#pragma once

#include "stdafx.h"
#include "MpongView.h"

using namespace Game;
using namespace Utilities;
using namespace Graphics;

cMPongView::cMPongView()
{
}

cMPongView::~cMPongView()
{
}


void cMPongView::OnRender(float fTime, float fElapsedTime)
{
	HRESULT hr = OnBeginRender(fTime);
	if(SUCCEEDED(hr))
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

