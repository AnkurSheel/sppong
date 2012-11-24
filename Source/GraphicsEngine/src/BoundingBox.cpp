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

using namespace Graphics;
using namespace Base;

// *************************************************************************
cBoundingBox::cBoundingBox( const cVector3 & vMinBound, const cVector3 & vMaxBound)
{
	m_avObjectBounds[0] = cVector3(vMinBound.m_dX, vMinBound.m_dY, vMinBound.m_dZ); 
	m_avObjectBounds[1] = cVector3(vMaxBound.m_dX, vMinBound.m_dY, vMinBound.m_dZ); 
	m_avObjectBounds[2] = cVector3(vMinBound.m_dX, vMaxBound.m_dY, vMinBound.m_dZ); 
	m_avObjectBounds[3] = cVector3(vMaxBound.m_dX, vMaxBound.m_dY, vMinBound.m_dZ); 
	m_avObjectBounds[4] = cVector3(vMinBound.m_dX, vMinBound.m_dY, vMaxBound.m_dZ); 
	m_avObjectBounds[5] = cVector3(vMaxBound.m_dX, vMinBound.m_dY, vMaxBound.m_dZ); 
	m_avObjectBounds[6] = cVector3(vMinBound.m_dX, vMaxBound.m_dY, vMaxBound.m_dZ); 
	m_avObjectBounds[7] = cVector3(vMaxBound.m_dX, vMaxBound.m_dY, vMaxBound.m_dZ); 
}

// *************************************************************************
cBoundingBox::~cBoundingBox()
{
}

// *************************************************************************
void cBoundingBox::VTransform(const D3DXMATRIX & matWorld)
{
	D3DXVECTOR3 worldBounds[8];
	D3DXVECTOR3 objectBounds[8];
	for( int i = 0; i < 8; i++ )
	{
		objectBounds[i] = Vector3ToD3DXVEC3(m_avObjectBounds[i]);
		D3DXVec3TransformCoord( &worldBounds[i], &objectBounds[i], &matWorld );
		m_avOBBBounds[i] = D3DXVEC3ToVector3(worldBounds[i]);
		RecalculateAABBFromOBB();
	}
}

// *************************************************************************
void cBoundingBox::RecalculateAABBFromOBB()
{
	cVector3 vMin = m_avOBBBounds[0];
	cVector3 vMax = m_avOBBBounds[0];

	for (int i=0; i<8; i++)
	{
		vMin.m_dX = min(vMin.m_dX, m_avOBBBounds[i].m_dX);
		vMin.m_dY = min(vMin.m_dY, m_avOBBBounds[i].m_dY);
		vMin.m_dZ = min(vMin.m_dZ, m_avOBBBounds[i].m_dZ);

		//Get the largest vertex 
		vMax.m_dX = max(vMax.m_dX, m_avOBBBounds[i].m_dX);
		vMax.m_dY = max(vMax.m_dY, m_avOBBBounds[i].m_dY);
		vMax.m_dZ = max(vMax.m_dZ, m_avOBBBounds[i].m_dZ);
	}

	m_avAABBBounds[0] = cVector3(vMin.m_dX, vMin.m_dY, vMin.m_dZ); 
	m_avAABBBounds[1] = cVector3(vMax.m_dX, vMin.m_dY, vMin.m_dZ); 
	m_avAABBBounds[2] = cVector3(vMin.m_dX, vMax.m_dY, vMin.m_dZ); 
	m_avAABBBounds[3] = cVector3(vMax.m_dX, vMax.m_dY, vMin.m_dZ); 
	m_avAABBBounds[4] = cVector3(vMin.m_dX, vMin.m_dY, vMax.m_dZ); 
	m_avAABBBounds[5] = cVector3(vMax.m_dX, vMin.m_dY, vMax.m_dZ); 
	m_avAABBBounds[6] = cVector3(vMin.m_dX, vMax.m_dY, vMax.m_dZ); 
	m_avAABBBounds[7] = cVector3(vMax.m_dX, vMax.m_dY, vMax.m_dZ); 

}

// *************************************************************************
IBoundingBox * IBoundingBox::CreateBoundingBox(const cVector3 & vMinBound,
											   const cVector3 & vMaxBound)
{
	IBoundingBox * pAABB = DEBUG_NEW cBoundingBox(vMinBound, vMaxBound);
	return pAABB;
}