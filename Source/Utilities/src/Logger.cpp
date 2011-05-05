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
#include "XMLFileIO.hxx"
#include <stdlib.h>
#include "Checks.hxx"

using namespace Utilities;
using namespace Base;

int cLogger::m_iCurrentId = 1;
// ***************************************************************
// Constructor
// ***************************************************************
cLogger::cLogger()
: m_fStdOut(NULL)
, m_hStdOut(NULL) 
, m_fXml(NULL)
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
	if( AllocConsole() != 0)
	{
		SetConsoleTitle("Console Logger");
		m_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

		COORD co = {ciWidth, ciHeight};

		SetConsoleScreenBufferSize(m_hStdOut, co);
	}
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
	if(!m_fXml)
		return;
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
	m_fXml->AddNode("Memory", "AvailablePhysical", "AvailablePhysical", cString(30, "%d", IResourceChecker::TheResourceChecker()->GetAvailablePhysicalMemory()));

	m_fXml->AddNode("Memory", "TotalPhysical", "TotalPhysical", cString(30, "%d", IResourceChecker::TheResourceChecker()->GetTotalPhysicalMemory()));

	m_fXml->AddNode("Memory", "AvailableVirtual", "AvailableVirtual", cString(30, "%d", IResourceChecker::TheResourceChecker()->GetAvailableVirtualMemory()));

	m_fXml->AddNode("Memory", "TotalVirtual", "TotalVirtual", cString(30, "%d", IResourceChecker::TheResourceChecker()->GetTotalVirtualMemory()));

	m_fXml->AddNode("Memory", "AvailableHardDiskSpace", "AvailableHardDiskSpace", cString(30, "%d", IResourceChecker::TheResourceChecker()->GetAvailableHardDiskSpace()));

	m_fXml->AddNode("Memory", "TotalHardDiskSpace", "TotalHardDiskSpace", cString(30, "%d", IResourceChecker::TheResourceChecker()->GetTotalHardDiskSpace()));

	m_fXml->AddNode("Configuration", "Processor", "Processor", "");
	m_fXml->AddNode("Processor", "ClockSpeed", "ClockSpeed", cString(30, "%d", IResourceChecker::TheResourceChecker()->GetCPUSpeed()));

	m_fXml->AddNode("Processor", "Family", "Family", IResourceChecker::TheResourceChecker()->GetCPUBrand());

	m_fXml->AddNode("Session", "Started", "Started", "");

	time_t currentTime;
	time(&currentTime );
	m_fXml->AddNode("Started", "Time", "Time", cString::TimeToString(currentTime));

	m_fXml->AddNode("Configuration", "Environment", "Environment", IResourceChecker::TheResourceChecker()->GetOSVersion());
}

void cLogger::Log(const Base::cString & str)
{
	char strtime[100];
	time_t currentTime;
	time(&currentTime );
	ctime_s(strtime, 100, &currentTime);
	strtime[24] = ' ';

#ifdef _DEBUG
	DWORD dwCharsWritten;
	if(m_hStdOut)
	{
		WriteConsole(m_hStdOut, strtime, (DWORD)strlen(strtime), &dwCharsWritten, NULL);
		WriteConsole(m_hStdOut, str.GetData(), (DWORD)strlen(str.GetData()), &dwCharsWritten, NULL);
		WriteConsole(m_hStdOut, "\n", 1, &dwCharsWritten, NULL);
	}
#endif
	if (m_fStdOut)
	{
		fprintf(m_fStdOut, strtime);
		fprintf(m_fStdOut, str.GetData());
		fprintf(m_fStdOut, "\n");
		fflush(m_fStdOut); 
	}
}
// ***************************************************************

void cLogger::Close()
{
	s_pLogger->m_fXml->Save("log.xml");
}
// ***************************************************************

void cLogger::WriteLogEntry( LogType eLogEntryType, const cString & strSourceFile, const cString & strFunction, int iSourceLine, const cString & strMessage )
{
	Log(strMessage);
	if(!m_fXml)
		return;

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
	s_pLogger = NULL;

}
