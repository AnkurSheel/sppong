// ***************************************************************
//  Macros   version:  1.0   Ankur Sheel  date: 2011/04/12
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Macros_h__
#define Macros_h__

#define DegtoRad(x)(x* D3DX_PI/180)

#define SAFE_DELETE(p) \
{ \
	if(p) \
	{ \
		delete (p) ; \
		(p)=NULL ; \
	} \
}

#define SAFE_DELETE_ARRAY(p) \
{ \
	if(p) \
	{ \
		delete [](p) ; \
		(p)=NULL ; \
	} \
}

#define SAFE_RELEASE(p) \
{ \
	if(p) \
	{ \
		(p)->Release() ; \
		(p)=NULL ; \
	} \
}

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
	if(ILogger::TheLogger()) \
	{ \
		ILogger::TheLogger()->WriteLogEntry( \
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

const int  KILOBYTE = 1024;
const int  MEGABYTE = KILOBYTE * KILOBYTE;

const int MAX_FILENAME_WIDTH = 256;
const int MAX_PATH_WIDTH = 260;

#ifdef _DEBUG
#define DEBUG_NEW   new( _NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif 

typedef DWORD TICK;

const unsigned int SCREEN_REFRESH_RATE(1000/60);

#endif // Macros_h__
