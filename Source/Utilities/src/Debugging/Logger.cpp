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
#include <time.h>
#include "FileIO/XMLFileIO.h"
#include <stdlib.h>

namespace Utilities
{
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
		void WriteLogEntry(LogType eLogEntryType, const char * const strSourceFile, const char * const strFunction, int iSourceLine, const char * const strMessage);

	private:
		void LogTypeToString( LogType eLogEntryType, char * str );

	private:
		FILE *			m_fStdOut;
		HANDLE			m_hStdOut;
		IXMLFileIO	*	m_fXml;
		static int		m_iCurrentId;

	};


	static cLogger * s_pLogger = NULL;
}
using namespace Utilities;

int cLogger::m_iCurrentId = 1;
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
	SAFE_DELETE(m_fXml);
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
	m_fXml = IXMLFileIO::CreateXMLFile();
	m_fXml->Init("RunTimeLog", "RunTimeLog", "BasicXSLT.xsl");
	m_fXml->AddNode("RunTimeLog", "LogHeader", "LogHeader", "");
	m_fXml->AddNode("RunTimeLog", "LogEvents", "LogEvents", "");

#if SYSTEM_DEBUG_LEVEL == 3
	m_fXml->AddNode("LogHeader", "OutputLevel", "OutputLevel", "Extra Comprehensive debugging information (Level 3)");
#elif SYSTEM_DEBUG_LEVEL == 2
	m_fXml->AddNode("LogHeader", "OutputLevel", "OutputLevel", "Comprehensive debugging information (Level 2)");
#elif SYSTEM_DEBUG_LEVEL == 1
	m_fXml->AddNode("LogHeader", "OutputLevel", "OutputLevel", "Retail debugging information (Level 1)");
#else
	m_fXml->AddNode("LogHeader", "OutputLevel", "OutputLevel", "No debugging information (Level 0)");
#endif

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
		fflush(m_fStdOut); 
	}
	return cnt;
}
// ***************************************************************

void cLogger::Close()
{
	s_pLogger->m_fXml->Save("log.xml");
}
// ***************************************************************

void cLogger::WriteLogEntry( LogType eLogEntryType, const char * const strSourceFile, const char * const strFunction, int iSourceLine, const char * const strMessage )
{
	char strEvent[100];
	sprintf_s(strEvent, 100, "LogEvent%d", m_iCurrentId);
	m_fXml->AddNode("LogEvents", strEvent, "LogEvent", "");
	m_fXml->AddAttribute(strEvent,"id", m_iCurrentId);
	char str[100];
	LogTypeToString(eLogEntryType, str);
	m_fXml->AddNode(strEvent, "Type", "Type", str);

	time_t currentTime;
	time(&currentTime );
	ctime_s(str, 100, &currentTime);
	str[24] = ' '; // remove the '/n' from the time string

	m_fXml->AddNode(strEvent, "TimeIndex", "TimeIndex", str);

	m_fXml->AddNode(strEvent, "File", "File", strSourceFile);
	m_fXml->AddNode(strEvent, "Function", "Function", strFunction);

	_itoa_s(iSourceLine, str, 100, 10);
	m_fXml->AddNode(strEvent, "LineNumber", "LineNumber", str);
	m_fXml->AddNode(strEvent, "Message", "Message", strMessage);
	m_iCurrentId++;
}

void cLogger::LogTypeToString( LogType eLogEntryType, char * str )
{
	switch(eLogEntryType)
	{
	case LT_DEBUG: 
		strcpy_s(str,100, "Debug");
		break;
	case LT_ERROR:
		strcpy_s(str,100, "Error");
		break;
	case LT_WARNING: 
		strcpy_s(str,100, "Warning");
		break;
	case LT_COMMENT: 
		strcpy_s(str,100, "Comment");
		break;
	case LT_EVENT: 
		strcpy_s(str,100, "Event");
		break;
	case LT_GAME_MESSAGE: 
		strcpy_s(str,100, "Game Message");
		break;
	case LT_UNKNOWN:
	default:
		strcpy_s(str,100, "UNKNOWN");
		break;
	}
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
