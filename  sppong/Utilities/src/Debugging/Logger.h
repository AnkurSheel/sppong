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


class cLogger
{
	FILE*	m_fStdOut;
	HANDLE	m_hStdOut;

	cLogger(const cLogger&){}
	cLogger operator =(const cLogger&){}

public:
	UTILITIES_API cLogger();
	UTILITIES_API void StartConsoleWin(const int ciWidth = 80, const int ciHeight = 40, const char* const cfName = NULL);
	UTILITIES_API int Log(const char * const  lpFmt, ...);
};

#endif // Logger_h__