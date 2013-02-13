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
#include "Checks.hxx"

using namespace Utilities;
using namespace Base;
using namespace std;

int cLogger::m_iCurrentId = 1;
cLogger * Utilities::cLogger::s_pLogger = NULL;

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
	Close();
	SAFE_DELETE(m_fXml);
}
// ***************************************************************

// ***************************************************************
// creates the console Window
// ***************************************************************
void cLogger::StartConsoleWin( const int ciWidth, const int ciHeight, const cString & cfName /*= NULL*/ )
{
#ifdef _DEBUG
	m_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(m_hStdOut == NULL && AllocConsole() != 0)
	{
		SetConsoleTitle("Console Logger");
		m_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		FILE *fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
	}
	COORD co = {ciWidth, ciHeight};
	SetConsoleScreenBufferSize(m_hStdOut, co);

	SMALL_RECT windowSize = {0, 0, ciWidth-1, ciHeight-1};
	SetConsoleWindowInfo( m_hStdOut, TRUE, &windowSize);
#endif
	if (!cfName.IsEmpty())
	{
		fopen_s(&m_fStdOut, cfName.GetData(), "w");
	}
	m_fXml = IXMLFileIO::CreateXMLFile();
	m_fXml->VInitializeForSave("RunTimeLog", "BasicXSLT.xsl");
	m_fXml->VAddElement("RunTimeLog", "LogHeader", "", "");
	m_fXml->VAddElement("RunTimeLog", "LogEvents", "", "");

}
void cLogger::CreateHeader()
{
	if(!m_fXml)
		return;
#if SYSTEM_DEBUG_LEVEL == 3
	m_fXml->VAddElement("LogHeader", "OutputLevel", "", "Extra Comprehensive debugging information (Level 3)");
#elif SYSTEM_DEBUG_LEVEL == 2
	m_fXml->VAddElement("LogHeader", "OutputLevel", "", "Comprehensive debugging information (Level 2)");
#elif SYSTEM_DEBUG_LEVEL == 1
	m_fXml->VAddElement("LogHeader", "OutputLevel", "", "Retail debugging information (Level 1)");
#else
	m_fXml->VAddElement("LogHeader", "OutputLevel", "", "No debugging information (Level 0)");
#endif
	m_fXml->VAddElement("LogHeader", "Session", "", "");
	m_fXml->VAddElement("Session", "Configuration", "", "");
	m_fXml->VAddElement("Configuration", "Memory", "", "");
	m_fXml->VAddElement("Memory", "AvailablePhysical", "", cString(30, "%d", IResourceChecker::GetInstance()->GetAvailablePhysicalMemory()));

	m_fXml->VAddElement("Memory", "TotalPhysical", "", cString(30, "%d", IResourceChecker::GetInstance()->GetTotalPhysicalMemory()));

	m_fXml->VAddElement("Memory", "AvailableVirtual", "", cString(30, "%d", IResourceChecker::GetInstance()->GetAvailableVirtualMemory()));

	m_fXml->VAddElement("Memory", "TotalVirtual", "", cString(30, "%d", IResourceChecker::GetInstance()->GetTotalVirtualMemory()));

	m_fXml->VAddElement("Memory", "AvailableHardDiskSpace", "", cString(30, "%d", IResourceChecker::GetInstance()->GetAvailableHardDiskSpace()));

	m_fXml->VAddElement("Memory", "TotalHardDiskSpace", "", cString(30, "%d", IResourceChecker::GetInstance()->GetTotalHardDiskSpace()));

	m_fXml->VAddElement("Configuration", "Processor", "", "");
	m_fXml->VAddElement("Processor", "ClockSpeed", "", cString(30, "%d", IResourceChecker::GetInstance()->GetCPUSpeed()));

	m_fXml->VAddElement("Processor", "Family", "", IResourceChecker::GetInstance()->GetCPUBrand());

	m_fXml->VAddElement("Session", "Started", "", "");

	time_t currentTime;
	time(&currentTime );
	m_fXml->VAddElement("Started", "Time", "", cString::TimeToString(currentTime));

	m_fXml->VAddElement("Configuration", "Environment", "", IResourceChecker::GetInstance()->GetOSVersion());
}

void cLogger::Log(const LogType eLogEntryType, const Base::cString & str)
{
	char strtime[100];
	time_t currentTime;
	time(&currentTime );
	ctime_s(strtime, 100, &currentTime);
	strtime[24] = ' ';

#ifdef _DEBUG
	SetConsoleTextColor(eLogEntryType);
	cout << strtime << str << "\n";
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
	m_fXml->VSave("log.xml");
	if (m_fStdOut)
	{
		fclose(m_fStdOut);
	}
}
// ***************************************************************

void cLogger::WriteLogEntry(const LogType eLogEntryType, const cString & strSourceFile, const cString & strFunction, int iSourceLine, const cString & strMessage )
{
	Log(eLogEntryType, strMessage);
	if(!m_fXml)
		return;

	cString strEvent = m_fXml->VAddElement("LogEvents", "LogEvent", cString(20, "%d", m_iCurrentId), "");

	cString str;
	LogTypeToString(eLogEntryType, str);
	m_fXml->VAddElement(strEvent, "Type", "", str);

	time_t currentTime;
	time(&currentTime );

	m_fXml->VAddElement(strEvent, "TimeIndex", "", cString::TimeToString(currentTime));

	m_fXml->VAddElement(strEvent, "File", "", strSourceFile);
	m_fXml->VAddElement(strEvent, "Function", "", strFunction);

	m_fXml->VAddElement(strEvent, "LineNumber", "", cString(20, "%d", iSourceLine));
	m_fXml->VAddElement(strEvent, "Message", "", strMessage);
	m_iCurrentId++;
}
// ***************************************************************

void cLogger::SetConsoleTextColor(const LogType eLogEntryType)
{
	switch(eLogEntryType)
	{
	case LT_DEBUG: 
		SetConsoleTextAttribute(m_hStdOut, FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
		break;
	case LT_ERROR:
		SetConsoleTextAttribute(m_hStdOut, FOREGROUND_RED|FOREGROUND_INTENSITY);
		break;
	case LT_WARNING: 
		SetConsoleTextAttribute(m_hStdOut, FOREGROUND_RED| FOREGROUND_GREEN|FOREGROUND_INTENSITY);
		break;
	case LT_COMMENT: 
		SetConsoleTextAttribute(m_hStdOut, FOREGROUND_GREEN|FOREGROUND_INTENSITY);
		break;
	case LT_EVENT: 
		SetConsoleTextAttribute(m_hStdOut, FOREGROUND_BLUE| FOREGROUND_GREEN|FOREGROUND_INTENSITY);
		break;
	case LT_GAME_MESSAGE: 
		SetConsoleTextAttribute(m_hStdOut, FOREGROUND_BLUE| FOREGROUND_INTENSITY);
		break;
	case LT_UNKNOWN:
	default:
		//set color to white
		SetConsoleTextAttribute(m_hStdOut, FOREGROUND_BLUE| FOREGROUND_RED | FOREGROUND_GREEN|FOREGROUND_INTENSITY);
		break;
	}
}
// ***************************************************************

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

ILogger * ILogger::GetInstance()
{
	if(cLogger::s_pLogger == NULL)
		cLogger::s_pLogger = DEBUG_NEW cLogger();
	return cLogger::s_pLogger;

}
// ***************************************************************

void ILogger::Destroy()
{
	SAFE_DELETE(cLogger::s_pLogger);
}
