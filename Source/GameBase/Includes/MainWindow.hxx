// ***************************************************************
//  MainWindow   version:  1.0   Ankur Sheel  date: 2011/02/16
//  -------------------------------------------------------------
//  Interface for Main Window
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
		: public Base::cNonCopyable
	{
	public:
		virtual ~IMainWindow(){}

		GAMEBASE_API virtual HWND Init( const HINSTANCE & hInstance, 
										const int & nCmdShow, 
										IBaseApp* const pGame, 
										const bool bFullScreen, 
										const int iFullScreenWidth, 
										const int iFullScreenHeight) = 0;
		GAMEBASE_API virtual void Destroy() = 0;
		GAMEBASE_API virtual void ToggleFullScreen() = 0;

		GAMEBASE_API static IMainWindow * GetInstance();
	};
}
#endif // MainWindow_h__

