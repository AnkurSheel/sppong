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
		shared_ptr<IMyFont> pFont;
		Base::cColor textColor;
		Base::cString strText;
		float fTextHeight;

		stLabelControlDef()
			: fTextHeight(0.0f)
		{
		}
	};

	struct stButtonControlDef
	{
		Base::cString strDefaultImage;
		Base::cString strPressedImage;
		Base::cString strCaption;
		shared_ptr<IMyFont> pFont;
		Base::cColor textColor;
		bool bAutoSize;
		int iWidth;
		int iHeight;

		stButtonControlDef()
			: bAutoSize(false)
			, iWidth(0)
			, iHeight(0)

		{
		}
	};
	
	struct stCheckBoxControlDef
	{
		stButtonControlDef buttonControlDef;
		stLabelControlDef  labelControlDef;

		int iSpaceCaption;
		stCheckBoxControlDef()
			: iSpaceCaption(0)
		{
		}
	};

	struct stTextBoxControlDef
	{
		Base::cString strBGImage;
		shared_ptr<IMyFont> pFont;
		Base::cColor textColor;
		float fTextHeight;
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
		stButtonControlDef thumbBtnDef;
		stButtonControlDef TopLeftArrowDef;
		stButtonControlDef BottomRightArrowDef;
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