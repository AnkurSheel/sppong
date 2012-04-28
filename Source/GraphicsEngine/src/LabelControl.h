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
	class IFont;
}
namespace Graphics
{
	class cLabelControl
		: public cBaseControl
	{
	public:
		cLabelControl();
		void Init(const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color, const Base::cString & strCaption );
	
	private:
		~cLabelControl();
		void VOnRender(const AppMsg & msg);
		void VOnLostDevice();
		HRESULT VOnResetDevice();
		void VSetAbsolutePosition();
		void VSetSize(const float fNewWidth, const float fNewHeight);
		void UpdateRect();

	private:
		shared_ptr<IFont>		m_pFont;
		RECT					m_rectBoundary;
	};
}
#endif // LabelControl_h__