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
#include "Logger.hxx"
#include "MainWindow.hxx"

using namespace GameBase;
using namespace Base;

void GameBase::cBaseApp::OnInit( const HINSTANCE hInstance, const int nCmdShow, const bool bFullScreen, HWND & outHwnd )
{
	outHwnd = IMainWindow::TheWindow()->Init(hInstance, nCmdShow, this, bFullScreen);

	if(outHwnd == NULL)
	{
		PostQuitMessage(0) ;
		return;
	}
}
