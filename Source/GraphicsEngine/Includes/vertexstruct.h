// ***************************************************************
//  vertexstruct   version:  1.0   Ankur Sheel  date: 05/25/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef vertexstruct_h__
#define vertexstruct_h__

#include "GraphicEngineDefines.h"

namespace Graphics
{
	class cVertex
	{
	public:
		float				m_fX, m_fY, m_fZ;
		float				m_fRHW;
		DWORD				m_dwColour;
		static const DWORD	FVF  = D3DFVF_XYZRHW|D3DFVF_DIFFUSE;
		GRAPHIC_API cVertex();
		GRAPHIC_API cVertex(const float fX, const float fY, const float fZ, const float fRHW, const DWORD dwColour);
	};
	

	class Vertex
	{
		D3DXVECTOR3			m_vPosition ;
		float				m_fRHW ;
		DWORD				m_dwColour ;        // The vertex m_Colour.
		D3DXVECTOR2			m_vTex ;		//texture coordinates
		static const DWORD	FVF  = D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1 ;
		//static const DWORD FVF  = D3DFVF_XYZRHW|D3DFVF_TEX1 ;

		GRAPHIC_API Vertex() ;
		GRAPHIC_API Vertex(const D3DXVECTOR3& vPos) ;
		GRAPHIC_API Vertex(const D3DXVECTOR3& vPos, const D3DCOLOR& col) ;
		GRAPHIC_API Vertex(const D3DXVECTOR3& vPos, const D3DCOLOR& col, const D3DXVECTOR2& vTex0) ;
	} ;

	class VertexMultiTex
	{
		D3DXVECTOR3			m_vPosition ;
		DWORD				m_Colour ;        // The vertex m_Colour.
		float				m_fU ;
		float				m_fV ;		//texture coordinates
		float				m_fU1 ;
		float				m_fV1 ;			// tex1 coordinates
		static const DWORD FVF = D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1|D3DFVF_TEX2 ;

		GRAPHIC_API VertexMultiTex() ;
		GRAPHIC_API VertexMultiTex(const D3DXVECTOR3& vPos, const D3DCOLOR& col, const float fU, const float fV, const float fU1, const float fV1) ;
	} ;

	class VertexLight
	{
		D3DXVECTOR3			m_vPosition ;
		float				m_fU ;
		float				m_fV ;		//texture coordinates

		static const DWORD FVF = D3DFVF_XYZ|D3DFVF_TEX1 ;

		GRAPHIC_API VertexLight() ;
		GRAPHIC_API VertexLight(const D3DXVECTOR3& vPos) ;
		GRAPHIC_API VertexLight(const D3DXVECTOR3& vPos, const float fU, const float fV) ;
	} ;

	class MeshVertex
	{
		D3DXVECTOR3			m_vPosition ;
		D3DXVECTOR3			m_vNormal ;
		D3DXVECTOR2			m_vTex0 ;

		static const DWORD MESHVERTEX_FVF = D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1 ;

		GRAPHIC_API MeshVertex() ;
		GRAPHIC_API MeshVertex(const float x, const float y, const float z, const float nx, const float ny, const float nz, const float m_fU, const float m_fV) ;
	} ;

	class VertexNormDiffuse
	{
		D3DXVECTOR3			m_vPosition ;
		D3DXVECTOR3			m_vNormal ;
		DWORD				m_Colour ;        // The vertex m_Colour.
		D3DXVECTOR2			m_vTex0 ;
		static const DWORD FVF  = D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE| D3DFVF_TEX1 ;

		GRAPHIC_API VertexNormDiffuse() ;
		GRAPHIC_API VertexNormDiffuse(const D3DXVECTOR3 &vPos, const D3DXCOLOR& col, const D3DXVECTOR3& vNorm, const D3DXVECTOR2 & vTex) ;
	} ;

	class VertexNormSpec
	{
		D3DXVECTOR3			m_vPosition ;
		D3DXVECTOR3			m_vNormal ;
		DWORD				m_colDiffuse ;        // The vertex m_Colour.
		DWORD				m_colSpec ;        // The vertex m_Colour.
		D3DXVECTOR2			m_vTex0 ;
		static const DWORD FVF  = D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_SPECULAR|D3DFVF_TEX1 ;

		GRAPHIC_API VertexNormSpec() ;
		GRAPHIC_API VertexNormSpec(const D3DXVECTOR3 &vPos, const D3DXCOLOR& colDiffuse, const D3DCOLOR& colSpec, const D3DXVECTOR3& vNorm, const D3DXVECTOR2& vTex) ;
	} ;
}
#endif // vertexstruct_h__