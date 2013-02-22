// *****************************************************************************
//  Bullet   version:  1.0   Ankur Sheel  date: 2013/02/21
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "Bullet.h"
#include "AABB.hxx"
#include "Game\Game.h"
#include "CollisionChecker.hxx"
#include "Asteroid.h"

using namespace Base;
using namespace GameBase;
using namespace Graphics;
using namespace Utilities;

// *****************************************************************************
cBullet::cBullet()
{
}

// *****************************************************************************
cBullet::~cBullet()
{
}

// *****************************************************************************
void cBullet::VInitialize(const cGameElementDef & def )
{
	cAsteroidGameElement::VInitialize(def);
	m_fAcceleration = 0.2f;
	m_fDragFactor = 0.02f;
	m_fRotationPower = DegtoRad(30.0f);
	m_vForward = cVector3(1, 0, 0);
	m_vLookAt = m_vForward;
}

// *****************************************************************************
void cBullet::OnUpdate(float fElapsedTime)
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
			}
		}
	}
}

// *****************************************************************************
cBullet * cBullet::CastToBullet()
{
	return this;
}