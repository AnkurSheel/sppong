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
#include "Bullet.h"
#include "Score.h"

using namespace Base;
using namespace GameBase;
using namespace Graphics;
using namespace Utilities;

// *****************************************************************************
cShip::cShip()
: m_iMaxNumberOfBullets(0)
, m_iActiveBullets(0)
, m_fBulletCountDown(0.0f)
, m_fLastBulletTime(0.0f)
, m_iScore(0)
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
	m_iMaxNumberOfBullets = 15;
	m_fBulletCountDown = 0.3f;

	m_iScore = 0;

	cGameElementDef bulletDef;
	bulletDef.strModelName = "sphere";
	bulletDef.vScale =	cVector3(0.2f, 0.2f, 0.2f);
	bulletDef.vPosition = m_vPosition;
	for (int i=0; i<m_iMaxNumberOfBullets;i++)
	{
		shared_ptr<cAsteroidGameElement> pBullet(DEBUG_NEW cBullet());
		pBullet->VInitialize(bulletDef);
		pBullet->VSetActive(false);
		m_Bullets.push_back(dynamic_pointer_cast<cBullet>(pBullet));
		m_pGame->AddGameElement(pBullet);
	}
}

// *****************************************************************************
void cShip::OnUpdate(float fElapsedTime)
{
	cAsteroidGameElement::OnUpdate(fElapsedTime);

	if(!m_bActive)
		return;
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
void cShip::Fire()
{
	if(!m_bActive)
		return;

	if (m_iActiveBullets < m_iMaxNumberOfBullets)
	{
		if(m_pGame->GetRunningTime() - m_fLastBulletTime >= m_fBulletCountDown)
		{
			BulletList::iterator iter;
			cBullet * pBullet = NULL;
			for (iter = m_Bullets.begin(); iter != m_Bullets.end(); iter++)
			{
				pBullet = (*iter).get();
				if (!pBullet->IsActive())
				{
					m_iActiveBullets++;
					pBullet->SetPosition(m_vPosition + (m_vLookAt * 0.75));
					pBullet->SetRotation(m_vRotation);
					pBullet->VSetActive(true);
					m_fLastBulletTime = m_pGame->GetRunningTime();
					break;
				}
			}
		}
	}
}

// *****************************************************************************
void cShip::OnRestart()
{
	cAsteroidGameElement::OnRestart();
	m_vVelocity = cVector3::Zero();
}

// *****************************************************************************
void cShip::Cleanup()
{
	m_Bullets.clear();
	cAsteroidGameElement::Cleanup();
}

// *****************************************************************************
cShip * cShip::CastToShip()
{
	return this;
}

// *****************************************************************************
void cShip::BulletDestroyed(cBullet * const pBullet)
{
	BulletList::iterator iter;
	for (iter = m_Bullets.begin(); iter != m_Bullets.end(); iter++)
	{
		if(pBullet == (*iter).get())
		{
			m_iActiveBullets--;
			pBullet->VSetActive(false);
			break;
		}
	}
}

// *****************************************************************************
void cShip::IncrementScore(const int iValue)
{
	m_iScore += iValue;
}
// *****************************************************************************
int cShip::GetScore() const
{
	return m_iScore;
}
