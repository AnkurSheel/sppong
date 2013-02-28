// ***************************************************************
//  CheckBoxControl   version:  1.0   Ankur Sheel  date: 2011/12/11
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef CheckBoxControl_h__
#define CheckBoxControl_h__

#include "BaseControl.h"

namespace Graphics
{
    /********************************************//**
     * @brief Class Declaration for \c CheckBox UI Control
     ***********************************************/
	class cCheckBoxControl
		: public cBaseControl
	{
	public:
		cCheckBoxControl();
		/********************************************//**
		 * @param[in] def The parameter definition to create a checkbox control
		 *
		 * Initializes the checkbox control as per the parameters
		 ***********************************************/
		void Initialize(const cCheckBoxControlDef & def);

	private:
		~cCheckBoxControl();
		void VRender(const ICamera * const pCamera );
		bool VOnLeftMouseButtonDown(const int X, const int Y);
		void VSetAbsolutePosition();

	private:
		bool						m_bChecked;	/*!< True if The checkbox is checked. False otherwise. */ 
		shared_ptr<IBaseControl>	m_pTickBox;	/*!< The check box. This is a button UI control. */ 
	};
}
#endif // CheckBoxControl_h__