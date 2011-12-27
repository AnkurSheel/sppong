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
		virtual void SetPosition(const D3DXVECTOR3 & vPosition) = 0;
		virtual void OnRender(const AppMsg & msg) = 0;
		virtual void SetSize(const float fNewWidth, const float fNewHeight) = 0;
		virtual DWORD GetWidth() const = 0;
		virtual DWORD GetHeight() const = 0;
		virtual bool OnMouseUp(const int iButton, const int X, const int Y) = 0;
		virtual bool OnMouseDown(const int iButton, const int X, const int Y) = 0;
		virtual IBaseControl * AddChildControl( IBaseControl * const pChildControl) = 0;
		virtual bool PostMsg(const AppMsg & msg) = 0;
		virtual void OnLostDevice() = 0;
		virtual HRESULT OnResetDevice() = 0;

	protected:
		virtual D3DXVECTOR3 GetPosition() const = 0;

	public:
		GRAPHIC_API static IBaseControl * CreateWindowControl(WINDOWTYPE wType, const Base::cString & strFileName);
		GRAPHIC_API static IBaseControl * CreateLabelControl(const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color, const Base::cString & strCaption);
		GRAPHIC_API static IBaseControl * CreateButtonControl(const Base::cString & strDefaultImage, const Base::cString & strPressedImage, const Base::cString & strCaption, const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color);
		GRAPHIC_API static IBaseControl * CreateButtonControl(const Base::cString & strDefaultImage, const Base::cString & strPressedImage);
		GRAPHIC_API static IBaseControl * CreateTextBoxControl(const Base::cString & strDefaultImage, const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color );
		GRAPHIC_API static IBaseControl * CreateCheckBoxControl(const Base::cString & strCheckedImage, const Base::cString & strUncheckedImage, const Base::cString & strCaption, const int iCheckBoxWidth, const int iCheckBoxHeight, const int iSpaceCaption, const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color);
	};
}
#endif // BaseControl_hxx__