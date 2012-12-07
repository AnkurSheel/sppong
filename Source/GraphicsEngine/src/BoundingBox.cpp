// *************************************************************************
//  BoundingBox   version:  1.0   Ankur Sheel  date: 2012/11/24
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************
#include "stdafx.h"
#include "BoundingBox.h"
#include "Vector2.h"
#include "GraphicUtils.h"
#include "AABB.h"

using namespace Graphics;
using namespace Base;

// *************************************************************************
cBoundingBox::cBoundingBox( const cVector3 & vMinBound, const cVector3 & vMaxBound)
: m_pAABB(NULL)
{
	m_avObjectBounds[0] = cVector3(vMinBound.x, vMinBound.y, vMinBound.z); 
	m_avObjectBounds[1] = cVector3(vMaxBound.x, vMinBound.y, vMinBound.z); 
	m_avObjectBounds[2] = cVector3(vMinBound.x, vMaxBound.y, vMinBound.z); 
	m_avObjectBounds[3] = cVector3(vMaxBound.x, vMaxBound.y, vMinBound.z); 
	m_avObjectBounds[4] = cVector3(vMinBound.x, vMinBound.y, vMaxBound.z); 
	m_avObjectBounds[5] = cVector3(vMaxBound.x, vMinBound.y, vMaxBound.z); 
	m_avObjectBounds[6] = cVector3(vMinBound.x, vMaxBound.y, vMaxBound.z); 
	m_avObjectBounds[7] = cVector3(vMaxBound.x, vMaxBound.y, vMaxBound.z); 

	m_pAABB = DEBUG_NEW cAABB();
}

// *************************************************************************
cBoundingBox::~cBoundingBox()
{
	SAFE_DELETE(m_pAABB);
}

// *************************************************************************
void cBoundingBox::VTransform(const D3DXMATRIX & matWorld)
{
	D3DXVECTOR3 worldBounds[8];
	D3DXVECTOR3 objectBounds[8];
	for( int i = 0; i < 8; i++ )
	{
		objectBounds[i] = D3DXVECTOR3(m_avObjectBounds[i].x, m_avObjectBounds[i].y,
			m_avObjectBounds[i].z);
		D3DXVec3TransformCoord( &worldBounds[i], &objectBounds[i], &matWorld );
		m_avOBBBounds[i] = cVector3(worldBounds[i].x, worldBounds[i].y,
			worldBounds[i].z);
	}
	RecalculateAABBFromOBB();
}

// *************************************************************************
void cBoundingBox::RecalculateAABBFromOBB()
{
	cVector3 vMin = m_avOBBBounds[0];
	cVector3 vMax = m_avOBBBounds[0];

	for (int i=0; i<8; i++)
	{
		vMin.x = min(vMin.x, m_avOBBBounds[i].x);
		vMin.y = min(vMin.y, m_avOBBBounds[i].y);
		vMin.z = min(vMin.z, m_avOBBBounds[i].z);

		//Get the largest vertex 
		vMax.x = max(vMax.x, m_avOBBBounds[i].x);
		vMax.y = max(vMax.y, m_avOBBBounds[i].y);
		vMax.z = max(vMax.z, m_avOBBBounds[i].z);
	}

	m_pAABB->SetCenter((vMin + vMax) * 0.5f);
	m_pAABB->SetHalfExtents((vMax - vMin) * 0.5f);
}

// *************************************************************************
IBoundingBox * IBoundingBox::CreateBoundingBox(const cVector3 & vMinBound,
											   const cVector3 & vMaxBound)
{
	IBoundingBox * pAABB = DEBUG_NEW cBoundingBox(vMinBound, vMaxBound);
	return pAABB;
}