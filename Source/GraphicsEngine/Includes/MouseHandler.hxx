// ***************************************************************
//  Input   version:  1.0   Ankur Sheel  date: 05/12/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef MouseHandler_hxx__
#define MouseHandler_hxx__

#include "GraphicEngineDefines.h"

namespace Graphics
{
	class IMouseHandler
	{
	public:
		virtual ~IMouseHandler(){}
		virtual bool OnMouseMove(const POINT & mousePos) = 0;
		virtual bool OnLButtonDown(const POINT & mousePos) = 0;
		virtual bool OnLButtonUp(const POINT & mousePos) = 0;
		virtual bool OnRButtonDown(const POINT & mousePos) = 0;
		virtual bool OnRButtonUp(const POINT & mousePos) = 0;
		GRAPHIC_API static IMouseHandler* CreateMouseHandler();
	};
}
#endif // MouseHandler_hxx__