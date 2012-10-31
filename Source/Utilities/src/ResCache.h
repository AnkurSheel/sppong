// ***************************************************************
//  ResCache   version:  1.0   Ankur Sheel  date: 2011/04/01
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef ResCache_h__
#define ResCache_h__

#include "ResCache.hxx"

namespace Base
{
	class cString;
}

namespace Utilities
{

	class cResHandle;
	class cResCache;

	class cResource 
		: public IResource
	{
	public:
		cResource(const Base::cString & strFileName);
		IResHandle * CreateHandle(const char * pBuffer, unsigned int size, IResCache * pResCache);
		Base::cString GetFileName() const;
	public:
		Base::cString m_strFileName;
	};

	class cResHandle
		: public IResHandle
	{
	public:
		cResHandle(cResource & resource, char * pBuffer, unsigned int iSize, IResCache * pResCache);
		virtual~ cResHandle();
		void Load(IResourceFile * pFile);
		unsigned int GetSize() const;
		char * GetBuffer() const;
		const IResource * GetResource() const;

	protected:
		cResource 		m_Resource;
		char *			m_pBuffer;
		unsigned int	m_iSize;
		IResCache *		m_pResCache;

	private:
		friend class cResCache;
	};

	//LRU
	typedef std::list<shared_ptr <IResHandle> > ResHandleList;
	typedef std::map<Base::cString, shared_ptr <IResHandle> > ResHandleMap;

	class cResCache
		: public IResCache
	{
	public:
		cResCache(unsigned int iCacheSizeInMB, const IResourceFile * pResFile);
		~cResCache();
		bool Init();
		shared_ptr<IResHandle> GetHandle(IResource & r);
		void Flush();

	protected:
		shared_ptr<IResHandle> Find(const IResource & r);
		const void Update(shared_ptr<IResHandle> handle);
		shared_ptr<IResHandle> Load(IResource & r) ; 
		void Free(shared_ptr<IResHandle> handle);
		bool MakeRoom(unsigned int iSize);
		char * Allocate(unsigned int iSize);
		void FreeOneResource();
		void MemoryHasBeenFreed(unsigned int iSize);

	protected:
		ResHandleList m_lru;
		ResHandleMap  m_Resources;
		IResourceFile * m_pFile;
		unsigned int m_iCacheSize;
		unsigned int m_iTotalMemoryAllocated;

	private:
		friend class cResHandle;
	};

	class IZipFile;

	class cResourceZipFile : public IResourceFile
	{
	public:
		cResourceZipFile(const Base::cString & resFileName);
		virtual ~cResourceZipFile();

		virtual bool Open();
		virtual int GetResourceSize(const IResource &r);
		virtual void GetResource(const IResource &r, char *buffer);

	private:
		IZipFile *	m_pZipFile;
		Base::cString m_strResFileName;

	};
}
#endif // ResCache_h__