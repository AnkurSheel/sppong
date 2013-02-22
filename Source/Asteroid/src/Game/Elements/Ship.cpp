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
: m_fAcceleration(0)
, m_fRotationPower(0)
, m_fDragFactor(0)
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
	if(m_bIsDirty)
	{
		float cosAngle = cos(m_vRotation.z);
		float sinAngle = sin(m_vRotation.z);
		m_vLookAt.x = m_vForward.x * cosAngle - m_vForward.y * sinAngle;
		m_vLookAt.y = m_vForward.x * sinAngle + m_vForward.y * cosAngle;
		m_vLookAt.z = m_vForward.z;
	}
	if (m_vVelocity.LengthSquared() > EpsilonFloat)
	{
		cVector3 vPredictedPos = GetPosition() + (m_vVelocity * fElapsedTime);
		WrapAround(vPredictedPos);

		SetPosition(vPredictedPos);
		m_vVelocity -= (m_vVelocity * m_fDragFactor);
	}
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
void cShip::WrapAround(cVector3 &vPredictedPos)
{
	if (vPredictedPos.x < m_pGame->VGetScreenTopLeftPos().x)
	{
		vPredictedPos.x = m_pGame->VGetScreenBottomRightPos().x;
	}
	else if (vPredictedPos.x > m_pGame->VGetScreenBottomRightPos().x)
	{
		vPredictedPos.x = m_pGame->VGetScreenTopLeftPos().x;
	}
	else if (vPredictedPos.y > m_pGame->VGetScreenTopLeftPos().y)
	{
		vPredictedPos.y = m_pGame->VGetScreenBottomRightPos().y;
	}
	else if (vPredictedPos.y < m_pGame->VGetScreenBottomRightPos().y)
	{
		vPredictedPos.y = m_pGame->VGetScreenTopLeftPos().y;
	}
}

// *****************************************************************************
cShip * cShip::CastToShip()
{
	return this;
}