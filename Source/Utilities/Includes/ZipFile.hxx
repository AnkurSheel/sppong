#pragma once

#include "UtilitiesDefines.h"

namespace Base
{
	class cString;
	template<class T>
	class tOptional;
}


namespace Utilities
{
	class IZipFile
	{
	public:
		UTILITIES_API virtual ~IZipFile(){}
		UTILITIES_API virtual bool Init(const Base::cString & resFileName) = 0;
		UTILITIES_API virtual void End() = 0;

		UTILITIES_API virtual int GetNumFiles() const = 0;
		UTILITIES_API virtual Base::cString GetFilename(int i) const = 0;
		UTILITIES_API virtual int GetFileLen(int i) const = 0;
		UTILITIES_API virtual bool ReadFile(int i, void *pBuf) = 0;

		UTILITIES_API virtual Base::tOptional<int> Find(const Base::cString & strPath) const = 0;

		UTILITIES_API static IZipFile * CreateZipFile();
	};
}


