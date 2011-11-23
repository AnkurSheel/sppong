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
		~cLabelControl();
		
		void OnKeyDown(const AppMsg & msg );
		void OnKeyUp(const AppMsg & msg );
		void OnRender(const AppMsg & msg);

		void Init(const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color, const Base::cString & strCaption );

	private:
		cLabelControl(const cLabelControl&){}
		cLabelControl operator =(const cLabelControl&){}

	private:
		IFont *				m_pFont;
		RECT				m_rectBoundary;
		D3DXVECTOR3			m_vPrevControlPosition;
	};
}
#endif // LabelControl_h__