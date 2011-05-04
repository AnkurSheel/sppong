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

using namespace Utilities;
using namespace Graphics;
using namespace GameBase;

cMPongView::cMPongView()
{
}

cMPongView::~cMPongView()
{
}

void cMPongView::OnRender(cGame * pGame,  TICK tickCurrent, float fElapsedTime)
{
	cHumanView::OnRender(tickCurrent, fElapsedTime);

	// process the user inputs according to game logic
	pGame->ProcessInput(m_pInput->GetMouseXDelta(), m_pInput->GetMouseYDelta(), m_pInput->GetMouseZDelta(), m_pInput->GetPressedKeys(), m_pInput->GetPressedButtons(), fElapsedTime) ;


}
