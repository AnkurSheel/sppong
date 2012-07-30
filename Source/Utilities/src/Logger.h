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
	{
	public:
		cLogger();
		~cLogger();
		void StartConsoleWin(const int ciWidth, const int ciHeight, const Base::cString & cfName);
		void Close();
		void WriteLogEntry(LogType eLogEntryType, const Base::cString & strSourceFile, const Base::cString & strFunction, int iSourceLine, const Base::cString & strMessage);
		static void CreateLogger();
		void CreateHeader();

	private:
		cLogger(const cLogger&){}
		cLogger operator =(const cLogger&){}
		void LogTypeToString(const LogType eLogEntryType, Base::cString & str );
		void Log(const LogType eLogEntryType, const Base::cString & str);
		void SetConsoleTextColor(const LogType eLogEntryType);

	private:
		FILE *			m_fStdOut;
		HANDLE			m_hStdOut;
		IXMLFileIO	*	m_fXml;
		static int		m_iCurrentId;
	};

	static cLogger * s_pLogger = NULL;
}
#endif // Logger_h__