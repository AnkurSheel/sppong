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
	class IMyFont;
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
		/********************************************//**
		 * @param[in] def The parameter definition to create a button control
		 *
		 * Initializes the button control as per the parameters
		 ***********************************************/
		void Initialize(const cButtonControlDef & def);

	private:
		~cButtonControl();
		void VRender(const ICamera * const pCamera);
		bool VOnLeftMouseButtonUp(const int X, const int Y);
		bool VOnLeftMouseButtonDown(const int X, const int Y);
		void VSetAbsolutePosition();

	private:
		shared_ptr<ITexture>		m_pDefaultTexture;	/*!< The texture to be used when the button is in default state. */ 
		shared_ptr<ITexture>		m_pPressedTexture;	/*!< The texture to be used when the button is in pressed state. */ 
		shared_ptr<IBaseControl>	m_pLabel;			/*!< The label/text associated with this button. */ 
		bool						m_bPressed;			/*!< True if the button is in pressed state. False otherwise. */ 
	};
}
#endif // ButtonControl_h__
