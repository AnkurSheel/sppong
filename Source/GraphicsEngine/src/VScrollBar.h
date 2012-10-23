// ***************************************************************
//  VScrollBar   version:  1.0   Ankur Sheel  date: 2012/04/29
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef VScrollBar_h__
#define VScrollBar_h__

#include "ScrollBarControl.h"

namespace Graphics
{
	class cVScrollBar
		: public cScrollBarControl
	{
	public:
		static cVScrollBar* Create();

	private:
		cVScrollBar();
		~cVScrollBar();
		bool VOnMouseMove(const int X, const int Y);
		void VSetAbsolutePosition();
		void VSetSize(const Base::cVector2 & vSize);
		void VSetThumbPosition(const int iNewPosition);
		void AutoSize();
	};
}
#endif // VScrollBar_h__