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

namespace Utilities
{
	class IFileInput
	{
	public:
		UTILITIES_API virtual ~IFileInput(){}
		UTILITIES_API virtual bool Open(const Base::cString & strFileName, const std::ios_base::openmode mode) = 0;
		UTILITIES_API virtual bool Close() = 0;
		UTILITIES_API virtual const BYTE * const ReadAll() = 0;
		UTILITIES_API virtual const BYTE * const Read(std::streamoff size) = 0;
		UTILITIES_API virtual void ReadLine() = 0;
		UTILITIES_API virtual bool IsEOF() = 0;
		UTILITIES_API virtual const BYTE * const GetBuffer() const = 0;
		UTILITIES_API virtual std::streamoff VGetFileSize() const = 0;
		UTILITIES_API static  IFileInput * CreateInputFile();
	};
}
#endif // FileInput_h__