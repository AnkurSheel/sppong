// ***************************************************************
//  Model   version:  1.0   Ankur Sheel  date: 2012/09/12
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Model_hxx__
#define Model_hxx__

#include "GraphicEngineDefines.h"

namespace Graphics
{
	class cVertex;
}

namespace Graphics
{
	class IModel
	{
	public:
		GRAPHIC_API virtual ~IModel(){}
		GRAPHIC_API virtual void VOnInitialization(const cVertex * const pVertexData, const UINT iNumberOfVertices, const UINT iPrimitiveCount) = 0;
		GRAPHIC_API virtual void VCleanup() = 0;
		GRAPHIC_API virtual void VRender() = 0;
		GRAPHIC_API static IModel * CreateModel();
	};
}
#endif // Model_hxx__
