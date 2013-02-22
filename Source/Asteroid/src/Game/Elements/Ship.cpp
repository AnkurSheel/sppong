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
}

// *****************************************************************************
void cShip::MoveBack(const float fElapsedTime)
{
	cContact contact;
	m_vVelocity -= (m_vLookAt * m_fAcceleration);
	//shared_ptr<IAABB> const pAABB = IAABB::DuplicateAABB(GetAABB());
	//pAABB->VTransalate(cVector3(0, -fDeltaMovement, 0));
	//if (!(ICollisionChecker::GetInstance()->VCheckForCollisions(pAABB.get(),
	//	m_pGame->VGetGameElements()[m_pGame->PGE_WALL_DOWN]->GetAABB(), contact)))
	//{
		//cVector3 vPredictedPos = GetPosition();
		//vPredictedPos -= vDeltaMovement;
		//SetPosition(vPredictedPos);
	//}
}

// *****************************************************************************
void cShip::MoveForward(const float fElapsedTime)
{
	cContact contact;
	m_vVelocity += (m_vLookAt * m_fAcceleration);
	//shared_ptr<IAABB> const pAABB = IAABB::DuplicateAABB(GetAABB());
	//pAABB->VTransalate(cVector3(0, fDeltaMovement, 0));
	//if (!(ICollisionChecker::GetInstance()->VCheckForCollisions(pAABB.get(),
	//	m_pGame->VGetGameElements()[m_pGame->PGE_WALL_UP]->GetAABB(), contact)))
	//{
		/*cVector3 vPredictedPos = GetPosition();
		vPredictedPos += vDeltaMovement;
		SetPosition(vPredictedPos);*/
	//}
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
cShip * cShip::CastToShip()
{
	return this;
}