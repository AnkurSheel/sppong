// ***************************************************************
//  Logger   version:  1.0   Ankur Sheel  date: 2011/01/04
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "Logger.h"
#include <string>


class cLogger
	: public ILogger
{
private:
	cLogger(const cLogger&){}
	cLogger operator =(const cLogger&){}

public:
	cLogger();
	void StartConsoleWin(const int ciWidth = 80, const int ciHeight = 40, const char* const cfName = NULL);
	int Log(const char * const  lpFmt, ...);

private:
	FILE*	m_fStdOut;
	HANDLE	m_hStdOut;

};

using namespace std;

// ***************************************************************
// Constructor
// ***************************************************************
cLogger::cLogger()
: m_fStdOut(NULL)
 ,m_hStdOut(NULL) 
{

}
// ***************************************************************

// ***************************************************************
// creates the console Window
// ***************************************************************
void cLogger::StartConsoleWin( const int ciWidth /*= 80*/,
							  const int ciHeight /*= 40*/, 
							  const char* const cfName /*= NULL*/ )
{
#ifdef _DEBUG
	AllocConsole();
	SetConsoleTitle("Console Logger");
	m_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD co = {ciWidth, ciHeight};

	SetConsoleScreenBufferSize(m_hStdOut, co);

	if (cfName)
	{
		fopen_s(&m_fStdOut, cfName, "w");
	}
#endif
}

int cLogger::Log( const char * const lpFmt, ... )
{
#ifdef _DEBUG
	//TCHAR s[256];
	char s[256];
	va_list argptr;
	int cnt;

	va_start(argptr, lpFmt);
	//cnt = _vstprintf_s(s, lpFmt, argptr);
	cnt = vsprintf_s(s, lpFmt, argptr);
	va_end(argptr);

	DWORD dwCharsWritten;

	if(m_hStdOut)
	{
		//WriteConsole(m_hStdOut, s, (DWORD)_tcslen(s), &dwCharsWritten, NULL);
		WriteConsole(m_hStdOut, s, (DWORD)strlen(s), &dwCharsWritten, NULL);
	}
	if (m_fStdOut)
	{
		//_ftprintf(m_fStdOut, s);
		fprintf(m_fStdOut, s);
	}
	return cnt;
#else
	return 0;
#endif
}
// ***************************************************************

// ***************************************************************
// Creates a logger
// ***************************************************************
ILogger * ILogger::CreateLogger()
{
	cLogger * pLogger = DEBUG_NEW cLogger();
	return pLogger;
}
// ***************************************************************
