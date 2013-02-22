// *****************************************************************************
//  Ball   version:  1.0   Ankur Sheel  date: 05/13/2008
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "Asteroid.h"
#include "RandomGenerator.hxx"
#include "AABB.hxx"
#include "Game\Game.h"
#include "CollisionChecker.hxx"
#include "HumanView.h"

using namespace Graphics;
using namespace Base;
using namespace Utilities;
using namespace GameBase;

// *****************************************************************************
cAsteroid::cAsteroid()
: m_fMinSize(0)
, m_fSizeVariance(0)
{
}

// *****************************************************************************
cAsteroid::~cAsteroid()
{
	Cleanup();
}

// *****************************************************************************
void cAsteroid::VInitialize(const cGameElementDef & def )
{
	cAsteroidGameElement::VInitialize(def);

	m_fRotationPower = DegtoRad(30.0f);
	m_vForward = cVector3(1, 0, 0);
	m_vLookAt = m_vForward;


	cVector3 pos;
	int minPosX = static_cast<int>(m_pGame->VGetScreenTopLeftPos().x);
	int minPosY = static_cast<int>(m_pGame->VGetScreenBottomRightPos().y);
	int maxPosX = static_cast<int>(m_pGame->VGetScreenBottomRightPos().x);
	int maxPosY = static_cast<int>(m_pGame->VGetScreenTopLeftPos().y);

	pos.x = static_cast<float>(m_pGame->GetRandomGenerator()->Random(m_pGame->VGetScreenTopLeftPos().x, m_pGame->VGetScreenBottomRightPos().x));
	pos.y = static_cast<float>(m_pGame->GetRandomGenerator()->Random(m_pGame->VGetScreenBottomRightPos().y, m_pGame->VGetScreenTopLeftPos().y));
	SetPosition(pos);

	m_fMinSize = 0.5;
	m_fSizeVariance = 1.5;

	cVector3 scale;
	scale.x = min(m_fMinSize, m_pGame->GetRandomGenerator()->Random() * (m_fSizeVariance));
	scale.y = min(m_fMinSize, m_pGame->GetRandomGenerator()->Random() * (m_fSizeVariance));
	SetScale(scale);

	cVector3 rot;
	rot.z = static_cast<float>(m_pGame->GetRandomGenerator()->Random(0, 359));
	SetRotation(rot);

	//m_vVelocity = cVector3(static_cast<float>(m_pGame->GetRandomGenerator()->Random(5,10)), static_cast<float>(m_pGame->GetRandomGenerator()->Random(5,10)), 0.0f);
}

// *****************************************************************************
void cAsteroid::OnRestart()
{
	cAsteroidGameElement::OnRestart();
	//m_vVelocity = cVector3(static_cast<float>(m_pGame->GetRandomGenerator()->Random(5,10)), static_cast<float>(m_pGame->GetRandomGenerator()->Random(5,10)), 0.0f);
}

// *****************************************************************************
void cAsteroid::OnUpdate(float fElapsedTime)
{
	cContact contact;
	cVector3 vDeltaPos = m_vVelocity * fElapsedTime;
	//shared_ptr< IAABB> const pAABB = IAABB::DuplicateAABB(GetAABB());
	//pAABB->VTransalate(vDeltaPos);
	//cVector3 vPredictedPos = GetPosition();
	//if ((ICollisionChecker::GetInstance()->VCheckForCollisions(pAABB.get(), m_pGame->VGetGameElements()[m_pGame->PGE_WALL_DOWN]->GetAABB(), contact))
	//	|| (ICollisionChecker::GetInstance()->VCheckForCollisions(pAABB.get(), m_pGame->VGetGameElements()[m_pGame->PGE_WALL_UP]->GetAABB(), contact)))
	//{
	//	float nv = m_vSpeed.Dot(contact.vNormal);
	//	m_vSpeed -= contact.vNormal * 2 * nv;
	//	m_pGame->VGetHumanView()->PlaySFX("collision1.wav");

	//}
	//if ((ICollisionChecker::GetInstance()->VCheckForCollisions(pAABB.get(), m_pGame->VGetGameElements()[m_pGame->PGE_PADDLE_LEFT]->GetAABB(), contact))
	//	|| (ICollisionChecker::GetInstance()->VCheckForCollisions(pAABB.get(), m_pGame->VGetGameElements()[m_pGame->PGE_PADDLE_RIGHT]->GetAABB(), contact)))
	//{
	//	float nv = m_vSpeed.Dot(contact.vNormal);
	//	m_vSpeed -= contact.vNormal * 2 * nv;
	//	m_pGame->VGetHumanView()->PlaySFX("collision2.wav");

	//}
	/*vPredictedPos = vPredictedPos + vDeltaPos + contact.vDistance;
	SetPosition(vPredictedPos);

	if (GetPosition().x < m_pGame->VGetScreenTopLeftPos().x)
	{
		cGame * pGame = const_cast<cGame *>(m_pGame);
		pGame->VRoundOver(true);
	}
	else if (GetPosition().x > m_pGame->VGetScreenBottomRightPos().x)
	{
		cGame * pGame = const_cast<cGame *>(m_pGame);
		pGame->VRoundOver(false);
	}*/
	cAsteroidGameElement::OnUpdate(fElapsedTime);
}

// *****************************************************************************
void cAsteroid::Cleanup()
{
	cGameElement::Cleanup();
}

// *****************************************************************************
cAsteroid * cAsteroid::CastToAsteroid()
{
	return this;
}