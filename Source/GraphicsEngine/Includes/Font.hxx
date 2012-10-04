// ***************************************************************
//  Font   version:  1.0   Ankur Sheel  date: 2011/02/16
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Font_hxx__
#define Font_hxx__

#include "GraphicEngineDefines.h"

namespace Base
{
	class cString;
}

namespace Graphics
{
	class ICamera;
}

namespace Graphics
{
	class IMyFont
	{
	public:
		virtual ~IMyFont(){}
		virtual bool VInitialize(const Base::cString & strFontDirPath,
			const Base::cString & strFontDescFilename) = 0;
		//virtual void InitFont(const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName) = 0;
		virtual void VSetText(const Base::cString & strText) = 0;
		/********************************************//**
 		 * @param[in] pCamera The camera which contains the current view matrix
		 *
		 * Puts the 2d texture on the video card to prepare it for drawing
		 * by the shader
		 ***********************************************/
		virtual void VRender(const ICamera * const pCamera) = 0;
		/********************************************//**
 		 * @param[in] vPosition The new position at which the sprite should be shown
		 *
		 * Sets the position of the sprite
		 ***********************************************/
		virtual void VSetPosition(const Base::cVector2 & vPosition) = 0;
		//virtual void SetRect(const RECT & boundingRect) = 0;
		//virtual void CalculateAndSetRect() = 0;
		//virtual const RECT & GetRect() const = 0;
		//virtual const RECT GetRect(const Base::cString & strText) const = 0;
		//virtual void SetFormat(const DWORD dwFormat) = 0;
		//virtual void SetTextColor(const D3DCOLOR & color) = 0;
		GRAPHIC_API static shared_ptr<IMyFont> CreateMyFont();
	} ;
}
#endif // Font_h__
