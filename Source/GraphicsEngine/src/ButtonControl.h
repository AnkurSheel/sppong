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
		~cButtonControl();

		void Init(const Base::cString & strDefaultImage, const Base::cString & strPressedImage, const Base::cString & strCaption, const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color, const bool bAutoSize);
		void Init(const Base::cString & strDefaultImage, const Base::cString & strPressedImage);

		bool VOnLeftMouseButtonUp(const int X, const int Y);
		bool VOnLeftMouseButtonDown(const int X, const int Y);
		void VOnRender(const AppMsg & msg);
		void VOnLostDevice();
		HRESULT VOnResetDevice();
		void VRegisterCallBack(function <void ()> callback);
		void VUnregisterCallBack();

	private:
		cButtonControl(const cButtonControl&){}
		cButtonControl operator =(const cButtonControl&){}
		void Cleanup();
		void VSetSize(const float fNewWidth, const float fNewHeight);

	private:
		IBaseControl *				m_pLabelCaption;
		shared_ptr<ITexture>		m_pDefaultTexture;
		shared_ptr<ITexture>		m_pPressedTexture;
		bool						m_bPressed;
		function<void ()>			m_pfnCallBack;
	};
}
#endif // ButtonControl_h__
