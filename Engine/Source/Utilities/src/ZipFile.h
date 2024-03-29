// ***************************************************************
//  ZipFile   version:  1.0   Ankur Sheel  date: 2011/04/12
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef ZipFile_h__
#define ZipFile_h__

#define ZLIB_WINAPI

#include "ZipFile.hxx"
#include "FileInput.h"

namespace Base
{
	class cString;
	template<class T>
	class tOptional;
}

namespace Utilities
{
	class cZipFile
		: public IZipFile
		, public cFileInput

	{
	private:
		typedef std::map<Base::cString, int> ZipContentsMap;		// maps path to a zip content id

	public:
		cZipFile();
		~cZipFile();

		bool Init(const Base::cString & resFileName);
		void End();

		int GetNumFiles() const;
		Base::cString GetFilename(int i) const;
		int GetFileLen(int i) const;
		bool ReadFile(int i, void *pBuf);

		// Added to show multi-threaded decompression
		bool ReadLargeFile(int i, void *pBuf, void (*callback)(int, bool &));

		Base::tOptional<int> Find(const Base::cString & strPath) const;

	private:

		struct TZipDirHeader;
		struct TZipDirFileHeader;
		struct TZipLocalHeader;

		char * m_pDirData;	// Raw data buffer.
		int  m_nEntries;	// Number of entries.

		// Pointers to the dir entries in pDirData.
		const TZipDirFileHeader **m_papDir;   

		ZipContentsMap m_ZipContentsMap;
	};
#include "Zipfile.inl"
}

#endif // ZipFile_h__
