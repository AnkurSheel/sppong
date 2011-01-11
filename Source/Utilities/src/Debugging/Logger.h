// ***************************************************************
//  Logger   version:  1.0   Ankur Sheel  date: 12/30/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Logger_h__
#define Logger_h__

#include "UtilitiesDefines.h"

// code to create wide string version of __FILE__ 
#define WIDEN2(x) L ## x
#define WIDEN(x) WIDEN2(x)
#define __WFILE__ WIDEN(__FILE__)


class ILogger
{
public:
	virtual ~ILogger(){}
	UTILITIES_API virtual void StartConsoleWin(const int ciWidth = 80, const int ciHeight = 40, const char* const cfName = NULL) = 0;
	UTILITIES_API virtual int Log(const char * const  lpFmt, ...) = 0;
	UTILITIES_API static void CreateLogger();
	UTILITIES_API static ILogger * TheLogger();
	UTILITIES_API void Destroy();
};
#endif // Logger_h__