// *************************************************************************
//  ControlStructures   version:  1.0   Ankur Sheel  date: 2012/10/17
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************
#ifndef ControlStructures_h__
#define ControlStructures_h__

#include "vector2.h"

namespace Graphics
{
	class IBaseControl;
}

namespace Graphics
{
	/********************************************//**
     * @brief Callback Event Types for UI controls
     ***********************************************/
	enum UIEVENTTYPE
	{
		UIET_BTNPRESSED,	/*!< Button was pressed */ 
		UIET_BTNRELEASED,	/*!< Button was released */ 
		UIET_SCBCHANGED,	/*!< The value of the Scrollbar was changed */ 
	};

	/********************************************//**
     * @brief Return structure for UI callback functions
     ***********************************************/
	union unUIEventCallbackParam
	{
		bool	bChecked;		/*!< Will be set/unset for checkboxes */ 
		int		iThumbPos;		/*!< The position of the thumb for scrollbars */ 

		unUIEventCallbackParam()
			: bChecked(false)
		{
		}
	};

	/********************************************//**
     * @brief Common parameters for creating a UI control
     ***********************************************/
	class cBaseControlDef
	{
	public:
		Base::cVector2	vPosition;		/*!< The position of the control */ 
		Base::cVector2  vSize;			/*!< The scale in pixels of the control */ 
		Base::cString	strControlName;	/*!< The name of the control */ 
	};

	/********************************************//**
     * @brief Params for creating a window control
     ***********************************************/
	class cWindowControlDef
		: public cBaseControlDef
	{
	public:
		/********************************************//**
		 * @brief Enum for setting the window type for window
		 * controls
		 ***********************************************/
		enum WINDOWTYPE
		{
			WT_DESKTOP,		/*!< This type contains the whole app screen. All other UI items will be a child of this */ 
			WT_STANDARD,	/*!< This type is used to set a child window control. Can be used for grouping controls */ 
		};

	public:
		WINDOWTYPE		wType;					/*!< The window type. Can be DESKTOP or STANDARD */ 
		Base::cString	strBGImageFile;			/*!< The path for the background image. Can be Empty */
		bool			bAllowMovingControls;	/*!< True if we want to allow the users to change the position of the control */

		cWindowControlDef()
			: wType(WT_DESKTOP)
			, bAllowMovingControls(false)
		{
		}
	};

	/********************************************//**
     * @brief Definition for creating a label control
     ***********************************************/
	class cLabelControlDef
		: public cBaseControlDef
	{
	public:
		Base::cString		strFont;		/*!< The font that will be used to display the text */ 
		Base::cColor		textColor;		/*!< The text color */ 
		Base::cString		strText;		/*!< The text that should be displayed initially */ 
		Base::cString		strBGImageFile;	/*!< The path for the background image. Can be Empty */
		float				fTextHeight;	/*!< The text height */ 
		bool				bAutoSize;		/*!< If true, autosizes the label based on the text width and height */ 

		cLabelControlDef()
			: fTextHeight(0.0f)
			, bAutoSize(true)
		{
		}
	};

	/********************************************//**
     * @brief Definition for creating a button control
     ***********************************************/
	struct cButtonControlDef
		: public cBaseControlDef
	{
	public:
		Base::cString		strDefaultImage;	/*!< The filename of the default texture for the button */ 
		Base::cString		strPressedImage;	/*!< The filename of the pressed texture for the button */ 
		cLabelControlDef	labelControlDef;	/*!< Optional. Params for The label/text associated with this button */ 
		bool				bAutoSize;			/*!< If true, autosizes the button based on the text width and height */ 

		cButtonControlDef()
			: bAutoSize(false)
		{
		}
	};
	
	/********************************************//**
     * @brief Definition for creating a check box control
     ***********************************************/
	class cCheckBoxControlDef
		: public cBaseControlDef
	{
	public:
		cButtonControlDef	buttonControlDef;	/*!< Params for The button of the checkbox */ 
		cLabelControlDef	labelControlDef;	/*!< Params for The label of the checkbox */ 
		int					iSpaceCaption;		/*!< The space between the button and the label */ 
		bool				bChecked;			/*!< True, if the the checkbox is set by default*/ 

		cCheckBoxControlDef()
			: iSpaceCaption(0)
		{
		}
	};

	/********************************************//**
     * @brief Definition for creating a text box control
     ***********************************************/
	class cTextBoxControlDef
		: public cBaseControlDef
	{
	public:
		Base::cString			strBGImage;			/*!< Optional. The background image of the textbox */ 
		Base::cString			strFont;			/*!< The font that will be used to display the text */ 
		Base::cColor			textColor;			/*!< The text color */ 
		float					fTextHeight;		/*!< The text height */ 
		Base::cString			strCaretImage;		/*!< The image to be used for displaying the caret */ 
		int						iCaretWidth;		/*!< The width of the caret */ 
		float					fCaretUpdateTime;	/*!< The time after which the caret is toggled between being visible/invisible */ 
		Base::cString			strText;			/*!< The text that should be displayed initially */ 

		cTextBoxControlDef()
			: fTextHeight(0.0f)
			, iCaretWidth(0)
			, fCaretUpdateTime(0.0f)
		{
		}
	};

	/********************************************//**
     * @brief Definition for creating a vertical or a 
	 * horizontal scrollbar control
     ***********************************************/
	class cScrollBarControlDef
		: public cBaseControlDef
	{
	public:
		Base::cString		strBGImage;				/*!< The background image of the textbox */ 	
		cButtonControlDef	thumbBtnDef;			/*!< Params for The thumb button of the scrollbar */ 
		cButtonControlDef	TopLeftArrowDef;		/*!< Params for The top or left arrow button of the scrollbar */ 
		cButtonControlDef	BottomRightArrowDef;	/*!< Params for The bottom or right arrow button of the scrollbar */ 
		int					iMinPos;				/*!< The minimum value that the scrollbar can go to */ 
		int					iMaxPos;				/*!< The maximum value that the scrollbar can go to */ 
		int					iInitialThumbPosition;	/*!< The initial position of the thumb */ 

		cScrollBarControlDef()
			: iMinPos(0)
			, iMaxPos(0)
			, iInitialThumbPosition(0)
		{
		}
	};
		
}
#endif // ControlStructures_h__