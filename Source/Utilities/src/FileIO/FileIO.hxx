#pragma once

#include "UtilitiesDefines.h"

namespace Base
{
	class cString;
}

namespace Utilities
{
	class IFileIO
	{
	public:
		UTILITIES_API virtual ~IFileIO(){}
		UTILITIES_API virtual bool Open(const Base::cString & strFileName) = 0;
		UTILITIES_API virtual bool Close() = 0;
		UTILITIES_API virtual Base::cString ReadAll() = 0;
		UTILITIES_API virtual Base::cString Read(size_t size) = 0;
		UTILITIES_API virtual Base::cString GetBuffer() const = 0;
		
		UTILITIES_API static  IFileIO * CreateUserFile();
	};
}