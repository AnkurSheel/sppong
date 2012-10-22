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
		void Init(const stButtonControlDef & def);

	private:
		~cButtonControl();
		void VRender(const ICamera * const pCamera);
		bool VOnLeftMouseButtonUp(const int X, const int Y);
		bool VOnLeftMouseButtonDown(const int X, const int Y);
		void VSetAbsolutePosition();

	private:
		shared_ptr<ITexture>		m_pDefaultTexture;
		shared_ptr<ITexture>		m_pPressedTexture;
		shared_ptr<IBaseControl>	m_pLabel;
		bool						m_bPressed;
	};
}
#endif // ButtonControl_h__
