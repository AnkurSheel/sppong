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

#define TOSTRING(x) #x

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

#endif // Macros_h__
