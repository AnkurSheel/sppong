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
#include "Logger.hxx"

namespace Utilities
{
	class IXMLFileIO;
}

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