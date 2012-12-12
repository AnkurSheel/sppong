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
	
	m_vSpeed = cVector3(m_pRandomGenerator->Random(3) + 0.5f, m_pRandomGenerator->Random(6) + 0.5f, 0.0f);
}

// *****************************************************************************
void cBall::OnRestart( const cVector3& vInitialPos )
{
	//cPongGameElement::OnRestart(vInitialPos);
	//int iSpeedDirection = m_pRandomGenerator->Random(2);
	//if (iSpeedDirection == 1)
	//{
	//	m_vSpeed.m_dX = -m_vSpeed.m_dX;
	//}

	//iSpeedDirection = m_pRandomGenerator->Random(2);
	//if (iSpeedDirection == 1)
	//{
	//	m_vSpeed.m_dY = -m_vSpeed.m_dY;
	//}
}

// *****************************************************************************
void cBall::OnUpdate(float fElapsedTime)
{
	cVector3 vDeltaPos = m_vSpeed * fElapsedTime;
	IAABB * const pAABB = IAABB::DuplicateAABB(GetAABB());
	pAABB->VTransalate(vDeltaPos);
	if ((ICollisionChecker::GetInstance()->VCheckForCollisions(pAABB, m_pGame->VGetGameElements()[m_pGame->PGE_WALL_DOWN]->GetAABB()))
		|| (ICollisionChecker::GetInstance()->VCheckForCollisions(pAABB, m_pGame->VGetGameElements()[m_pGame->PGE_WALL_UP]->GetAABB())))
	{
		m_vSpeed.y = -m_vSpeed.y;
	}
	else
	{
		cVector3 vPredictedPos = GetPosition();
		vPredictedPos += vDeltaPos;
		SetPosition(vPredictedPos);
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
