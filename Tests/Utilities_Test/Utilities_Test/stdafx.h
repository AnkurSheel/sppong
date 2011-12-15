// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


// TODO: reference additional headers your program requires here
#include "windows.h"
#include "myString.h"
#include <crtdbg.h>

#include "Includes.h"

#ifdef _DEBUG
#define DEBUG_NEW   new( _NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif 
