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

const DWORD	Graphics::cVertex::FVF  = D3DFVF_XYZRHW|D3DFVF_DIFFUSE;

// ***************************************************************
Graphics::cVertex::cVertex()
: m_fX(0.0f)
, m_fY(0.0f)
, m_fZ(0.0f)
, m_fRHW(1.0f)
, m_dwColour(0)
{

}

// ***************************************************************
Graphics::cVertex::cVertex( const float fX, const float fY, const float fZ, const float fRHW, const DWORD dwColour )
: m_fX(fX)
, m_fY(fY)
, m_fZ(fZ)
, m_fRHW(fRHW)
, m_dwColour(dwColour)
{

}
/*
// ***************************************************************
// Constructor
// ***************************************************************
Vertex::Vertex()
{
	m_vPosition.x = 0.0f ;
	m_vPosition.y = 0.0f ;
	m_vPosition.z = 0.0f ;
//	m_Colour = WHITE ;
	m_vTex.x = 0 ;
	m_vTex.y = 0 ;
} 
// ***************************************************************

// ***************************************************************
// Constructor
// ***************************************************************
Vertex::Vertex(const D3DXVECTOR3 &vPos)
{
	m_vPosition = vPos ;
//	m_Colour = WHITE ;
	m_vTex.x = 0 ;
	m_vTex.y = 0 ;
}
// ***************************************************************

// ***************************************************************
// Constructor
// ***************************************************************
Vertex::Vertex(const D3DXVECTOR3 &vPos, const D3DCOLOR &col)
{
	m_vPosition = vPos ;
	m_dwColour = col ;
	m_vTex.x = 0 ;
	m_vTex.y = 0 ;
}
// ***************************************************************

// ***************************************************************
// Constructor
// ***************************************************************
Vertex::Vertex(const D3DXVECTOR3 &vPos, const D3DCOLOR &col, const D3DXVECTOR2 &vTex0)
{
	m_vPosition = vPos ;
	m_fRHW = 1.0f ;
	m_dwColour = col ;
	m_vTex = vTex0 ;
}
// ***************************************************************

// ***************************************************************
// Constructor
// ***************************************************************
VertexMultiTex::VertexMultiTex()
{
	m_vPosition.x = 0.0f ;
	m_vPosition.y = 0.0f ;
	m_vPosition.z = 0.0f ;
	m_Colour = cColor::WHITE.GetColor();
	m_fU = 0 ;
	m_fV = 0 ;
	m_fU1 = 0 ;
	m_fV1 = 0 ;
} 
// ***************************************************************

// ***************************************************************
// Constructor
// ***************************************************************
VertexMultiTex::VertexMultiTex(const D3DXVECTOR3& vPos, const D3DCOLOR &col, 
							   const float fU, const float fV, 
							   const float fU1, const float fV1)
{
	m_vPosition = vPos ;
	m_Colour = col ;
	m_fU = fU ;
	m_fV = fV ;
	m_fU1 = fU1 ;
	m_fV1 = fV1 ;
}
// ***************************************************************

// ***************************************************************
// Constructor
// ***************************************************************
VertexLight::VertexLight()
{
}
// ***************************************************************

// ***************************************************************
// Constructor
// ***************************************************************
VertexLight::VertexLight(const D3DXVECTOR3& vPos)
{
	m_vPosition = vPos ;
	m_fU = 0.0f ;
	m_fV = 0.0f ;
}
// ***************************************************************

// ***************************************************************
// Constructor
// ***************************************************************
VertexLight::VertexLight(const D3DXVECTOR3& vPos, const float fU, const float fV)
{
	m_vPosition = vPos ;
	
	
	m_fU = fU ;
	m_fV = fV ;
}
// ***************************************************************

// ***************************************************************
// Constructor
// ***************************************************************
MeshVertex::MeshVertex()
{
}
// ***************************************************************

// ***************************************************************
// Constructor
// ***************************************************************
MeshVertex::MeshVertex(const float x, const float y, const float z, const float nx, const float ny, const float nz, const float m_fU, const float m_fV)
{
	m_vPosition.x = x ;			m_vPosition.y = y ;			m_vPosition.z = z ;
	m_vNormal.x = nx ;		m_vNormal.y = ny ;		m_vNormal.z = nz ;
	m_vTex0.x = m_fU ;		m_vTex0.y = m_fV ;
}
// ***************************************************************

// ***************************************************************
// Constructor
// ***************************************************************
VertexNormDiffuse::VertexNormDiffuse()
{
}
// ***************************************************************

// ***************************************************************
// Constructor
// ***************************************************************
VertexNormDiffuse::VertexNormDiffuse(const D3DXVECTOR3 &vPos, const D3DXCOLOR& col, const D3DXVECTOR3& vNorm, const D3DXVECTOR2 & vTex)
{
	m_vPosition = vPos ;
	m_Colour = col ;
	m_vNormal = vNorm ;
	m_vTex0 = vTex ;
}
// ***************************************************************

// ***************************************************************
// Constructor
// ***************************************************************
VertexNormSpec::VertexNormSpec()
{
	m_vPosition.x = 0.0f ;
	m_vPosition.y = 0.0f ;
	m_vPosition.z = 0.0f ;
	m_vNormal.x = 0.0f ;
	m_vNormal.y = 0.0f ;
	m_vNormal.z = 0.0f ;

	m_colDiffuse = cColor::WHITE.GetColor();
	m_colSpec = cColor::WHITE.GetColor();
} 
// ***************************************************************

// ***************************************************************
// Constructor
// ***************************************************************
VertexNormSpec::VertexNormSpec(const D3DXVECTOR3 &vPos, const D3DXCOLOR& colDiffuse, const D3DCOLOR& colSpec, const D3DXVECTOR3& vNorm, const D3DXVECTOR2& vTex)
{
	m_vPosition = vPos ;
	m_vNormal = vNorm ;
	m_vTex0 = vTex ;
	m_colDiffuse = colDiffuse ;
	m_colSpec = colSpec ;
}
// ***************************************************************
*/