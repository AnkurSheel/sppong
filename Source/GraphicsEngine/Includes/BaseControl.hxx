// *****************************************************************************
//  BaseControl   version:  1.0   Ankur Sheel  date: 2011/11/22
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef BaseControl_hxx__
#define BaseControl_hxx__

#include "GraphicEngineDefines.h"
#include "MouseHandler.hxx"
#include "KeyboardHandler.hxx"
#include "ControlStructures.h"

namespace Base
{
	class cString;
	class cVector2;
	class cColor;
	struct AppMsg;
}

namespace Graphics
{
	class ICamera;
	class IMyFont;
}

namespace Graphics
{
	typedef function<void (const stUIEventCallbackParam &)> UIEventCallBackFn;

	/********************************************//**
	 * @brief Interface for All UI controls.
	 *
	 * Used to create UI controls such as Window, Label, 
	 * Button, CheckBox, TextBox and ScrollBars
	 ***********************************************/
	class IBaseControl
		: public IMouseHandler
		, public IKeyboardHandler
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
 		 * @param[in] strControlName The name of the control that needs to be removed
		 *
		 * Removes and deletes the child control
		 ***********************************************/
		virtual void VRemoveChildControl(const Base::cString & strControlName) = 0;
		/********************************************//**
 		 * @param[in] strControlName The name of the control that needs to be found
		 * @return The child control with name equal to strControlName
		 *
		 * Returns the child control
		 ***********************************************/
		virtual Graphics::IBaseControl * const VFindChildControl(const Base::cString & strControlName) = 0;
		/********************************************//**
 		 * @param[in] pCamera The camera which contains the current view matrix
		 *
		 * Draws the control
		 ***********************************************/
		virtual void VRender(const ICamera * const pCamera) = 0;
		/********************************************//**
 		 * @param[in] bIsVisible True if the control should be visible, false otherwise
		 *
		 * Sets the visibility of the 2D element
		 ***********************************************/
		virtual void VSetVisible(bool bIsVisible) = 0;
		/********************************************//**
 		 * @param[in] vPosition The position of the control
		 *
		 * Sets the position of the control
		 ***********************************************/
		virtual void VSetPosition(const Base::cVector2 & vPosition) = 0;
		/********************************************//**
 		 * @return vSize The size of the control
		 *
		 * Returns the size of the control
		 ***********************************************/
		virtual const Base::cVector2 VGetSize() const = 0;
		/********************************************//**
 		 * @param[in] vSize The new size of the control
		 *
		 * Sets the size of the control
		 ***********************************************/
		virtual void VSetSize(const Base::cVector2 & vSize) = 0;
		/********************************************//**
		 * @param[in] eventType The type of the event for the call back.
 		 * @param[in] fnCallback Function pointer to the callback funtion. The function takes in a stUIEventCallbackParam and returns void
		 *
		 * Sets the callback function to invoke when the eventType event occurs
		 ***********************************************/
		virtual void VRegisterCallBack(const UIEVENTTYPE eventType,
			UIEventCallBackFn fnCallback) = 0;
		/********************************************//**
		 * @param[in] eventType The type of the event for the call back.
		 *
		 * Unregisters the callback function for the eventtype event
		 ***********************************************/
		virtual void VUnregisterCallBack(const UIEVENTTYPE eventType) = 0;
		/********************************************//**
		 * @param[in] pControl The control to be moved to the front
		 *
		 * Moves the child control to the front.
		 ***********************************************/
		virtual void VMoveToFront(const IBaseControl * const pControl) = 0;
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
		 * @return Pointer to a window control object
		 *
		 * Returns a pointer to a window control object
		 ***********************************************/
		GRAPHIC_API static IBaseControl * CreateWindowControl(const cWindowControlDef & def);
		/********************************************//**
		 * @param[in] def The params to create the label control  
		 * @return Pointer to a label control object
		 *
		 * Returns a pointer to a label control object
		 ***********************************************/
		GRAPHIC_API static IBaseControl * CreateLabelControl(const cLabelControlDef & def);
		/********************************************//**
		 * @param[in] def The params to create the button control  
		 * @return Pointer to a button control object
		 *
		 * Returns a pointer to a button control object
		 ***********************************************/
		GRAPHIC_API static IBaseControl * CreateButtonControl(const cButtonControlDef & def);
		/********************************************//**
		 * @param[in] def The params to create the checkbox control  
		 * @return Pointer to a checkbox control object
		 *
		 * Returns a pointer to a checkbox control object
		 ***********************************************/
		GRAPHIC_API static IBaseControl * CreateCheckBoxControl(const cCheckBoxControlDef & def);
		/********************************************//**
		 * @param[in] def The params to create the textbox control  
		 * @return Pointer to a textbox control object
		 *
		 * Returns a pointer to a textbox control object
		 ***********************************************/
		GRAPHIC_API static IBaseControl * CreateTextBoxControl(const cTextBoxControlDef & def);
		/********************************************//**
		 * @param[in] def The params to create the vertical scrollbar control  
		 * @return Pointer to a vertical scrollbar control object
		 *
		 * Returns a pointer to a vertical scrollbar control object
		 ***********************************************/
		GRAPHIC_API static IBaseControl * CreateVScrollBarControl(const cScrollBarControlDef & def);
		/********************************************//**
		 * @param[in] def The params to create the horizontal scrollbar control  
		 * @return Pointer to a horizontal scrollbar control object
		 *
		 * Returns a pointer to a horizontal scrollbar control object
		 ***********************************************/
		GRAPHIC_API static IBaseControl * CreateHScrollBarControl(const cScrollBarControlDef & def);
	};
}
#endif // BaseControl_hxx__