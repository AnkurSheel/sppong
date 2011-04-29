// ***************************************************************
//  Polygon   version:  1.0   Ankur Sheel  date: 2011/01/31
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Polygon_hxx__
#define Polygon_hxx__

#include "GraphicEngineDefines.h"
namespace Graphics
{
	class IPolygon
	{
	public:
		virtual void Translate(const D3DXVECTOR2 & trans) = 0;
		GRAPHIC_API static IPolygon * CreatePolygon(const D3DXVECTOR2 * const pVertices, int nNoOfVertices);
	};
}
#endif // Polygon_hxx_