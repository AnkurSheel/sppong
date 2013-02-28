// ***************************************************************
//  ResCache   version:  1.0   Ankur Sheel  date: 2011/04/01
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "ResCache.h"
#include "ZipFile.hxx"
#include "Optional.h"

using namespace Utilities;
using namespace Base;
	
cResCache::cResCache(unsigned int iCacheSizeInMB, const IResourceFile * pResFile)
: m_iCacheSize(iCacheSizeInMB * MEGABYTE)
, m_iTotalMemoryAllocated(0)
{
	m_pFile = const_cast<IResourceFile *>(pResFile);
}


cResCache::~cResCache()
{
	while(!m_lru.empty())
	{
		FreeOneResource();
	}
	SAFE_DELETE(m_pFile);
}

bool cResCache::Init()
{
	return m_pFile->Open();
}

shared_ptr<IResHandle> cResCache::GetHandle(IResource & r)
{
	shared_ptr<IResHandle> handle(Find(r));
	if(handle == NULL)
	{
		handle = Load(r);
	}
	else
	{
		Update(handle);
	}
	return handle;
}
		
void cResCache::Flush()
{
	while(m_lru.empty())
	{
		shared_ptr<IResHandle> handle = *(m_lru.begin());
		Free(handle);
		m_lru.pop_front();
	}
}

shared_ptr<IResHandle> cResCache::Find(const IResource & r)
{
	ResHandleMap::const_iterator itr = m_Resources.find(r.VGetFileName());
	if(itr == m_Resources.end())
	{
		Log_Write_L2(ILogger::LT_COMMENT, cString(100, "Could not find %s in cache", r.VGetFileName().GetData()));
		return shared_ptr<IResHandle>(); 
	}
	Log_Write_L2(ILogger::LT_COMMENT, cString(100, "Found %s in cache", r.VGetFileName().GetData()));

	return (*itr).second;
}

const void cResCache::Update(shared_ptr<IResHandle> handle)
{
	m_lru.remove(handle);
	m_lru.push_front(handle);
}

shared_ptr<IResHandle> cResCache::Load(IResource & r)
{
	int iSize = m_pFile->GetResourceSize(r);
	if (iSize == 0)
	{
		Log_Write_L1(ILogger::LT_ERROR, "Could not find file in zip file");
		return shared_ptr<IResHandle>();
	}
	char * pBuffer = Allocate(iSize);
	if(pBuffer == NULL)
	{
		return shared_ptr<IResHandle>();
	}

	shared_ptr<IResHandle> handle(r.VCreateHandle(pBuffer, iSize, this));

	handle->Load(m_pFile);

	m_lru.push_front(handle);
	m_Resources[r.VGetFileName()] = handle;

	return handle;
}

void cResCache::Free(shared_ptr<IResHandle> handle)
{
	m_lru.remove(handle);
	m_Resources.erase(handle->GetResource()->VGetFileName());
}

bool cResCache::MakeRoom(unsigned int iSize)
{
	if(iSize > m_iCacheSize)
	{
		Log_Write_L1(ILogger::LT_DEBUG, cString(100, "File size %d greater than cache size %d",iSize, m_iCacheSize));
		return false;
	}

	while(iSize > (m_iCacheSize - m_iTotalMemoryAllocated))
	{
		Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Cache needs to be freed to make space"));
		if(m_lru.empty())
		{
			return false;
		}
		 FreeOneResource();
	}
	return true;
}


char * cResCache::Allocate(unsigned int iSize)
{
	if(!MakeRoom(iSize))
	{
		return NULL;
	}
	char * pBuffer = DEBUG_NEW char[iSize];
	if(pBuffer)
	{	
		m_iTotalMemoryAllocated += iSize;
		Log_Write_L1(ILogger::LT_DEBUG, cString(300, "Allocating Memory. File Size : %u KB. Currently using %u KB (%0.2f MB) out of %u MB in cache", iSize/KILOBYTE, m_iTotalMemoryAllocated/KILOBYTE, (float)m_iTotalMemoryAllocated/MEGABYTE, m_iCacheSize/MEGABYTE));

	}
	return pBuffer;
}


void cResCache::FreeOneResource()
{
	ResHandleList::const_iterator itr = m_lru.end();
	
	itr--;
	shared_ptr<IResHandle> handle = *itr;
	m_lru.pop_back();
	m_Resources.erase(handle->GetResource()->VGetFileName());
	Log_Write_L1(ILogger::LT_DEBUG, cString(100, "Removed file %s from cache", handle->GetResource()->VGetFileName().GetData()));
}

void cResCache::MemoryHasBeenFreed(unsigned int iSize)
{
	m_iTotalMemoryAllocated -= iSize;
	Log_Write_L1(ILogger::LT_DEBUG, cString(300, "Freeing Memory. File Size : %u KB. Currently using %u KB (%0.2f MB) out of %u MB in cache", iSize/KILOBYTE, m_iTotalMemoryAllocated/KILOBYTE, (float)m_iTotalMemoryAllocated/MEGABYTE, m_iCacheSize/MEGABYTE));
}

IResCache * IResCache::CreateResourceCache(const int iSizeInMB, const Base::cString & strFileName)
{
	cResCache * pResCache = DEBUG_NEW cResCache(iSizeInMB, DEBUG_NEW cResourceZipFile(strFileName));
	return pResCache;

}
cResourceZipFile::cResourceZipFile(const Base::cString & resFileName) 
: m_pZipFile(NULL)
, m_strResFileName(resFileName) 
{ 
}

cResourceZipFile::~cResourceZipFile()
{
	SAFE_DELETE(m_pZipFile);
}

bool cResourceZipFile::Open()
{
	m_pZipFile = IZipFile::CreateZipFile();
	if(m_pZipFile)
	{
		return m_pZipFile->Init(m_strResFileName);
	}
	return false;
}

int cResourceZipFile::GetResourceSize(const IResource &r)
{
	int iSize = 0;
	tOptional<int> resNum = m_pZipFile->Find(r.VGetFileName());
	if(resNum.IsValid())
	{
		iSize = m_pZipFile->GetFileLen(*resNum);
	}
	return iSize;
}

void cResourceZipFile::GetResource(const IResource &r, char *buffer)
{
	int iSize = 0;
	tOptional<int> resNum = m_pZipFile->Find(r.VGetFileName());
	if(resNum.IsValid())
	{
		iSize = m_pZipFile->GetFileLen(*resNum);
		m_pZipFile->ReadFile(*resNum, buffer);
	}
}