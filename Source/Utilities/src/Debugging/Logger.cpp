// ***************************************************************
//  Logger   version:  1.0   Ankur Sheel  date: 2011/01/04
//  -------------------------------------------------------------
// 2011/01/04 : based on 
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "Logger.h"
#include <time.h>
#include "FileIO/XMLFileIO.hxx"
#include <stdlib.h>
#include "InitialChecks/Checks.hxx"

using namespace Utilities;
using namespace Base;

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
void cLogger::StartConsoleWin( const int ciWidth, const int ciHeight, const cString & cfName /*= NULL*/ )
{
#ifdef _DEBUG
	AllocConsole();
	SetConsoleTitle("Console Logger");
	m_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD co = {ciWidth, ciHeight};

	SetConsoleScreenBufferSize(m_hStdOut, co);
#endif
	if (!cfName.IsEmpty())
	{
		fopen_s(&m_fStdOut, cfName.GetData(), "w");
	}
	m_fXml = IXMLFileIO::CreateXMLFile();
	m_fXml->Init("RunTimeLog", "RunTimeLog", "BasicXSLT.xsl");
	m_fXml->AddNode("RunTimeLog", "LogHeader", "LogHeader", "");
	m_fXml->AddNode("RunTimeLog", "LogEvents", "LogEvents", "");

}
void cLogger::CreateHeader()
{
#if SYSTEM_DEBUG_LEVEL == 3
	m_fXml->AddNode("LogHeader", "OutputLevel", "OutputLevel", "Extra Comprehensive debugging information (Level 3)");
#elif SYSTEM_DEBUG_LEVEL == 2
	m_fXml->AddNode("LogHeader", "OutputLevel", "OutputLevel", "Comprehensive debugging information (Level 2)");
#elif SYSTEM_DEBUG_LEVEL == 1
	m_fXml->AddNode("LogHeader", "OutputLevel", "OutputLevel", "Retail debugging information (Level 1)");
#else
	m_fXml->AddNode("LogHeader", "OutputLevel", "OutputLevel", "No debugging information (Level 0)");
#endif
	m_fXml->AddNode("LogHeader", "Session", "Session", "");
	m_fXml->AddNode("Session", "Configuration", "Configuration", "");
	m_fXml->AddNode("Configuration", "Memory", "Memory", "");
	m_fXml->AddNode("Memory", "AvailablePhysical", "AvailablePhysical", cString(30, "%d", IResourceChecker::TheResourceChecker()->GetAvailablePhysicalMemory()).GetData());

	m_fXml->AddNode("Memory", "TotalPhysical", "TotalPhysical", cString(30, "%d", IResourceChecker::TheResourceChecker()->GetTotalPhysicalMemory()).GetData());

	m_fXml->AddNode("Memory", "AvailableVirtual", "AvailableVirtual", cString(30, "%d", IResourceChecker::TheResourceChecker()->GetAvailableVirtualMemory()).GetData());

	m_fXml->AddNode("Memory", "TotalVirtual", "TotalVirtual", cString(30, "%d", IResourceChecker::TheResourceChecker()->GetTotalVirtualMemory()).GetData());

	m_fXml->AddNode("Memory", "AvailableHardDiskSpace", "AvailableHardDiskSpace", cString(30, "%d", IResourceChecker::TheResourceChecker()->GetAvailableHardDiskSpace()).GetData());

	m_fXml->AddNode("Memory", "TotalHardDiskSpace", "TotalHardDiskSpace", cString(30, "%d", IResourceChecker::TheResourceChecker()->GetTotalHardDiskSpace()).GetData());

	m_fXml->AddNode("Configuration", "Processor", "Processor", "");
	m_fXml->AddNode("Processor", "ClockSpeed", "ClockSpeed", cString(30, "%d", IResourceChecker::TheResourceChecker()->GetCPUSpeed()).GetData());

	m_fXml->AddNode("Processor", "Family", "Family", IResourceChecker::TheResourceChecker()->GetCPUBrand().GetData());

	m_fXml->AddNode("Session", "Started", "Started", "");

	time_t currentTime;
	time(&currentTime );
	m_fXml->AddNode("Started", "Time", "Time", cString::TimeToString(currentTime));

	m_fXml->AddNode("Configuration", "Environment", "Environment", IResourceChecker::TheResourceChecker()->GetOSVersion().GetData());
}

int cLogger::Log( const cString & lpFmt, ... )
{
	char s[256];
	char strtime[100];
	va_list argptr;
	int cnt;

	va_start(argptr, lpFmt);
	cnt = vsprintf_s(s, lpFmt.GetData(), argptr);
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

void cLogger::WriteLogEntry( LogType eLogEntryType, const cString & strSourceFile, const cString & strFunction, int iSourceLine, const cString & strMessage )
{
	cString strEvent(20, "LogEvent%d", m_iCurrentId);
	m_fXml->AddNode("LogEvents", strEvent, "LogEvent", "");
	m_fXml->AddAttribute(strEvent,"id", m_iCurrentId);

	cString str;
	LogTypeToString(eLogEntryType, str);
	m_fXml->AddNode(strEvent, "Type", "Type", str);

	time_t currentTime;
	time(&currentTime );

	m_fXml->AddNode(strEvent, "TimeIndex", "TimeIndex", cString::TimeToString(currentTime));

	m_fXml->AddNode(strEvent, "File", "File", strSourceFile);
	m_fXml->AddNode(strEvent, "Function", "Function", strFunction);

	m_fXml->AddNode(strEvent, "LineNumber", "LineNumber", cString(20, "%d", iSourceLine));
	m_fXml->AddNode(strEvent, "Message", "Message", strMessage);
	m_iCurrentId++;
}

void cLogger::LogTypeToString( LogType eLogEntryType, cString & str )
{
	switch(eLogEntryType)
	{
	case LT_DEBUG: 
		str = "Debug";
		break;
	case LT_ERROR:
		str = "Error";
		break;
	case LT_WARNING: 
		str = "Warning";
		break;
	case LT_COMMENT: 
		str = "Comment";
		break;
	case LT_EVENT: 
		str = "Event";
		break;
	case LT_GAME_MESSAGE: 
		str = "Game Message";
		break;
	case LT_UNKNOWN:
	default:
		str = "UNKNOWN";
		break;
	}
}
// ***************************************************************

// ***************************************************************
// Creates a logger
// ***************************************************************
void cLogger::CreateLogger()
{
	s_pLogger = DEBUG_NEW cLogger();
}

ILogger * ILogger::TheLogger()
{
	if(!s_pLogger)
		cLogger::CreateLogger();
	return s_pLogger;
}
// ***************************************************************

void ILogger::Destroy()
{
	s_pLogger->Close();
	delete this;
}
