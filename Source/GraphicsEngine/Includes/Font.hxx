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
		 * Parses the font description file and sets up the character descriptors.
		 * Creates and Initializes the font texture.
		 ***********************************************/
		virtual bool VInitialize(const Base::cString & strFontDirPath,
			const Base::cString & strFontDescFilename) = 0;
		/********************************************//**
		 * @return An object to use this interface
		 *
		 * Returns an object to use this interface
		 ***********************************************/
		GRAPHIC_API static IMyFont * CreateMyFont();
	} ;
}
#endif // Font_h__
