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
	enum WINDOWTYPE
	{
		WT_DESKTOP,
		WT_STANDARD,
	};

	struct stWindowControlDef
	{
		WINDOWTYPE wType;					/*!< The window type. Can be DESKTOP or STANDARD */ 
		Base::cString strBGImageFile;		/*!< The path for the background image. Can be Empty */
		bool bAllowMovingControls;			/*!< True if we want to allow the users to change the position of the control */

		stWindowControlDef()
			: wType(WT_DESKTOP)
			, bAllowMovingControls(false)
		{
		}
	};

	struct stLabelControlDef
	{
		shared_ptr<IMyFont> pFont;		/*!< The font that will be used to display the text */ 
		Base::cColor textColor;			/*!< The text color */ 
		Base::cString strText;			/*!< The text that should be displayed initially */ 
		float fTextHeight;				/*!< The text height */ 

		stLabelControlDef()
			: fTextHeight(0.0f)
		{
		}
	};

	struct stButtonControlDef
	{
		Base::cString strDefaultImage;		/*!< The filename of the default texture for the button */ 
		Base::cString strPressedImage;		/*!< The filename of the pressed texture for the button */ 
		stLabelControlDef labelControlDef;	/*!< Optional. Params for The label/text associated with this button */ 
		bool bAutoSize;						/*!< If true, autosizes the button based on the text width and height */ 
		int iWidth;							/*!< The width of the button. Not required if autosize is true */ 
		int iHeight;						/*!< The height of the button. Not required if autosize is true */ 

		stButtonControlDef()
			: bAutoSize(false)
			, iWidth(0)
			, iHeight(0)

		{
		}
	};
	
	struct stCheckBoxControlDef
	{
		stButtonControlDef buttonControlDef;	/*!< Params for The button of the checkbox */ 
		stLabelControlDef  labelControlDef;		/*!< Params for The label of the checkbox */ 
		int iSpaceCaption;						/*!< The space between the button and the label */ 
		
		stCheckBoxControlDef()
			: iSpaceCaption(0)
		{
		}
	};

	struct stTextBoxControlDef
	{
		Base::cString strBGImage;
		shared_ptr<IMyFont> pFont;		/*!< The font that will be used to display the text */ 
		Base::cColor textColor;			/*!< The text color */ 
		float fTextHeight;				/*!< The text height */ 
		Base::cString strCaretImage;
		int iCaretWidth;
		float fCaretUpdateTime;

		stTextBoxControlDef()
			: fTextHeight(0.0f)
			, iCaretWidth(0)
			, fCaretUpdateTime(0.0f)
		{
		}
	};

	struct stScrollBarControlDef
	{
		Base::cString strBGImage;					
		stButtonControlDef thumbBtnDef;				/*!< Params for The thumb button of the scrollbar */ 
		stButtonControlDef TopLeftArrowDef;			/*!< Params for The top or left arrow button of the scrollbar */ 
		stButtonControlDef BottomRightArrowDef;		/*!< Params for The bottom or right arrow button of the scrollbar */ 
		int iMinPos;
		int iMaxPos;

		stScrollBarControlDef()
			: iMinPos(0)
			, iMaxPos(0)
		{
		}
	};
		
}
#endif // ControlStructures_h__