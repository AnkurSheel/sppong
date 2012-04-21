// ***************************************************************
//  ResourceManager   version:  1.0   Ankur Sheel  date: 2011/11/16
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "ResourceManager.h"
#include "ResCache.hxx"
#include "myString.h"

using namespace Utilities;
using namespace Base;

Graphics::cResourceManager::cResourceManager()
: m_pResourceCache(NULL)
{

}

Graphics::cResourceManager::~cResourceManager()
{

}

void Graphics::cResourceManager::OnDestroyDevice()
{
	SAFE_DELETE(m_pResourceCache);
	Destroy();
}

void Graphics::cResourceManager::Init()
{
	m_pResourceCache = IResCache::CreateResourceCache(30, "resources\\resources.zip");
	if(!m_pResourceCache->Init())
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Could not create Resource Cache.\n"));
		PostQuitMessage(0);
		return;
	}
}

IResCache * Graphics::cResourceManager::GetResourceCache() const
{
	return m_pResourceCache;
}

void Graphics::cResourceManager::Destroy()
{
	delete this;
	s_pResourceManager = NULL;
}


// ***************************************************************
// returns an instance of the class
// ***************************************************************
Graphics::IResourceManager* Graphics::IResourceManager::TheResourceManager()
{
	if(!s_pResourceManager)
		s_pResourceManager = DEBUG_NEW cResourceManager();
	return s_pResourceManager;
}