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
		void Init(const shared_ptr<IMyFont> m_pFont, const Base::cColor & textColor,
			const Base::cString & strText, const float fTextHeight);
	
	private:
		~cLabelControl();
		void VRender(const ICamera * const pCamera);
		void VSetAbsolutePosition();
		void VCleanup();

	private:
		ISentence *		m_pSentence;
	};
}
#endif // LabelControl_h__