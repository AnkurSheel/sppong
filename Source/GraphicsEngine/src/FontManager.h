// *************************************************************************
//  FontManager   version:  1.0   Ankur Sheel  date: 2012/11/27
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************

#include "FontManager.hxx"

namespace Graphics
{
	class IMyFont;
}

namespace Graphics
{
	/********************************************//**
     * @brief Class Declaration for \c IFontManager
     * interface
     ***********************************************/
	class cFontManager
		: public IFontManager
	{
		/** Map of Fonts. The key is the font filename. Value is a shared_ptr to the actual font */
		typedef std::map<Base::cString, shared_ptr <IMyFont> > FontMap;

	public:
		/********************************************//**
 		 * @return An Object of this class
		 *
		 * Creates an object of this class and returns it
		 ***********************************************/
		static IFontManager * Create();

	private:
		cFontManager();
		~cFontManager();
		shared_ptr<IMyFont> VGetFont(const Base::cString & strFontDescFilename);
		/********************************************//**
 		 * param[in] strFontDescFilename The file name of the font description file
		 * @return Pointer to the font if it is found in the font list. NULL otherwise
		 *
		 * Checks if the font has already been loaded. Returns a pointer to the font if
		 * it is found. NULL otherwise.
		 ***********************************************/
		shared_ptr<IMyFont> Find(const Base::cString & strFontDescFilename);

	private:
		FontMap		m_pFonts;					/*!< map of the fonts that have already been loaded */

	public:
		static IFontManager * s_pFontManager;	/*!< static object of this class */
	};
}