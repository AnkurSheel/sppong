// ***************************************************************
//  MainWindow   version:  1.0   Ankur Sheel  date: 2011/02/16
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef MainWindow_h__
#define MainWindow_h__

#include "GraphicEngineDefines.h"

namespace Graphics
{
	class IBaseApp;
}

namespace Graphics
{
	class IMainWindow
	{
	public:
		virtual ~IMainWindow(){}
		GRAPHIC_API virtual HWND Init( const HINSTANCE &hInstance, const int &nCmdShow, const char * const lpWindowTitle,const int iFullScreenWidth, const int iFullScreenHeight, IBaseApp * const pGameApp) = 0;
		GRAPHIC_API virtual void Run() = 0;
		GRAPHIC_API static IMainWindow * TheWindow();
		GRAPHIC_API virtual void DisplayFPS() = 0;
		GRAPHIC_API virtual float GetElapsedTime() const = 0;
		GRAPHIC_API virtual float GetRunningTime() const = 0;
		GRAPHIC_API virtual void LockKey( const DWORD dwKey ) = 0;
		GRAPHIC_API virtual long GetAbsXMousePos() const = 0;
		GRAPHIC_API virtual long GetAbsYMousePos() const= 0;
		GRAPHIC_API virtual void Destroy() = 0;
		GRAPHIC_API static void CreateMyWindow();
	};
}
#endif // MainWindow_h__