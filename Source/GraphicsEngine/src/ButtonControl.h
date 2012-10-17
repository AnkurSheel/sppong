// ***************************************************************
//  ButtonControl   version:  1.0   Ankur Sheel  date: 2011/11/23
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef ButtonControl_h__
#define ButtonControl_h__

#include "BaseControl.h"

namespace Graphics
{
	class IFont;
	class cLabelControl;
	class ITexture;
}

namespace Graphics
{
    /********************************************//**
     * @brief Class Declaration for \c Button UI Control
     ***********************************************/
	class cButtonControl
		: public cBaseControl
	{
	public:
		cButtonControl();
		void Init(const ButtonControlDef & def);

	private:
		~cButtonControl();
		void VRender(const ICamera * const pCamera );
		bool VOnLeftMouseButtonUp(const int X, const int Y);
		bool VOnLeftMouseButtonDown(const int X, const int Y);
		void VSetAbsolutePosition();
		void VCleanup();
	private:
		IBaseControl *				m_pLabelCaption;	/*!< static object of this class */
		shared_ptr<ITexture>		m_pDefaultTexture;
		shared_ptr<ITexture>		m_pPressedTexture;
		bool						m_bPressed;
	};
}
#endif // ButtonControl_h__
