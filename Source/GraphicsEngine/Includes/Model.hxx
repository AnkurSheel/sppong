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
	struct stVertex;
	class ICamera;
}

namespace Graphics
{
	class IModel
	{
	public:
		GRAPHIC_API virtual ~IModel(){}
		GRAPHIC_API virtual bool VOnInitialization(const stVertex * const pVertices, 
			const unsigned long * const pIndices, const UINT iNumberOfVertices, 
			const UINT iNumberOfIndices, const UINT iPrimitiveCount) = 0;
		GRAPHIC_API virtual void VCleanup() = 0;
		GRAPHIC_API virtual void VRender(const ICamera * const pCamera) = 0;
		GRAPHIC_API static IModel * CreateModel();
	};
}
#endif // Model_hxx__
