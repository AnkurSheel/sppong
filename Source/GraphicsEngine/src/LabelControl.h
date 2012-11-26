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
	/********************************************//**
     * @brief Class Declaration for a Label UI Control
     ***********************************************/
	class cLabelControl
		: public cBaseControl
	{
	public:
		cLabelControl();
		/********************************************//**
		 * @param[in] def The parameter definition to create a label control
		 *
		 * Initializes the label control as per the parameters
		 ***********************************************/
		void Initialize(const stLabelControlDef & def);
	
	private:
		~cLabelControl();
		void VRender(const ICamera * const pCamera);
		void VSetAbsolutePosition();
		void VSetText(const Base::cString & strText);
		void VCleanup();

	private:
		ISentence *		m_pSentence;	/*!< The text/sentence of the label. */ 
	};
}
#endif // LabelControl_h__