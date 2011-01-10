// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers


// TODO: reference additional headers your program requires here
#ifndef _DEBUG
//#define WINDOWED
#endif


#define STRSAFE_NO_CB_FUNCTIONS
#define NULLCHAR '\0'

#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif

#define DIRECTINPUT_VERSION 0x0800

#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
//#include <tchar.h>
#include <mmsystem.h>
//#include <atlstr.h>
#include <tchar.h>
#include <list>
//#include <strsafe.h>
#include <crtdbg.h>
#include <DxErr.h> //For DXGetErrorString9
#include <dinput.h>
#include "constants.h"
#include "Macros.h"

using namespace std;

#ifdef _DEBUG
#define DEBUG_NEW   new( _NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif 