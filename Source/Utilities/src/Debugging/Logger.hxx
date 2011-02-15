// ***************************************************************
//  Logger   version:  1.0   Ankur Sheel  date: 2011/02/16
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Logger_hxx__
#define Logger_hxx__

#include "UtilitiesDefines.h"

namespace Utilities
{
	class ILogger
	{
	public:
		enum LogType
		{
			LT_UNKNOWN = -1,
			LT_DEBUG,
			LT_ERROR,
			LT_WARNING,
			LT_COMMENT,
			LT_EVENT,
			LT_GAME_MESSAGE,
			LT_TOTAL
		};
	public:
		virtual ~ILogger(){}
		UTILITIES_API virtual void StartConsoleWin(const int ciWidth = 80, const int ciHeight = 40, const char* const cfName = NULL) = 0;
		UTILITIES_API virtual void CreateHeader() = 0;
		UTILITIES_API static ILogger * TheLogger();
		UTILITIES_API void Destroy();
		UTILITIES_API virtual void WriteLogEntry(LogType eLogEntryType, const char * const strSourceFile, const char * const strFunction, int iSourceLine, const char * const strMessage ) = 0;
	};
}
#endif // Logger_h__