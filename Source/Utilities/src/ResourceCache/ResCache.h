#pragma once

#include "ResCache.hxx"
#include <list>
#include <map>
#include <memory>

namespace Base
{
	class cString;
}

namespace Utilities
{

	class cResHandle;
	class cResCache;

	class cResource
	{
	public:
		UTILITIES_API cResource(const Base::cString & strFileName);
		virtual cResHandle * CreateHandle(const char * pBuffer, unsigned int size, cResCache * pResCache);

	public:
		Base::cString m_strFileName;
	};

	class cResHandle
	{
	public:
		cResHandle(cResource & resource, char * pBuffer, unsigned int iSize, cResCache * pResCache);
		virtual ~cResHandle();
		virtual void Load(IResourceFile * pFile);
		UTILITIES_API unsigned int GetSize() const;
		char * GetBuffer() const;

	protected:
		cResource		m_Resource;
		char *			m_pBuffer;
		unsigned int	m_iSize;
		cResCache *		m_pResCache;

	private:
		friend class cResCache;
	};

	//LRU
	typedef std::list<std::tr1::shared_ptr <cResHandle> > ResHandleList;
	typedef std::map<Base::cString, std::tr1::shared_ptr <cResHandle> > ResHandleMap;

	class cResCache
	{
	public:
		UTILITIES_API cResCache(unsigned int iCacheSizeInMB, const IResourceFile * pResFile);
		UTILITIES_API ~cResCache();
		UTILITIES_API bool Init();
		UTILITIES_API std::tr1::shared_ptr<cResHandle> GetHandle(cResource & r);
		void Flush();

	protected:
		std::tr1::shared_ptr<cResHandle> Find(const cResource & r);
		const void Update(std::tr1::shared_ptr<cResHandle> handle);
		std::tr1::shared_ptr<cResHandle> Load(cResource & r) ; 
		void Free(std::tr1::shared_ptr<cResHandle> handle);
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
		UTILITIES_API cResourceZipFile(const Base::cString & resFileName);
		virtual ~cResourceZipFile();

		virtual bool Open();
		virtual int GetResourceSize(const cResource &r);
		virtual void GetResource(const cResource &r, char *buffer);

	private:
		IZipFile *	m_pZipFile;
		Base::cString m_strResFileName;

	};

}