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

using namespace Utilities;
using namespace Base;

Graphics::IResourceManager * Graphics::cResourceManager::s_pResourceManager = NULL;

Graphics::cResourceManager::cResourceManager()
: m_pResourceCache(NULL)
{

}

Graphics::cResourceManager::~cResourceManager()
{
	SAFE_DELETE(m_pResourceCache);
}

void Graphics::cResourceManager::Init(const cString strPath)
{
	m_pResourceCache = IResCache::CreateResourceCache(30, strPath);
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

void Graphics::cResourceManager::Create()
{
	s_pResourceManager = DEBUG_NEW cResourceManager();
}

void Graphics::cResourceManager::Destroy()
{
	SAFE_DELETE(s_pResourceManager);
}

// ***************************************************************
// returns an instance of the class
// ***************************************************************
Graphics::IResourceManager* Graphics::IResourceManager::GetInstance()
{
	if(cResourceManager::s_pResourceManager == NULL)
		cResourceManager::Create();
	return cResourceManager::s_pResourceManager;
}

void Graphics::IResourceManager::Destroy()
{
	cResourceManager::Destroy();
}
