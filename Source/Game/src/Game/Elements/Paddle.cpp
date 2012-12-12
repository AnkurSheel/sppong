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
#include "Game\Game.hxx"
#include "CollisionChecker.hxx"

using namespace Base;
using namespace GameBase;
using namespace Graphics;
using namespace Utilities;

// *****************************************************************************
cPaddle::cPaddle()
: m_iMoveFactor(0)
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
	m_iMoveFactor = 5;
}

// *****************************************************************************
void cPaddle::MoveDown( const float fElapsedTime )
{
	float fDeltaMovement = m_iMoveFactor * fElapsedTime;
	IAABB * const pAABB = IAABB::DuplicateAABB(GetAABB());
	pAABB->VTransalate(cVector3(0, -fDeltaMovement, 0));
	if (!(ICollisionChecker::GetInstance()->VCheckForCollisions(pAABB,
		m_pGame->VGetGameElements()[m_pGame->PGE_WALL_DOWN]->GetAABB())))
	{
		cVector3 vPredictedPos = GetPosition();
		vPredictedPos.y -= fDeltaMovement;
		SetPosition(vPredictedPos);
	}
}

// *****************************************************************************
void cPaddle::MoveUp( const float fElapsedTime )
{
	float fDeltaMovement = m_iMoveFactor * fElapsedTime;
	IAABB * const pAABB = IAABB::DuplicateAABB(GetAABB());
	pAABB->VTransalate(cVector3(0, fDeltaMovement, 0));
	if (!(ICollisionChecker::GetInstance()->VCheckForCollisions(pAABB,
		m_pGame->VGetGameElements()[m_pGame->PGE_WALL_UP]->GetAABB())))
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
void cPaddle::OnRestart( const Base::cVector3& vInitialPos )
{
	//cGameElement::OnRestart(vInitialPos);
	//if (m_vPosition.m_dX > m_siTableWidth /2)
	//{
	//	m_vPosition.m_dX = m_siTableWidth - m_pSprite->VGetSize().m_dX - 10.0f ;
	//	UpdatePosition();
	//}
}

// *****************************************************************************
cPaddle * cPaddle::CastToPaddle()
{
	return this;
}