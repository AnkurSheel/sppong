// *****************************************************************************
//  Paddle   version:  1.0   Ankur Sheel  date: 05/12/2008
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "Paddle.h"
#include "AABB.hxx"
#include "Game\Game.h"
#include "CollisionChecker.hxx"

using namespace Base;
using namespace GameBase;
using namespace Graphics;
using namespace Utilities;

// *****************************************************************************
cPaddle::cPaddle()
: m_fMoveFactor(0)
{
}

// *****************************************************************************
cPaddle::~cPaddle()
{
}

// *****************************************************************************
void cPaddle::VInitialize(const cGameElementDef & def )
{
	cPongGameElement::VInitialize(def);
	m_fMoveFactor = 6.f;
}

// *****************************************************************************
void cPaddle::MoveDown( const float fElapsedTime )
{
	cContact contact;
	float fDeltaMovement = m_fMoveFactor * fElapsedTime;
	shared_ptr<IAABB> const pAABB = IAABB::DuplicateAABB(GetAABB());
	pAABB->VTransalate(cVector3(0, -fDeltaMovement, 0));
	if (!(ICollisionChecker::GetInstance()->VCheckForCollisions(pAABB.get(),
		m_pGame->VGetGameElements()[m_pGame->PGE_WALL_DOWN]->GetAABB(), contact)))
	{
		cVector3 vPredictedPos = GetPosition();
		vPredictedPos.y -= fDeltaMovement;
		SetPosition(vPredictedPos);
	}
}

// *****************************************************************************
void cPaddle::MoveUp( const float fElapsedTime )
{
	cContact contact;
	float fDeltaMovement = m_fMoveFactor * fElapsedTime;
	shared_ptr<IAABB> const pAABB = IAABB::DuplicateAABB(GetAABB());
	pAABB->VTransalate(cVector3(0, fDeltaMovement, 0));
	if (!(ICollisionChecker::GetInstance()->VCheckForCollisions(pAABB.get(),
		m_pGame->VGetGameElements()[m_pGame->PGE_WALL_UP]->GetAABB(), contact)))
	{
		cVector3 vPredictedPos = GetPosition();
		vPredictedPos.y += fDeltaMovement;
		SetPosition(vPredictedPos);
	}
}

// *****************************************************************************
void cPaddle::MoveLeft( const float fElapsedTime )
{
	//m_vPosition.m_dX -= (m_iMoveFactor * fElapsedTime) ;
	//UpdatePosition();
}

// *****************************************************************************
void cPaddle::MoveRight( const float fElapsedTime )
{
	//m_vPosition.m_dX += (m_iMoveFactor * fElapsedTime) ;

	//UpdatePosition();
}

// *****************************************************************************
cPaddle * cPaddle::CastToPaddle()
{
	return this;
}