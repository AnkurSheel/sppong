// *************************************************************************
//  FileOutput   version:  1.0   Ankur Sheel  date: 2012/11/07
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************
#ifndef FileOutput_hxx__
#define FileOutput_hxx__

#include "UtilitiesDefines.h"

namespace Base
{
	class cString;
}

namespace Utilities
{
	class IFileOutput
	{
	public:
		UTILITIES_API virtual ~IFileOutput(){}
		UTILITIES_API virtual bool Open(const Base::cString & strFileName, const std::ios_base::openmode mode) = 0;
		UTILITIES_API virtual bool Close() = 0;
		UTILITIES_API virtual void WriteLine(const Base::cString & strLine) = 0;
		
		UTILITIES_API static  IFileOutput * CreateOutputFile();
	};
}
#endif // FileOutput_hxx__