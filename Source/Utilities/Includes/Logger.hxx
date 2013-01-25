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

#define TEST

//configure some basic precompilation defines
//0 - no debugging wanted
//1 - very basic debug output
//2 - comprehensive debug output
//3 - all output, and a transcript of all messages
#ifdef TEST
#define SYSTEM_DEBUG_LEVEL 3
#else
#ifdef _DEBUG
//Set the output level for 'DEBUG' builds
#define SYSTEM_DEBUG_LEVEL 2
#else
//Set the output level for 'RELEASE' builds
#define SYSTEM_DEBUG_LEVEL 1
#endif

#endif

#define Log_Write( linetype, linetext )  \
	if(ILogger::GetInstance()) \
	{ \
		ILogger::GetInstance()->WriteLogEntry( \
      (linetype), \
      __FILE__, \
      __FUNCSIG__, \
      __LINE__, \
      (linetext) ); \
	} 

#if SYSTEM_DEBUG_LEVEL == 3
  //enable all macros
  #define Log_Write_L1( linetype, linetext ) Log_Write( linetype, linetext )
  #define Log_Write_L2( linetype, linetext ) Log_Write( linetype, linetext )
  #define Log_Write_L3( linetype, linetext ) Log_Write( linetype, linetext )
      
#elif SYSTEM_DEBUG_LEVEL == 2
  //enable levels 1..2 macros
  #define Log_Write_L1( linetype, linetext ) Log_Write( linetype, linetext )
  #define Log_Write_L2( linetype, linetext ) Log_Write( linetype, linetext )
  #define Log_Write_L3( linetype, linetext )
      
#elif SYSTEM_DEBUG_LEVEL == 1
  //enable level 1 macros
  #define Log_Write_L1( linetype, linetext )  Log_Write( linetype, linetext )
  #define Log_Write_L2( linetype, linetext )
  #define Log_Write_L3( linetype, linetext )
      
#else
  //disable macros
  #define Log_Write_L1( linetype, linetext )
  #define Log_Write_L2( linetype, linetext )
  #define Log_Write_L3( linetype, linetext )
#endif

namespace Base
{
	class cString;
}
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
		UTILITIES_API virtual void StartConsoleWin(const int ciWidth, const int ciHeight, const Base::cString & cfName) = 0;
		UTILITIES_API virtual void CreateHeader() = 0;
		UTILITIES_API static ILogger * GetInstance();
		UTILITIES_API static void Destroy();
		UTILITIES_API virtual void WriteLogEntry(LogType eLogEntryType, const Base::cString & strSourceFile, const Base::cString & strFunction, int iSourceLine, const Base::cString & strMessage) = 0;
	};
}
#endif // Logger_h__