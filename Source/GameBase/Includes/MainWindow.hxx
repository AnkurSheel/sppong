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

#include "GameBaseDefines.h"

namespace GameBase
{
	class IBaseApp;
}

namespace GameBase
{
	class IMainWindow
	{
	public:
		virtual ~IMainWindow(){}
		GAMEBASE_API virtual HWND Init( const HINSTANCE & hInstance, const int &nCmdShow, IBaseApp * const pGame, const bool bFullScreen) = 0;
		GAMEBASE_API static IMainWindow * TheWindow();
		GAMEBASE_API virtual void Destroy() = 0;
		GAMEBASE_API virtual int GetClientWindowHeight() const = 0;
		GAMEBASE_API virtual int GetClientWindowWidth() const = 0;
		GAMEBASE_API virtual void ToggleFullScreen() = 0;

	};
}
#endif // MainWindow_h__

