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
#include "ScreenElement.hxx"
#include "MouseHandler.hxx"
#include "ControlStructures.h"

namespace Base
{
	class cString;
	class cVector2;
	class cColor;
}

namespace Graphics
{
	class ICamera;
	class IMyFont;
}

namespace Graphics
{
	/********************************************//**
	 * @brief Interface for All UI controls.
	 *
	 * Used to create UI controls such as Window, Label, 
	 * Button, CheckBox, TextBox and ScrollBars
	 ***********************************************/
	class IBaseControl
		: public IScreenElement
		, public IMouseHandler
	{
	public:
		virtual ~IBaseControl(){}
		/********************************************//**
 		 * @param[in] msg The window message that needs to be processed
		 * return True if the message is handled by this control or one of its children
		 *
		 * Checks if any of the child controls can handle the message. If no child
		 * controls can handle the message it tries to handle the message itself.
		 * Returns true if the message is handled. False otherwise
		 ***********************************************/
		virtual bool VPostMsg(const Base::AppMsg & msg) = 0;
		/********************************************//**
 		 * @param[in] pChildControl The control that needs to be added
		 *
		 * Adds a child control
		 ***********************************************/
		virtual void VAddChildControl(shared_ptr<IBaseControl> pChildControl) = 0;
		/********************************************//**
		 *
		 * Removes and deletes all the child controls.
		 ***********************************************/
		virtual void VRemoveAllChildren() = 0;
		/********************************************//**
 		 * @param[in] pChildControl The control that needs to be removed
		 *
		 * Removes and deletes the child control
		 ***********************************************/
		virtual void VRemoveChildControl(shared_ptr<IBaseControl> pChildControl) = 0;
		/********************************************//**
 		 * @param[in] vPosition The position of the control
		 *
		 * Sets the position of the control
		 ***********************************************/
		virtual void VSetPosition(const Base::cVector2 & vPosition) = 0;
		/********************************************//**
 		 * @param[in] vSize The new size of the sprite
		 *
		 * Sets the size of the control
		 ***********************************************/
		virtual void VSetSize(const Base::cVector2 & vSize) = 0;
		/********************************************//**
 		 * @param[in] callback pointer to the callback funtion. The function takes in a bool and returns void
		 *
		 * Sets the callback function to invoke when an event occurs
		 ***********************************************/
		virtual void VRegisterCallBack(function <void (bool)> callback) = 0;
		/********************************************//**
		 *
		 * UnRgisters the callback function
		 ***********************************************/
		virtual void VUnregisterCallBack() = 0;
		/********************************************//**
 		 * @return The width of the control
		 *
		 * Returns the width of the control
		 ***********************************************/
		virtual float VGetWidth() const = 0;
		/********************************************//**
 		 * @return The width of the control
		 *
		 * Returns the height of the control
		 ***********************************************/
		virtual float VGetHeight() const = 0;
		/********************************************//**
 		 * @param[in] strText The text to be displayed on the control
		 *
		 * Sets the text to be displayed on the control
		 ***********************************************/
		virtual void VSetText(const Base::cString & strText) = 0;

		/********************************************//**
		 * @param[in] def The params to create the window control  
		 * @return A window control object
		 *
		 * Returns a window control object
		 ***********************************************/
		GRAPHIC_API static IBaseControl * CreateWindowControl(const WindowControlDef & def);
		GRAPHIC_API static IBaseControl * CreateLabelControl(const LabelControlDef & def);
		GRAPHIC_API static IBaseControl * CreateButtonControl(const ButtonControlDef & def);
		//GRAPHIC_API static IBaseControl * CreateCheckBoxControl(const Base::cString & strCheckedImage, const Base::cString & strUncheckedImage, const Base::cString & strCaption, const int iCheckBoxWidth, const int iCheckBoxHeight, const int iSpaceCaption, const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color);
		//GRAPHIC_API static IBaseControl * CreateTextBoxControl(const Base::cString & strDefaultImage, const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color );
		//GRAPHIC_API static IBaseControl * CreateVScrollBarControl(const Base::cString & strBackgroundImage, const Base::cString & strDefaultThumbImage, const Base::cString & strPressedThumbImage, const Base::cString & strDefaultMinImage, const Base::cString & strPressedMinImage, const Base::cString & strDefaultMaxImage,	const Base::cString & strPressedMaxImage, const int iMinPos, const int iMaxPos);
		//GRAPHIC_API static IBaseControl * CreateHScrollBarControl(const Base::cString & strBackgroundImage, const Base::cString & strDefaultThumbImage, const Base::cString & strPressedThumbImage, const Base::cString & strDefaultMinImage, const Base::cString & strPressedMinImage, const Base::cString & strDefaultMaxImage, const Base::cString & strPressedMaxImage, const int iMinPos, const int iMaxPos);
	};
}
#endif // BaseControl_hxx__