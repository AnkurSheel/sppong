// ***************************************************************
//  MouseHandler   version:  1.0   Ankur Sheel  date: 2012/04/20
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef MouseHandler_hxx__
#define MouseHandler_hxx__

namespace Graphics
{
	class IMouseHandler
	{
	public:
		virtual ~IMouseHandler(){}
		virtual bool VOnLeftMouseButtonUp(const int X, const int Y) = 0;
		virtual bool VOnLeftMouseButtonDown(const int X, const int Y) = 0;
	};
}

#endif // MouseHandler_h__