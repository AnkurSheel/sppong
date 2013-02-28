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
	/********************************************//**
     * @brief Class Declaration for a Vertical Scrollbar
	 * UI Control
     ***********************************************/
	class cVScrollBar
		: public cScrollBarControl
	{
	public:
		/********************************************//**
 		 * @return An Object of this class
		 *
		 * Creates an object of this class and returns it
		 ***********************************************/
		static cVScrollBar* Create();

	private:
		cVScrollBar();
		~cVScrollBar();
		bool VOnMouseMove(const int X, const int Y);
		void VSetAbsolutePosition();
		void VSetSize(const Base::cVector2 & vSize);
		void VSetThumbPosition(const int iNewPosition);
		/********************************************//**
		 *
		 * Resizes the thumb depending on the number of increments
		 * and the total size of the scrollbar
		 ***********************************************/
		void AutoSizeThumb();
	};
}
#endif // VScrollBar_h__