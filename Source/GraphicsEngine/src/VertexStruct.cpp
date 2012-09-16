// ***************************************************************
//  VertexStruct   version:  1.0   Ankur Sheel  date: 05/25/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "VertexStruct.h"

using namespace Graphics;
using namespace Base;

// ***************************************************************
Graphics::stVertex::stVertex()
: m_fX(0.0f)
, m_fY(0.0f)
, m_fZ(0.0f)
, m_fRed(0.0f)
, m_fBlue(0.0f)
, m_fGreen(0.0f)
, m_fAlpha(0.0f)
{

}

// ***************************************************************
Graphics::stVertex::stVertex( const float fX, const float fY, const float fZ, 
						   const float fRed, const float fBlue, const float fGreen,
						   const float fAlpha )
: m_fX(fX)
, m_fY(fY)
, m_fZ(fZ)
, m_fRed(fRed)
, m_fBlue(fBlue)
, m_fGreen(fGreen)
, m_fAlpha(fAlpha)
{

}
