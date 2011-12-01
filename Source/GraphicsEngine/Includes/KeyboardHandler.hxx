// ***************************************************************
//  KeyboardHandler   version:  1.0   Ankur Sheel  date: 2011/05/11
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef KeyboardHandler_hxx__
#define KeyboardHandler_hxx__

#include "GraphicEngineDefines.h"

namespace Graphics
{
	class IKeyboardHandler
	{
	public:
		virtual ~IKeyboardHandler(){}
		GRAPHIC_API virtual bool OnKeyDown(const BYTE c)=0;
		GRAPHIC_API virtual bool OnKeyUp(const BYTE c)=0;
	};
}
#endif // KeyboardHandler_hxx__
