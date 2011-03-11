#pragma once

#include "UtilitiesDefines.h"
#include <map>
#include "FileIO/FileIO.h"

namespace Base
{
	class cString;
}

namespace Utilities
{
	class cZipFile :
		public cFileIO
	{
	private:
		typedef std::map<std::string, int> ZipContentsMap;		// maps path to a zip content id
	public:
		UTILITIES_API cZipFile();
		UTILITIES_API virtual ~cZipFile();

		UTILITIES_API bool Init(const Base::cString & resFileName);
		UTILITIES_API void End();

		UTILITIES_API int GetNumFiles() const;
		UTILITIES_API Base::cString GetFilename(int i) const;
		UTILITIES_API int GetFileLen(int i) const;
		UTILITIES_API bool ReadFile(int i, void *pBuf);

		// Added to show multi-threaded decompression
		UTILITIES_API bool ReadLargeFile(int i, void *pBuf, void (*callback)(int, bool &));

		UTILITIES_API int Find(const char *path) const;

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
}


