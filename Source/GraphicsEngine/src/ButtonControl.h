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
	class cButtonControl
		: public cBaseControl
	{
	public:
		cButtonControl();
		void Init(const Base::cString & strDefaultImage, const Base::cString & strPressedImage,
			const Base::cString & strCaption, const shared_ptr<IMyFont> m_pFont,
			const Base::cColor & textColor, const bool bAutoSize);
		void Init(const Base::cString & strDefaultImage, const Base::cString & strPressedImage);

	private:
		~cButtonControl();
		void VRender(const ICamera * const pCamera );
		bool VOnLeftMouseButtonUp(const int X, const int Y);
		bool VOnLeftMouseButtonDown(const int X, const int Y);
		void VRegisterCallBack(function <void (bool)> callback);
		void VUnregisterCallBack();
		void VSetAbsolutePosition();
		void VCleanup();
	private:
		IBaseControl *				m_pLabelCaption;
		shared_ptr<ITexture>		m_pDefaultTexture;
		shared_ptr<ITexture>		m_pPressedTexture;
		bool						m_bPressed;
		function<void (bool)>		m_pfnCallBack;
	};
}
#endif // ButtonControl_h__
