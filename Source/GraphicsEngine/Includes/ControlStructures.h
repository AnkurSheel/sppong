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

	struct WindowControlDef
	{
		WINDOWTYPE wType;					/*!< The window type. Can be DESKTOP or STANDARD */ 
		Base::cString strBGImageFile;		/*!< The path for the background image. Can be Empty */
		bool bAllowMovingControls;			/*!< True if we want to allow the users to change the position of the control */

		WindowControlDef()
			: wType(WT_DESKTOP)
			, bAllowMovingControls(false)
		{
		}
	};

	struct LabelControlDef
	{
		shared_ptr<IMyFont> pFont;
		Base::cColor textColor;
		Base::cString strText;
		float fTextHeight;

		LabelControlDef()
			: fTextHeight(0.0f)
		{
		}
	};

	struct ButtonControlDef
	{
		Base::cString strDefaultImage;
		Base::cString strPressedImage;
		Base::cString strCaption;
		shared_ptr<IMyFont> pFont;
		Base::cColor textColor;
		bool bAutoSize;

		ButtonControlDef()
			: bAutoSize(false)
		{
		}
	};
	
}
#endif // ControlStructures_h__