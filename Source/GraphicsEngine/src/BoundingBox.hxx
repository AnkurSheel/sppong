// *************************************************************************
//  BoundingBox   version:  1.0   Ankur Sheel  date: 2012/11/24
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************
#ifndef BoundingBox_hxx__
#define BoundingBox_hxx__

#include "GraphicEngineDefines.h"
namespace Graphics
{
	class IBoundingBox
	{
	public:
		virtual ~IBoundingBox() {}
		GRAPHIC_API virtual void VTransform(const D3DXMATRIX & matWorld) = 0;
		GRAPHIC_API static IBoundingBox * CreateBoundingBox(const Base::cVector3 & vMinBound,
			const Base::cVector3 & vMaxBound);
	};
}
#endif // BoundingBox_hxx__
