// *****************************************************************************
//  GameElement   version:  1.0   Ankur Sheel  date: 05/14/2008
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "PongGameElement.h"
#include "Game\Game.hxx"

using namespace GameBase;

const cGame * cPongGameElement::m_pGame = NULL;

// *****************************************************************************
cPongGameElement::cPongGameElement()
{
}

// *****************************************************************************
cPongGameElement::~cPongGameElement()
{
}

// *****************************************************************************
void cPongGameElement::VInitialize(const cGameElementDef & def)
{
	cGameElement::VInitialize(def);
	m_vInitialPos = GetPosition();
}

// *****************************************************************************
void cPongGameElement::OnRestart()
{
	SetPosition(m_vInitialPos);
}

// *****************************************************************************
cPaddle * cPongGameElement::CastToPaddle()
{
	return NULL;
}

// *****************************************************************************
cBall * cPongGameElement::CastToBall()
{
	return NULL;
}

// *****************************************************************************
void cPongGameElement::SetGame(const cGame * const pGame)
{
	m_pGame = pGame;
}
