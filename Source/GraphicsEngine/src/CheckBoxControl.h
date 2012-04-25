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
		~cCheckBoxControl();
		
		void Init(const Base::cString & strCheckedImage, const Base::cString & strUnCheckedImage, const Base::cString & strCaption, const int iCheckBoxWidth, const int iCheckBoxHeight, const int iSpaceCaption, const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color);
		bool GetCheckedState();
		void SetCheckedState(const bool bState);

		void VOnRender(const AppMsg & msg);
		bool VOnLeftMouseButtonDown(const int X, const int Y);
		void VOnLostDevice();
		HRESULT VOnResetDevice();
		void VRegisterCallBack(function <void ()> callback);
		void VUnregisterCallBack();

	private:
		cCheckBoxControl(cCheckBoxControl&){}
		cCheckBoxControl operator =(const cCheckBoxControl&){}

		void Cleanup();
	private:
		bool				m_bChecked;
		IBaseControl *		m_pTickBox;
		IBaseControl *		m_pLabel;
		D3DXVECTOR3			m_iLabelPosition;
		function<void ()>	m_pfnCallBack;
	};

#include "CheckBoxControl.inl"
}
#endif // CheckBoxControl_h__