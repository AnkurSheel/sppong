// *************************************************************************
//  FontManager   version:  1.0   Ankur Sheel  date: 2012/11/27
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************

#include "stdafx.h"
#include "FontManager.h"
#include "Font.hxx"

using namespace Graphics;
using namespace Utilities;
using namespace Base;

IFontManager * cFontManager::s_pFontManager = NULL;

// *************************************************************************
cFontManager::cFontManager()
{

}

// *************************************************************************
cFontManager::~cFontManager()
{
	m_pFonts.clear();
}

// *************************************************************************
IFontManager * cFontManager::Create()
{
	return DEBUG_NEW cFontManager();
}

// *************************************************************************
shared_ptr<IMyFont> cFontManager::VGetFont(const Base::cString & strFontName)
{
	unsigned long hash = cHashedString::CalculateHash(strFontName);
	shared_ptr<IMyFont> ptr = Find(hash);

	if(ptr == NULL)
	{
		ptr = shared_ptr<IMyFont>(IMyFont::CreateMyFont());
		ptr->VInitialize(strFontName);
		m_pFonts[hash] = ptr;
	}
	else
	{
		Log_Write_L2(ILogger::LT_COMMENT, "Font already loaded: " + strFontName);
	}
	return ptr;
}

// *************************************************************************
shared_ptr<IMyFont> cFontManager::Find(const unsigned long ulFontHash)
{
	FontMap::const_iterator itr = m_pFonts.find(ulFontHash);
	if(itr == m_pFonts.end())
	{
		return shared_ptr<IMyFont>(); 
	}

	return (*itr).second;
}

// *************************************************************************
IFontManager * IFontManager::GetInstance()
{
	if(cFontManager::s_pFontManager == NULL)
		cFontManager::s_pFontManager = cFontManager::Create();
	return cFontManager::s_pFontManager ;
}

// *************************************************************************
void IFontManager::Destroy()
{
	SAFE_DELETE(cFontManager::s_pFontManager);
}