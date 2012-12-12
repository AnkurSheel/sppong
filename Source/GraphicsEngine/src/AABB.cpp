// *******************************************************************************************
//  AABB   version:  1.0   Ankur Sheel  date: 2012/11/25
//  ---------------------------------------------------------------------------------------
//  
//  ---------------------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *******************************************************************************************
// 
// *******************************************************************************************
#include "stdafx.h"
#include "AABB.h"

using namespace Graphics;
using namespace Base;

// *******************************************************************************************
cAABB::cAABB()
{

}

// *******************************************************************************************
cAABB::~cAABB()
{

}

cAABB::cAABB(const cAABB & other)
{
	m_vCenter = other.m_vCenter;
	m_vHalfExtents = other.m_vHalfExtents;
}

cAABB & cAABB::operator =(const cAABB & other)
{
	m_vCenter = other.m_vCenter;
	m_vHalfExtents = other.m_vHalfExtents;
	return *this;
}

// *******************************************************************************************
void cAABB::VTransalate(const Base::cVector3 & vDeltaPos)
{
	m_vCenter += vDeltaPos;
}

// *******************************************************************************************
cVector3 cAABB::GetCenter() const
{
	return m_vCenter;
}

// *******************************************************************************************
void cAABB::SetCenter(const cVector3 vCenter)
{
	m_vCenter = vCenter;
}

// *******************************************************************************************
Base::cVector3 cAABB::GetHalfExtents() const
{
	return m_vHalfExtents;
}

// *******************************************************************************************
void cAABB::SetHalfExtents(const cVector3 vHalfExtents)
{
	m_vHalfExtents = vHalfExtents;
}

// *******************************************************************************************
bool cAABB::Overlaps(const cAABB & other) const
{
	cVector3 vCenterDelta = other.m_vCenter - m_vCenter;
	vCenterDelta.AbsTo();

	cVector3 vHalfExtentSum = other.m_vHalfExtents + m_vHalfExtents;
	vCenterDelta = vCenterDelta - vHalfExtentSum;

	bool val = vCenterDelta.x <= 0 && vCenterDelta.y <= 0 && vCenterDelta.z <= 0;
	if(val)
	{
		int a = 5;
	}
	return vCenterDelta.x <= 0 && vCenterDelta.y <= 0 && vCenterDelta.z <= 0;
}

// *******************************************************************************************
IAABB * const IAABB::DuplicateAABB(const IAABB * const pAABB)
{
	const cAABB * ptr = dynamic_cast<const cAABB *>(pAABB);
	IAABB * dupAABB = DEBUG_NEW cAABB(*ptr);
	return dupAABB;
}