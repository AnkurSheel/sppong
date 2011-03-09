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
		UTILITIES_API virtual ~IFileIO(){ Destroy(); }
		UTILITIES_API virtual bool OpenAndRead(const Base::cString & strFileName) = 0;
		UTILITIES_API virtual bool Close() = 0;
		UTILITIES_API virtual Base::cString GetBuffer() = 0;
		
		UTILITIES_API static  IFileIO * CreateFile();
		UTILITIES_API void  Destroy();
	};
}