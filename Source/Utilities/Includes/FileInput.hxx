// ***************************************************************
//  FileInput   version:  1.0   Ankur Sheel  date: 2011/04/12
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef FileInput_hxx__
#define FileInput_hxx__

#include "UtilitiesDefines.h"

namespace Base
{
	class cString;
}

namespace Utilities
{
	class IFileInput
	{
	public:
		UTILITIES_API virtual ~IFileInput(){}
		UTILITIES_API virtual bool Open(const Base::cString & strFileName) = 0;
		UTILITIES_API virtual bool Close() = 0;
		UTILITIES_API virtual Base::cString ReadAll() = 0;
		UTILITIES_API virtual Base::cString Read(size_t size) = 0;
		UTILITIES_API virtual Base::cString GetBuffer() const = 0;
		
		UTILITIES_API static  IFileInput * CreateUserFile();
	};
}
#endif // FileInput_h__