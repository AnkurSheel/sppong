// *****************************************************************************
//  Ship   version:  1.0   Ankur Sheel  date: 2013/02/21
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "Ship.h"
#include "AABB.hxx"
#include "Game\Game.h"
#include "CollisionChecker.hxx"
#include "Asteroid.h"

using namespace Base;
using namespace GameBase;
using namespace Graphics;
using namespace Utilities;

// *****************************************************************************
cShip::cShip()
{
}

// *****************************************************************************
cShip::~cShip()
{
}

// *****************************************************************************
void cShip::VInitialize(const cGameElementDef & def )
{
	cAsteroidGameElement::VInitialize(def);
	m_fAcceleration = 0.2f;
	m_fDragFactor = 0.02f;
	m_fRotationPower = DegtoRad(30.0f);
	m_vForward = cVector3(1, 0, 0);
	m_vLookAt = m_vForward;
}

// *****************************************************************************
void cShip::OnUpdate(float fElapsedTime)
{
	cAsteroidGameElement::OnUpdate(fElapsedTime);

	if(!m_bActive)
		return;

	IGame::GameElementList::iterator iter;
	IGame::GameElementList pGameElements;
	m_pGame->VGetGameElements(pGameElements);
	cAsteroid * pAsteroid = NULL;
	cContact contact;
	for (iter = pGameElements.begin(); iter != pGameElements.end(); iter++)
	{
		pAsteroid = (*iter)->CastToAsteroid();
		if(pAsteroid)
		{
			if ((ICollisionChecker::GetInstance()->VCheckForCollisions(GetAABB(),
				pAsteroid->GetAABB(), contact)))
			{
				MakeInactiveFor(1);
				cGame * pGame = const_cast<cGame *>(m_pGame);
				pGame->VRoundOver(false);
			}
		}
	}
}

// *****************************************************************************
void cShip::MoveBack(const float fElapsedTime)
{
	m_vVelocity -= (m_vLookAt * m_fAcceleration);
}

// *****************************************************************************
void cShip::MoveForward(const float fElapsedTime)
{
	m_vVelocity += (m_vLookAt * m_fAcceleration);
}

// *****************************************************************************
void cShip::RotateLeft(const float fElapsedTime)
{
	float fDeltaRadian = m_fRotationPower * fElapsedTime;
	SetRotation(cVector3(0.0f, 0.0f, GetRotation().z + fDeltaRadian));
}

// *****************************************************************************
void cShip::RotateRight(const float fElapsedTime)
{
	float fDeltaRadian = m_fRotationPower * fElapsedTime;
	SetRotation(cVector3(0.0f, 0.0f, GetRotation().z - fDeltaRadian));
}

// *****************************************************************************
void cShip::OnRestart()
{
	cAsteroidGameElement::OnRestart();
	m_vVelocity = cVector3::Zero();
}

// *****************************************************************************
cShip * cShip::CastToShip()
{
	return this;
}