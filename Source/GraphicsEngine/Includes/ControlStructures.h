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

namespace Base
{
	class cColor;
}

namespace Graphics
{
	class IMyFont;
}
namespace Graphics
{
	/********************************************//**
     * @brief Enum for setting the window type for window
	 * controls
     ***********************************************/
	enum WINDOWTYPE
	{
		WT_DESKTOP,			/*!< This type contains the whole app screen. All other UI items will be a child of this */ 
		WT_STANDARD,		/*!< This type is used to set a child window control. Can be used for grouping controls */ 
	};

	/********************************************//**
     * @brief Structure Definition for creating a window
     * control
     ***********************************************/
	struct stWindowControlDef
	{
		WINDOWTYPE		wType;					/*!< The window type. Can be DESKTOP or STANDARD */ 
		Base::cString	strBGImageFile;			/*!< The path for the background image. Can be Empty */
		bool			bAllowMovingControls;	/*!< True if we want to allow the users to change the position of the control */

		stWindowControlDef()
			: wType(WT_DESKTOP)
			, bAllowMovingControls(false)
		{
		}
	};

	/********************************************//**
     * @brief Structure Definition for creating a label
     * control
     ***********************************************/
	struct stLabelControlDef
	{
		shared_ptr<IMyFont> pFont;			/*!< The font that will be used to display the text */ 
		Base::cColor		textColor;		/*!< The text color */ 
		Base::cString		strText;		/*!< The text that should be displayed initially */ 
		float				fTextHeight;	/*!< The text height */ 

		stLabelControlDef()
			: fTextHeight(0.0f)
		{
		}
	};

	/********************************************//**
     * @brief Structure Definition for creating a button
     * control
     ***********************************************/
	struct stButtonControlDef
	{
		Base::cString		strDefaultImage;	/*!< The filename of the default texture for the button */ 
		Base::cString		strPressedImage;	/*!< The filename of the pressed texture for the button */ 
		stLabelControlDef	labelControlDef;	/*!< Optional. Params for The label/text associated with this button */ 
		bool				bAutoSize;			/*!< If true, autosizes the button based on the text width and height */ 
		int					iWidth;				/*!< The width of the button. Not required if autosize is true */ 
		int					iHeight;			/*!< The height of the button. Not required if autosize is true */ 

		stButtonControlDef()
			: bAutoSize(false)
			, iWidth(0)
			, iHeight(0)

		{
		}
	};
	
	/********************************************//**
     * @brief Structure Definition for creating a check box
     * control
     ***********************************************/
	struct stCheckBoxControlDef
	{
		stButtonControlDef	buttonControlDef;	/*!< Params for The button of the checkbox */ 
		stLabelControlDef	labelControlDef;	/*!< Params for The label of the checkbox */ 
		int					iSpaceCaption;		/*!< The space between the button and the label */ 
		bool				bChecked;			/*!< True, if the the checkbox is set by default*/ 

		stCheckBoxControlDef()
			: iSpaceCaption(0)
		{
		}
	};

	/********************************************//**
     * @brief Structure Definition for creating a text box
     * control
     ***********************************************/
	struct stTextBoxControlDef
	{
		Base::cString			strBGImage;			/*!< Optional. The background image of the textbox */ 
		shared_ptr<IMyFont>		pFont;				/*!< The font that will be used to display the text */ 
		Base::cColor			textColor;			/*!< The text color */ 
		float					fTextHeight;		/*!< The text height */ 
		Base::cString			strCaretImage;		/*!< The image to be used for displaying the caret */ 
		int						iCaretWidth;		/*!< The width of the caret */ 
		float					fCaretUpdateTime;	/*!< The time after which the caret is toggled between being visible/invisible */ 

		stTextBoxControlDef()
			: fTextHeight(0.0f)
			, iCaretWidth(0)
			, fCaretUpdateTime(0.0f)
		{
		}
	};

	/********************************************//**
     * @brief Structure Definition for creating a vertical
     * or a horizontal scrollbar control
     ***********************************************/
	struct stScrollBarControlDef
	{
		Base::cString		strBGImage;					
		stButtonControlDef	thumbBtnDef;				/*!< Params for The thumb button of the scrollbar */ 
		stButtonControlDef	TopLeftArrowDef;			/*!< Params for The top or left arrow button of the scrollbar */ 
		stButtonControlDef	BottomRightArrowDef;		/*!< Params for The bottom or right arrow button of the scrollbar */ 
		int					iMinPos;					/*!< The maximum value that the scrollbar can go to */ 
		int					iMaxPos;					/*!< The maximum value that the scrollbar can go to */ 
		int					iInitialThumbPosition;		/*!< The initial position of the thumb */ 

		stScrollBarControlDef()
			: iMinPos(0)
			, iMaxPos(0)
			, iInitialThumbPosition(0)
		{
		}
	};
		
}
#endif // ControlStructures_h__