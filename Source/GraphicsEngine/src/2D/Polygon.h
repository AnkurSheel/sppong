// ***************************************************************
//  Polygon   version:  1.0   Ankur Sheel  date: 2011/01/31
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Polygon_h__
#define Polygon_h__

#include "GraphicEngineDefines.h"
namespace Graphics
{
	class cPolygon
	{
	public:
		GRAPHIC_API cPolygon(const D3DXVECTOR2 * const pVertices, int nNoOfVertices);
		GRAPHIC_API ~cPolygon();
		GRAPHIC_API void Translate(const D3DXVECTOR2 & trans);

	public:
		D3DXVECTOR2 *	m_pVertices;
		int				m_nNoOfVertices;
	};
}
#endif // Polygon_h__