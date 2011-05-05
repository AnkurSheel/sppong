// ***************************************************************
//  MpongView   version:  1.0   Ankur Sheel  date: 2011/05/02
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "MpongView.h"
#include "Sprite.hxx"
#include "DxBase.hxx"
#include "Game/Game.h"
#include "Input.hxx"
#include "Font.hxx"
#include "Game/Elements/Score.h"

using namespace Utilities;
using namespace Graphics;
using namespace GameBase;
using namespace Base;

cMPongView::cMPongView()
: m_bDisplayFPS(false)
{
}

cMPongView::~cMPongView()
{
}

void cMPongView::OnUpdate(cGame * pGame, float fElapsedTime)
{
	cHumanView::OnUpdate(fElapsedTime);

	const bool* const pbPressedKeys = m_pInput->GetPressedKeys();

	if (pbPressedKeys[DIK_F2])
	{
		// lock the F2 key
		m_pInput->LockKey(DIK_F2) ;

		m_bDisplayFPS = !m_bDisplayFPS;
	}
	if (pbPressedKeys[DIK_ESCAPE])
	{
		// lock the ESC key
		m_pInput->LockKey(DIK_ESCAPE) ;

		PostQuitMessage(0);
	}

	// process the user inputs according to game logic
	pGame->ProcessInput(m_pInput->GetMouseXDelta(), m_pInput->GetMouseYDelta(), m_pInput->GetMouseZDelta(), pbPressedKeys, m_pInput->GetPressedButtons(), fElapsedTime) ;
}

void cMPongView::OnRender(cGame * pGame, TICK tickCurrent, float fElapsedTime)
{
	HRESULT hr;
	hr = OnBeginRender(tickCurrent);
	RenderPrivate(hr);
	if (SUCCEEDED(hr))
	{
		if (m_bDisplayFPS)
		{
			m_pFont->SetText(cString(20, "%0.2f", pGame->GetFPS()));
			m_pFont->Render(IDXBase::GetInstance()->GetDevice());
		}
		OnEndRender(hr);
	}
}