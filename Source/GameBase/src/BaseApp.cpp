// ***************************************************************
//  BaseApp   version:  1.0   Ankur Sheel  date: 2011/10/19
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "BaseApp.h"
#include "MainWindow.hxx"

using namespace GameBase;
using namespace Base;

GAMEBASE_API void GameBase::cBaseApp::OnInit(const HINSTANCE hInstance, const int nCmdShow,const bool bFullScreen, const int iFullScreenWidth, const int iFullScreenHeight, HWND & outHwnd)
{
	outHwnd = IMainWindow::GetInstance()->VOnInitialization(hInstance, nCmdShow, this, bFullScreen, iFullScreenWidth, iFullScreenHeight);

	if(outHwnd == NULL)
	{
		PostQuitMessage(0) ;
		return;
	}
}
