// ****************************************************************************
//  ResourceManager   version:  1.0   Ankur Sheel  date: 2011/11/16
//  ---------------------------------------------------------------------------
//  
//  ---------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ****************************************************************************
// 
// ****************************************************************************
#include "stdafx.h"
#include "ResourceManager.h"
#include "ResCache.hxx"

using namespace Utilities;
using namespace Base;

IResourceManager * Utilities::cResourceManager::s_pResourceManager = NULL;

// ****************************************************************************
cResourceManager::cResourceManager()
: m_pResourceCache(NULL)
{

}

// ****************************************************************************
cResourceManager::~cResourceManager()
{
	SAFE_DELETE(m_pResourceCache);
}

// ****************************************************************************
void cResourceManager::VInitialize(const cString strPath)
{
	m_pResourceCache = IResCache::CreateResourceCache(30, strPath);
	if(!m_pResourceCache->Init())
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Could not create Resource Cache.\n"));
		PostQuitMessage(0);
		return;
	}
}

// ****************************************************************************
IResCache * cResourceManager::VGetResourceCache() const
{
	return m_pResourceCache;
}

// ****************************************************************************
IResourceManager * cResourceManager::Create()
{
	return DEBUG_NEW cResourceManager();
}

// ****************************************************************************
IResourceManager * IResourceManager::GetInstance()
{
	if(cResourceManager::s_pResourceManager == NULL)
		cResourceManager::s_pResourceManager = cResourceManager::Create();
	return cResourceManager::s_pResourceManager;
}

// ****************************************************************************
void IResourceManager::Destroy()
{
	SAFE_DELETE(cResourceManager::s_pResourceManager);
}
