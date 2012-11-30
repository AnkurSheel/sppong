// ***************************************************************
//  GraphicUtils   version:  1.0   Ankur Sheel  date: 2012/08/29
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "GraphicUtils.h"
#include "Vector2.h"
#include "DxBase.hxx"
#include "Camera.hxx"

using namespace Base;
using namespace Graphics;

// ***************************************************************
D3DXVECTOR3 cGraphicUtils::Vector3ToD3DXVEC3(const cVector3& inVec)
{
	D3DXVECTOR3 vec;
	vec.x = inVec.m_dX;
	vec.y = inVec.m_dY;
	vec.z = inVec.m_dZ;
	return vec;
}

// ***************************************************************
Base::cVector3 cGraphicUtils::D3DXVEC3ToVector3(const D3DXVECTOR3& inVec)
{
	cVector3 vec;
	vec.m_dX = inVec.x;
	vec.m_dY = inVec.y;
	vec.m_dZ = inVec.z;
	return vec;
}

// ***************************************************************
D3DXVECTOR2 cGraphicUtils::Vector2ToD3DXVEC2(const Base::cVector2& inVec)
{
	D3DXVECTOR2 vec;
	vec.x = inVec.m_dX;
	vec.y = inVec.m_dY;
	return vec;
}

// ***************************************************************
Base::cVector2 cGraphicUtils::D3DXVEC2ToVector2(const D3DXVECTOR2& inVec)
{
	cVector2 vec;
	vec.m_dX = inVec.x;
	vec.m_dY = inVec.y;
	return vec;
}