// *************************************************************************
//  TextureManager   version:  1.0   Ankur Sheel  date: 2012/10/28
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************

#include "stdafx.h"
#include "TextureManager.h"
#include "Texture.hxx"

using namespace Graphics;
using namespace Utilities;
using namespace Base;

ITextureManager * cTextureManager::s_pTexturemanager = NULL;

// *************************************************************************
cTextureManager::cTextureManager()
{

}

// *************************************************************************
cTextureManager::~cTextureManager()
{
	m_pTextures.clear();
}

// *************************************************************************
ITextureManager * cTextureManager::Create()
{
	return DEBUG_NEW cTextureManager();
}

// *************************************************************************
shared_ptr<ITexture> cTextureManager::VGetTexture(const cString & strTexturePath)
{
	shared_ptr<ITexture> ptr = Find(strTexturePath);

	if(ptr == NULL)
	{
		ptr = ITexture::CreateTexture(strTexturePath);
		m_pTextures[strTexturePath] = ptr;
	}

	return ptr;
}

// *************************************************************************
shared_ptr<ITexture> cTextureManager::Find(const Base::cString & strTexturePath)
{
	TextureMap::const_iterator itr = m_pTextures.find(strTexturePath);
	if(itr == m_pTextures.end())
	{
		return shared_ptr<ITexture>(); 
	}
	Log_Write_L2(ILogger::LT_COMMENT,  "Texture already loaded " + 
		strTexturePath);

	return (*itr).second;
}

// *************************************************************************
ITextureManager * ITextureManager::GetInstance()
{
	if(cTextureManager::s_pTexturemanager == NULL)
		cTextureManager::s_pTexturemanager = cTextureManager::Create();
	return cTextureManager::s_pTexturemanager ;
}

// *************************************************************************
void ITextureManager::Destroy()
{
	SAFE_DELETE(cTextureManager::s_pTexturemanager);
}