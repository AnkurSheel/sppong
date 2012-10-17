// ***************************************************************
//  LabelControl   version:  1.0   Ankur Sheel  date: 2011/11/22
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef LabelControl_h__
#define LabelControl_h__

#include "BaseControl.h"

namespace Graphics
{
	class IMyFont;
	class ISentence;
}

namespace Graphics
{
	class cLabelControl
		: public cBaseControl
	{
	public:
		cLabelControl();
		void Init(const LabelControlDef & def);
	
	private:
		~cLabelControl();
		void VRender(const ICamera * const pCamera);
		void VSetAbsolutePosition();
		void VSetText(const Base::cString & strText);
		void VCleanup();

	private:
		ISentence *		m_pSentence;
	};
}
#endif // LabelControl_h__