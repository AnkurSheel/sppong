// ***************************************************************
//  HScrollBar   version:  1.0   Ankur Sheel  date: 2012/04/29
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef HScrollBar_h__
#define HScrollBar_h__

#include "ScrollBarControl.h"

namespace Graphics
{
	class cHScrollBar
		: public cScrollBarControl
	{
	public:
		static cHScrollBar* Create();

	private:
		cHScrollBar();
		~cHScrollBar();
		bool VOnMouseMove(const int X, const int Y);
		void VSetAbsolutePosition();
		void VSetSize(const float fNewWidth, const float fNewHeight);
		void VSetThumbPosition(const int iNewPosition);
		void AutoSize();
	};
}
#endif // HScrollBar_h__
