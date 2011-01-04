// ***************************************************************
//  MainWindow   version:  1.0   Ankur Sheel  date: 04/28/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef mywinmainclass_h__
#define mywinmainclass_h__

#include "GraphicEngineDefines.h"

class IBaseApp;

class IMainWindow
{
public:
	GRAPHIC_API virtual HWND Init( const HINSTANCE &hInstance, const int &nCmdShow, const char * const lpWindowTitle,const int iFullScreenWidth, const int iFullScreenHeight, IBaseApp * const pGameApp) = 0;
	GRAPHIC_API virtual void Run() = 0;
	GRAPHIC_API static IMainWindow * TheWindow();
	GRAPHIC_API virtual void DisplayFPS() = 0;
	GRAPHIC_API virtual float GetElapsedTime() const = 0;
	GRAPHIC_API virtual float GetRunningTime() const = 0;
	GRAPHIC_API virtual void LockKey( const DWORD dwKey ) = 0;
	GRAPHIC_API virtual long GetAbsXMousePos() const = 0;
	GRAPHIC_API virtual long GetAbsYMousePos() const= 0;
};
GRAPHIC_API IMainWindow * CreateMyWindow();
#endif // mywinmainclass_h__