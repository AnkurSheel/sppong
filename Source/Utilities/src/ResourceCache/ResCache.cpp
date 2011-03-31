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
#include "FileIO/ZipFile.hxx"

using namespace Utilities;
using namespace Base;
	

cResource::cResource(const cString & strFileName)
: m_strFileName(strFileName)
{
}

cResHandle * cResource::CreateHandle(const char * pBuffer, unsigned int size, cResCache *pResCache)
{
	return DEBUG_NEW cResHandle((*this), (char *)pBuffer, size, pResCache);
}

cResHandle::cResHandle(cResource & resource, char * pBuffer, unsigned int iSize, cResCache * pResCache)
: m_Resource(resource)
, m_pBuffer(pBuffer)
, m_iSize(iSize)
, m_pResCache(pResCache)
{
}

cResHandle::~cResHandle()
{
	SAFE_DELETE(m_pBuffer);
	m_pResCache->MemoryHasBeenFreed(m_iSize);
}

void cResHandle::Load(IResourceFile * pFile)
{
	return pFile->GetResource(m_Resource, m_pBuffer);
}

unsigned int cResHandle::GetSize() const
{
	return m_iSize;
}

char * cResHandle::GetBuffer() const
{
	return m_pBuffer;
}

using namespace std::tr1;

cResCache::cResCache(unsigned int iCacheSizeInMB, const IResourceFile * pResFile)
: m_iCacheSize(iCacheSizeInMB * 1024 * 1024)
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

shared_ptr<cResHandle> cResCache::GetHandle(cResource & r)
{
	shared_ptr<cResHandle> handle(Find(r));
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
		shared_ptr<cResHandle> handle = *(m_lru.begin());
		Free(handle);
		m_lru.pop_front();
	}
}

shared_ptr<cResHandle> cResCache::Find(const cResource & r)
{
	ResHandleMap::iterator itr = m_Resources.find(r.m_strFileName);
	if(itr == m_Resources.end())
	{
		return shared_ptr<cResHandle>(); 
	}

	return (*itr).second;
}

const void cResCache::Update(shared_ptr<cResHandle> handle)
{
	m_lru.remove(handle);
	m_lru.push_front(handle);
}

shared_ptr<cResHandle> cResCache::Load(cResource & r)
{
	int iSize = m_pFile->GetResourceSize(r);
	char * pBuffer = Allocate(iSize);
	if(pBuffer == NULL)
	{
		return shared_ptr<cResHandle>();
	}

	shared_ptr<cResHandle> handle(r.CreateHandle(pBuffer, iSize, this));

	handle->Load(m_pFile);

	m_lru.push_front(handle);
	m_Resources[r.m_strFileName] = handle;

	return handle;
}

void cResCache::Free(shared_ptr<cResHandle> handle)
{
	m_lru.remove(handle);
	m_Resources.erase(handle->m_Resource.m_strFileName);
}

bool cResCache::MakeRoom(unsigned int iSize)
{
	if(iSize > m_iCacheSize)
	{
		return false;
	}

	while(iSize > (m_iCacheSize - m_iTotalMemoryAllocated))
	{
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
	}

	return pBuffer;
}


void cResCache::FreeOneResource()
{
	ResHandleList::iterator itr = m_lru.end();
	
	itr--;
	shared_ptr<cResHandle> handle = *itr;
	m_lru.pop_back();
	m_Resources.erase(handle->m_Resource.m_strFileName);
}

void cResCache::MemoryHasBeenFreed(unsigned int iSize)
{
	m_iTotalMemoryAllocated -= iSize;
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

int cResourceZipFile::GetResourceSize(const cResource &r)
{
	int iSize = 0;
	int resNum = m_pZipFile->Find(r.m_strFileName);
	if(resNum != -1)
	{
		iSize = m_pZipFile->GetFileLen(resNum);
	}
	return iSize;
}

void cResourceZipFile::GetResource(const cResource &r, char *buffer)
{
	int iSize = 0;
	int resNum = m_pZipFile->Find(r.m_strFileName);
	if(resNum != -1)
	{
		iSize = m_pZipFile->GetFileLen(resNum);
		m_pZipFile->ReadFile(resNum, buffer);
	}
}