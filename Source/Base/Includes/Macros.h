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

const int  KILOBYTE = 1024;
const int  MEGABYTE = KILOBYTE * KILOBYTE;

const int MAX_FILENAME_WIDTH = 256;
const int MAX_PATH_WIDTH = 260;

const int KEYBOARD_KEYS = 256;

#ifdef _DEBUG
#define DEBUG_NEW   new( _NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif 

typedef DWORD TICK;

const unsigned int SCREEN_REFRESH_RATE(1000/60);
const int     MaxInt    = (std::numeric_limits<int>::max)();
const double  MaxDouble = (std::numeric_limits<double>::max)();
const double  MinDouble = (std::numeric_limits<double>::min)();
const float   MaxFloat  = (std::numeric_limits<float>::max)();
const float   MinFloat  = (std::numeric_limits<float>::min)();

const double   Pi        = 3.14159;
const double   TwoPi     = Pi * 2;
const double   HalfPi    = Pi / 2;
const double   QuarterPi = Pi / 4;

inline bool isEqual(const double a, const double b)
{
	if (fabs(a-b) < 1E-12)
	{
		return true;
	}

	return false;
}

inline double DegtoRad(const double x)
{
	return (x * Pi /180);
}
#endif // Macros_h__
