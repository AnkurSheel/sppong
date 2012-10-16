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
		/********************************************//**
		 * @param[in] strDefaultImage
		 * @param[in] strPressedImage
		 * @param[in] strCaption
		 * @param[in] m_pFont
		 * @param[in] textColor
		 * @param[in] bAutoSize
		 *
		 * Sets up the device, swap chain, depth buffer, depth stencil state. 
		 * Bind the render target view and the depth stencil buffer to the output render pipeline.
		 ***********************************************/
		void Init(const Base::cString & strDefaultImage, const Base::cString & strPressedImage,
			const Base::cString & strCaption, const shared_ptr<IMyFont> m_pFont,
			const Base::cColor & textColor, const bool bAutoSize);
		void Init(const Base::cString & strDefaultImage, const Base::cString & strPressedImage);

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
