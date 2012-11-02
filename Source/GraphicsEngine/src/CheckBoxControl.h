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
	class cCheckBoxControl
		: public cBaseControl
	{
	public:
		cCheckBoxControl();
		void Initialize(const stCheckBoxControlDef & def);

	private:
		~cCheckBoxControl();
		
		void VRender(const ICamera * const pCamera );
		bool VOnLeftMouseButtonDown(const int X, const int Y);
		void VSetAbsolutePosition();

	private:
		bool						m_bChecked;
		shared_ptr<IBaseControl>	m_pTickBox;
	};
}
#endif // CheckBoxControl_h__