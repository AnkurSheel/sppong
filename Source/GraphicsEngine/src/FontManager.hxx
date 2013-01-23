// *************************************************************************
//  FontManager   version:  1.0   Ankur Sheel  date: 2012/11/27
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************
#include "GraphicEngineDefines.h"

namespace Graphics
{
	class IMyFont;
}

namespace Graphics
{
	/********************************************//**
	 * @brief Interface for font manager.
	 *
	 * Use this class to create and use Fonts
	 * 
	 * Singleton class.\n
	 * Usage :
	 * \li Call \c GetInstance() to use this class.
	 * \li Call \c VOnDestroy() when the application quits
	 ***********************************************/
	class IFontManager
	{
	public:
		virtual ~IFontManager(){}
		/********************************************//**
 		 * @param[in] strFontDescFilename The file name of the font description file
		 * @return Pointer to the font
		 *
		 * Loads and creates the font if it has not been created already.
		 * Adds the font to the font list
		 * Returns a pointer to the existing font otherwise
		 ***********************************************/
		virtual shared_ptr<IMyFont> VGetFont(const Base::cString & strFontDescFilename) = 0;

		GRAPHIC_API static IFontManager * GetInstance();
		GRAPHIC_API static void Destroy();
	};
}