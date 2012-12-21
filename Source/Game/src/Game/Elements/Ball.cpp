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
#include "Ball.h"
#include "RandomGenerator.hxx"
#include "AABB.hxx"
#include "Game\Game.hxx"
#include "CollisionChecker.hxx"

using namespace Graphics;
using namespace Base;
using namespace Utilities;
using namespace GameBase;

// *****************************************************************************
cBall::cBall()
: m_pRandomGenerator(NULL)
{
}

// *****************************************************************************
cBall::~cBall()
{
	Cleanup();
}

// *****************************************************************************
void cBall::VInitialize(const cGameElementDef & def )
{
	cPongGameElement::VInitialize(def);
	m_pRandomGenerator = IRandomGenerator::CreateRandomGenerator();
	if (m_pRandomGenerator)
	{
		Log_Write_L1(ILogger::LT_DEBUG, cString(100, "Random Generator created for Ball with seed %u", m_pRandomGenerator->GetRandomSeed()));
	}
	
	m_vSpeed = cVector3(static_cast<float>(m_pRandomGenerator->Random(5,10)), static_cast<float>(m_pRandomGenerator->Random(5,10)), 0.0f);
}

// *****************************************************************************
void cBall::OnRestart()
{
	cPongGameElement::OnRestart();
	m_vSpeed = cVector3(static_cast<float>(m_pRandomGenerator->Random(5,10)), static_cast<float>(m_pRandomGenerator->Random(5,10)), 0.0f);
	
	int iSpeedDirection = m_pRandomGenerator->Random(2);
	if (iSpeedDirection == 1)
	{
		m_vSpeed.x = -m_vSpeed.x;
	}

	iSpeedDirection = m_pRandomGenerator->Random(2);
	if (iSpeedDirection == 1)
	{
		m_vSpeed.y = -m_vSpeed.y;
	}
}

// *****************************************************************************
void cBall::OnUpdate(float fElapsedTime)
{
	cContact contact;
	cVector3 vDeltaPos = m_vSpeed * fElapsedTime;
	shared_ptr< IAABB> const pAABB = IAABB::DuplicateAABB(GetAABB());
	pAABB->VTransalate(vDeltaPos);
	cVector3 vPredictedPos = GetPosition();
	if ((ICollisionChecker::GetInstance()->VCheckForCollisions(pAABB.get(), m_pGame->VGetGameElements()[m_pGame->PGE_WALL_DOWN]->GetAABB(), contact))
		|| (ICollisionChecker::GetInstance()->VCheckForCollisions(pAABB.get(), m_pGame->VGetGameElements()[m_pGame->PGE_WALL_UP]->GetAABB(), contact))
		|| (ICollisionChecker::GetInstance()->VCheckForCollisions(pAABB.get(), m_pGame->VGetGameElements()[m_pGame->PGE_PADDLE_LEFT]->GetAABB(), contact))
		|| (ICollisionChecker::GetInstance()->VCheckForCollisions(pAABB.get(), m_pGame->VGetGameElements()[m_pGame->PGE_PADDLE_RIGHT]->GetAABB(), contact)))
	{
		float nv = m_vSpeed.Dot(contact.vNormal);
		m_vSpeed -= contact.vNormal * 2 * nv;
	}
	vPredictedPos = vPredictedPos + vDeltaPos + contact.vDistance;
	SetPosition(vPredictedPos);

	if (GetPosition().x < m_pGame->VGetScreenTopLeftPos().x)
	{
		IGame * pGame = const_cast<IGame *>(m_pGame);
		pGame->VRoundOver(true);
	}
	else if (GetPosition().x > m_pGame->VGetScreenBottomRightPos().x)
	{
		IGame * pGame = const_cast<IGame *>(m_pGame);
		pGame->VRoundOver(false);
	}

}

// *****************************************************************************
void cBall::Cleanup()
{
	SAFE_DELETE(m_pRandomGenerator);
	cGameElement::Cleanup();
}

// *****************************************************************************
cBall * cBall::CastToBall()
{
	return this;
}
