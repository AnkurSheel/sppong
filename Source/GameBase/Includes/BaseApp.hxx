// ***************************************************************
//  BaseApp   version:  1.0   Ankur Sheel  date: 04/30/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef BaseApp_hxx__
#define BaseApp_hxx__

#include "GameBaseDefines.h"

namespace Base
{
	class cString;
}

namespace GameBase
{
	struct AppMsg
	{
		HWND	m_hWnd;
		UINT	m_uMsg;
		WPARAM	m_wParam;
		LPARAM	m_lParam;
	};

	class IBaseApp
	{
	public:
		virtual ~IBaseApp(){}
		virtual void Render(TICK tickCurrent, float fElapsedTime) = 0;
		virtual void OnInit(const HINSTANCE hInstance, const int nCmdShow,const bool bFullscreen) = 0;
		virtual void ProcessInput(const long xDelta,const long yDelta, const long zDelta, const bool* const pbPressedKeys, const bool* const pbMouseButtons, const float fElapsedTime ) = 0;
		virtual void Restart() = 0;
		virtual Base::cString GetGameTitle() = 0; 
		virtual void OnUpdate() = 0;
		GAMEBASE_API static void OnMsgProc(const AppMsg & msg){}
		GAMEBASE_API virtual void Run() = 0;
	};
}
#endif // BaseApp_hxx__