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

using namespace Base;
using namespace GameBase;
using namespace Utilities;

const cGame * cAsteroidGameElement::m_pGame = NULL;

// *****************************************************************************
cAsteroidGameElement::cAsteroidGameElement()
: m_fRotationPower(0)
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
cAsteroid * cAsteroidGameElement::CastToAsteroid()
{
	return NULL;
}

// *****************************************************************************
void cAsteroidGameElement::SetGame(const cGame * const pGame)
{
	m_pGame = pGame;
}

// *****************************************************************************
void cAsteroidGameElement::OnUpdate(float fElapsedTime)
{
	if(m_bIsDirty)
	{
		float cosAngle = cos(m_vRotation.z);
		float sinAngle = sin(m_vRotation.z);
		m_vLookAt.x = m_vForward.x * cosAngle - m_vForward.y * sinAngle;
		m_vLookAt.y = m_vForward.x * sinAngle + m_vForward.y * cosAngle;
		m_vLookAt.z = m_vForward.z;
	}
	cGameElement::OnUpdate(fElapsedTime);
}
