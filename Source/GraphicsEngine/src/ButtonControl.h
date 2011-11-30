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

		void Init(const Base::cString & strDefaultImage, const Base::cString & strPressedImage, const Base::cString & strCaption, const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color);

		void OnMouseUp(const int iButton, const int X, const int Y);
		void OnMouseDown(const int iButton, const int X, const int Y);
		void OnKeyDown(const AppMsg & msg );
		void OnKeyUp(const AppMsg & msg );
		void OnRender(const AppMsg & msg);

	private:
		cButtonControl(const cButtonControl&){}
		cButtonControl operator =(const cButtonControl&){}
		void Cleanup();
	private:
		IBaseControl *		m_pLabelCaption;
		ITexture *			m_pDefaultTexture;
		ITexture *			m_pPressedTexture;
		bool				m_bPressed;
	};
}
#endif // ButtonControl_h__
