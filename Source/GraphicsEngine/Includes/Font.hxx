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
		/********************************************//**
 		 * @param[in] strFontDirPath The directory path from the font description file
		 * @param[in] strFontDescFilename The file name of the font description file
		 *
		 * Parses the font descrition file and sets up the character descriptors.
		 * Creates and Initialises the font texture.
		 ***********************************************/
		virtual bool VInitialize(const Base::cString & strFontDirPath,
			const Base::cString & strFontDescFilename) = 0;
		/********************************************//**
 		 * @param[in] pCamera The camera which contains the current view matrix
		 *
		 * Puts the text on the video card to prepare it for drawing
		 * by the shader
		 ***********************************************/
		virtual void VRender(const ICamera * const pCamera) = 0;
		/********************************************//**
 		 * @param[in] vPosition The new position at which the sprite should be shown
		 *
		 * Sets the position of the sprite
		 ***********************************************/
		virtual void VSetPosition(const Base::cVector2 & vPosition) = 0;
		/********************************************//**
 		 * @param[in] vPosition The text that needs to be displayed
		 *
		 * Sets the text that needs to be shown
		 ***********************************************/
		virtual void VSetText(const Base::cString & strText) = 0;
		/********************************************//**
		 * @return An object to use this interface
		 *
		 * Returns an object to use this interface
		 ***********************************************/
		GRAPHIC_API static shared_ptr<IMyFont> CreateMyFont();
	} ;
}
#endif // Font_h__
