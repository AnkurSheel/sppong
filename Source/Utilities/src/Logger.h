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
#ifndef Logger_h__
#define Logger_h__

#include "Logger.hxx"

namespace Base
{
	class cString;
}

namespace Utilities
{
	class IXMLFileIO;
}

namespace Utilities
{
	class cLogger
		: public ILogger
		, public Base::cNonCopyable
	{
	private:
		void StartConsoleWin(const int ciWidth, const int ciHeight, const Base::cString & cfName);
		void WriteLogEntry(LogType eLogEntryType, const Base::cString & strSourceFile, const Base::cString & strFunction, int iSourceLine, const Base::cString & strMessage);
		void CreateHeader();

	private:
		cLogger();
		~cLogger();
		void Close();
		void LogTypeToString(const LogType eLogEntryType, Base::cString & str );
		void Log(const LogType eLogEntryType, const Base::cString & str);
		void SetConsoleTextColor(const LogType eLogEntryType);

	private:
		FILE *			m_fStdOut;
		HANDLE			m_hStdOut;
		IXMLFileIO	*	m_fXml;
		static int		m_iCurrentId;
		static cLogger * s_pLogger;

	private:
		friend static ILogger * ILogger::GetInstance();
		friend static void ILogger::Destroy();
	};
}
#endif // Logger_h__