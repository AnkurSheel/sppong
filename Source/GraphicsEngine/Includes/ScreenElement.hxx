// ***************************************************************
//  ScreenElement   version:  1.0   Ankur Sheel  date: 2011/05/05
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef ScreenElement_hxx__
#define ScreenElement_hxx__

#include "GraphicEngineDefines.h"

namespace Base
{
	struct AppMsg;
}

namespace Graphics
{
	class ICamera;
}

namespace Graphics
{
	class IScreenElement
	{
	public:
		virtual ~IScreenElement(){};
		GRAPHIC_API virtual void VSetVisible(bool bIsVisible) = 0;
		GRAPHIC_API virtual bool VIsVisible() const = 0;
		GRAPHIC_API virtual void VOnRender(const ICamera * const pCamera) = 0;
	};
}
#endif // ScreenElement_hxx__