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
	struct stVertex
	{
	public:
		float		m_fX, m_fY, m_fZ;
		float		m_fRed, m_fBlue, m_fGreen, m_fAlpha;
		GRAPHIC_API stVertex();
		GRAPHIC_API stVertex(const float fX, const float fY, const float fZ, 
			const float fRed, const float fBlue, const float fGreen, const float fAlpha);
	};

	struct stTexVertex
	{
	public:
		float		m_fX, m_fY, m_fZ;
		float		m_fTex0, m_fTex1;
		GRAPHIC_API stTexVertex();
		GRAPHIC_API stTexVertex(const float fX, const float fY, const float fZ, 
			const float fTex0, const float fTex1);
	};
}
#endif // vertexstruct_h__