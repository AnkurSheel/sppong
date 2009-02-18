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

class cLogger
{
	FILE*	m_fStdOut;
	HANDLE	m_hStdOut;

	cLogger(const cLogger&){}
	cLogger operator =(const cLogger&){}

public:
	UTILITIES_API cLogger();
	UTILITIES_API void StartConsoleWin(const int ciWidth = 80, const int ciHeight = 40, const char* const cfName = NULL);
	UTILITIES_API int Log(LPCTSTR lpFmt, ...);
};

#endif // Logger_h__