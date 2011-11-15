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

namespace Base
{
	class cString;
}

namespace Utilities
{
	class IResCache;
}
namespace GameBase
{
	class IMainWindow
	{
	public:
		virtual ~IMainWindow(){}
		GAMEBASE_API virtual HWND Init( const HINSTANCE &hInstance, const int &nCmdShow, const Base::cString & lpWindowTitle,const int iFullScreenWidth, const int iFullScreenHeight, const bool bFullScreen) = 0;
		GAMEBASE_API static IMainWindow * TheWindow();
		GAMEBASE_API virtual void Destroy() = 0;
		GAMEBASE_API virtual int GetClientWindowHeight() = 0;
		GAMEBASE_API virtual int GetClientWindowWidth() = 0;

	};
}
#endif // MainWindow_h__

