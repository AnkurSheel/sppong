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
bool cAABB::Overlaps(const cAABB & other)
{
	cVector3 vCenterDelta = other.m_vCenter - m_vCenter;
	vCenterDelta.AbsTo();

	cVector3 vHalfExtentSum = other.m_vHalfExtents + m_vHalfExtents;
	vCenterDelta = vCenterDelta - vHalfExtentSum;

	return vCenterDelta.x < 0 && vCenterDelta.y < 0 && vCenterDelta.z < 0;
}
