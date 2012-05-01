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
#include "KeyboardHandler.hxx"
#include "MouseHandler.hxx"

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
		: public IMouseHandler
	{
	public:
		virtual ~IBaseControl(){}
		virtual bool VPostMsg(const AppMsg & msg) = 0;
		virtual void VOnRender(const AppMsg & msg) = 0;
		virtual void VOnLostDevice() = 0;
		virtual HRESULT VOnResetDevice() = 0;
		virtual IBaseControl * VAddChildControl( IBaseControl * const pChildControl) = 0;
		virtual void VRemoveAllChildren() = 0;
		virtual void VSetPosition(const D3DXVECTOR3 & vPosition) = 0;
		virtual void VSetSize(const float fNewWidth, const float fNewHeight) = 0;
		virtual float VGetWidth() const = 0;
		virtual float VGetHeight() const = 0;
		virtual void VRegisterCallBack(function <void (bool)> callback) = 0;
		virtual void VUnregisterCallBack() = 0;

	public:
		GRAPHIC_API static IBaseControl * CreateWindowControl(WINDOWTYPE wType, const Base::cString & strFileName, const bool bAllowMovingControls);
		GRAPHIC_API static IBaseControl * CreateLabelControl(const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color, const Base::cString & strCaption);
		GRAPHIC_API static IBaseControl * CreateButtonControl(const Base::cString & strDefaultImage, const Base::cString & strPressedImage, const Base::cString & strCaption, const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color, const bool bAutoSize);
		GRAPHIC_API static IBaseControl * CreateButtonControl(const Base::cString & strDefaultImage, const Base::cString & strPressedImage);
		GRAPHIC_API static IBaseControl * CreateCheckBoxControl(const Base::cString & strCheckedImage, const Base::cString & strUncheckedImage, const Base::cString & strCaption, const int iCheckBoxWidth, const int iCheckBoxHeight, const int iSpaceCaption, const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color);
		GRAPHIC_API static IBaseControl * CreateTextBoxControl(const Base::cString & strDefaultImage, const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color );
		GRAPHIC_API static IBaseControl * CreateVScrollBarControl(const Base::cString & strBackgroundImage, const Base::cString & strDefaultThumbImage, const Base::cString & strPressedThumbImage, const Base::cString & strDefaultMinImage, const Base::cString & strPressedMinImage, const Base::cString & strDefaultMaxImage,	const Base::cString & strPressedMaxImage, const int iMinPos, const int iMaxPos);
		GRAPHIC_API static IBaseControl * CreateHScrollBarControl(const Base::cString & strBackgroundImage, const Base::cString & strDefaultThumbImage, const Base::cString & strPressedThumbImage, const Base::cString & strDefaultMinImage, const Base::cString & strPressedMinImage, const Base::cString & strDefaultMaxImage, const Base::cString & strPressedMaxImage, const int iMinPos, const int iMaxPos);
	};
}
#endif // BaseControl_hxx__