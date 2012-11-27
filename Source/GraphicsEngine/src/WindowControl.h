// ***************************************************************
//  WindowControl   version:  1.0   Ankur Sheel  date: 2011/11/21
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef WindowControl_h__
#define WindowControl_h__

#include "BaseControl.h"

namespace Graphics
{
	/********************************************//**
     * @brief Class Declaration for a Window UI Control
     ***********************************************/
	class cWindowControl
		: public cBaseControl
	{
	public:
		cWindowControl();
		/********************************************//**
		 * @param[in] def The parameter definition to create a window control
		 *
		 * Initializes the window control as per the parameters
		 ***********************************************/
		void Initialize(const stWindowControlDef & def);

	private:
		~cWindowControl();
	
		bool VOnLeftMouseButtonUp(const int X, const int Y);
		bool VOnLeftMouseButtonDown(const int X, const int Y);
		bool VOnMouseMove(const int X, const int Y);
		void VSetAbsolutePosition();

	private:
		WINDOWTYPE			m_eWindowType;	/*!< The window type. */
	};
}

#endif // WindowControl_h__