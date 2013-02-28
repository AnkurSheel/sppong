// *****************************************************************************
//  GraphicUtils   version:  1.0   Ankur Sheel  date: 2012/12/06
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef GraphicUtils_hxx__
#define GraphicUtils_hxx__

#include "GraphicEngineDefines.h"

namespace Graphics
{
	class ICamera;
}

namespace Graphics
{
	class IGraphicUtils
	{
	public:
		/********************************************//**
		 * @return Returns a pointer to the singleton object
		 *
		 * Creates and returns a pointer to a singleton object of this interface
		 ***********************************************/
		GRAPHIC_API static IGraphicUtils * GetInstance();
		GRAPHIC_API static void Destroy();
		virtual Base::cVector3 ScreenToWorldSpace(const Base::cVector2 & vPos,
			const Graphics::ICamera * const pCamera) = 0;

	protected:
		virtual ~IGraphicUtils(){}
	};
}
#endif // GraphicUtils_hxx__
