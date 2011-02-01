// ***************************************************************
//  Logger   version:  1.0   Ankur Sheel  date: 2011/01/04
//  -------------------------------------------------------------
// 2011/01/04 : based on 
//	     		http://archive.gamedev.net/reference/programming/features/xmltech/default.asp 
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "Logger.h"
#include <string>
#include <time.h>
#include "FileIO/XMLFileIO.h"

class cLogger
	: public ILogger
{
private:
	cLogger(const cLogger&){}
	cLogger operator =(const cLogger&){}

public:
	cLogger();
	~cLogger();
	void StartConsoleWin(const int ciWidth = 80, const int ciHeight = 40, const char* const cfName = NULL);
	int Log(const char * const  lpFmt, ...);
	void Close();
private:
	FILE*	m_fStdOut;
	HANDLE	m_hStdOut;
	cXMLFileIO	m_fXml;
};

static cLogger * s_pLogger = NULL;

using namespace std;

// ***************************************************************
// Constructor
// ***************************************************************
cLogger::cLogger()
: m_fStdOut(NULL)
 ,m_hStdOut(NULL) 
{
}

cLogger::~cLogger()
{
	if (m_fStdOut)
	{
		fclose(m_fStdOut);
	}
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
#endif
	if (cfName)
	{
		fopen_s(&m_fStdOut, cfName, "w");
	}
	m_fXml.Init("RunTimeLog");
	m_fXml.AddNode("RunTimeLog", "LogHeader", "");
	m_fXml.AddNode("RunTimeLog", "LogEvents", "");
}

int cLogger::Log( const char * const lpFmt, ... )
{
	char s[256];
	char strtime[100];
	va_list argptr;
	int cnt;

	va_start(argptr, lpFmt);
	cnt = vsprintf_s(s, lpFmt, argptr);
	va_end(argptr);

	time_t currentTime;
	time(&currentTime );
	ctime_s(strtime, 100, &currentTime);
	strtime[24] = ' '; // remove the '/n' from the time string

#ifdef _DEBUG
	DWORD dwCharsWritten;
	if(m_hStdOut)
	{
		WriteConsole(m_hStdOut, strtime, (DWORD)strlen(s), &dwCharsWritten, NULL);
		WriteConsole(m_hStdOut, s, (DWORD)strlen(s), &dwCharsWritten, NULL);
	}
#endif
	if (m_fStdOut)
	{
		fprintf(m_fStdOut, strtime);
		fprintf(m_fStdOut, s);
	}
	return cnt;
}
// ***************************************************************

void cLogger::Close()
{
	s_pLogger->m_fXml.Save("log.xml");
}
// ***************************************************************

// ***************************************************************
// Creates a logger
// ***************************************************************
void ILogger::CreateLogger()
{
	s_pLogger = DEBUG_NEW cLogger();
}

ILogger * ILogger::TheLogger()
{
	return s_pLogger;
}
// ***************************************************************

void ILogger::Destroy()
{
	s_pLogger->Close();
	delete this;
}
