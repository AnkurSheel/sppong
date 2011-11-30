// ***************************************************************
//  BaseControl   version:  1.0   Ankur Sheel  date: 2011/11/22
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef BaseControl_hxx__
#define BaseControl_hxx__

#include "GraphicEngineDefines.h"

namespace Base
{
	class cString;
}

namespace Graphics
{
	struct AppMsg;
}

namespace Graphics
{
	enum WINDOWTYPE
	{
		WT_DESKTOP,
		WT_STANDARD,
	};

	class IBaseControl
	{
	public:
		virtual ~IBaseControl(){}
		virtual bool PostMsg(const AppMsg & msg) = 0;
		virtual IBaseControl * AddChildControl( IBaseControl * const pChildControl) = 0;
		virtual void SetHeight(DWORD dwHeight) = 0;
		virtual void SetPosition(const D3DXVECTOR3 & vPosition) = 0;
		virtual void SetWidth(DWORD dwWidth) = 0;
		virtual void OnRender(const AppMsg & msg) = 0;

		GRAPHIC_API static IBaseControl * CreateWindowControl(WINDOWTYPE wType, const Base::cString & strFileName);
		GRAPHIC_API static IBaseControl * CreateLabelControl(const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color, const Base::cString & strCaption);
		GRAPHIC_API static IBaseControl * CreateButtonControl(const Base::cString & strDefaultImage, const Base::cString & strPressedImage, const Base::cString & strCaption, const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color);
	};
}
#endif // BaseControl_hxx__