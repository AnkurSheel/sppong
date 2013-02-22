// *****************************************************************************
//  AsteroidGameElement   version:  1.0   Ankur Sheel  date: 2013/02/21
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "AsteroidGameElement.h"
#include "Game\Game.hxx"

using namespace GameBase;

const cGame * cAsteroidGameElement::m_pGame = NULL;

// *****************************************************************************
cAsteroidGameElement::cAsteroidGameElement()
{
}

// *****************************************************************************
cAsteroidGameElement::~cAsteroidGameElement()
{
}

// *****************************************************************************
void cAsteroidGameElement::VInitialize(const cGameElementDef & def)
{
	cGameElement::VInitialize(def);
	m_vInitialPos = GetPosition();
}

// *****************************************************************************
void cAsteroidGameElement::OnRestart()
{
	SetPosition(m_vInitialPos);
}

// *****************************************************************************
cShip * cAsteroidGameElement::CastToShip()
{
	return NULL;
}

// *****************************************************************************
cBall * cAsteroidGameElement::CastToBall()
{
	return NULL;
}

// *****************************************************************************
void cAsteroidGameElement::SetGame(const cGame * const pGame)
{
	m_pGame = pGame;
}
