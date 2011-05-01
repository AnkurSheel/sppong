// ***************************************************************
//  Main   version:  1.0   Ankur Sheel  date: 2011/02/16
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "Main.h"
#include "MainWindow.hxx"
#include "Game\Game.hxx"
#include "Checks.hxx"

using namespace Utilities;
using namespace Graphics;
using namespace Base;
using namespace GameBase;

static IBaseApp * pGame = NULL;
// ***************************************************************
// Main function
// ***************************************************************
int WINAPI WinMain(const HINSTANCE hInstance, 
				   HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, 
				   int nCmdShow)
{

	CheckForMemoryLeaks() ;

	ILogger::TheLogger()->StartConsoleWin(80,60, "");

	pGame = IGame::CreateGame();

#ifndef MULTIPLEINSTANCES
	if (!IResourceChecker::TheResourceChecker()->IsOnlyInstance(pGame->GetGameTitle()))
	{
		PostQuitMessage(0);
		return -1;
	}
#endif

	if(!IResourceChecker::TheResourceChecker()->CheckMemory(32, 64) 
		|| !IResourceChecker::TheResourceChecker()->CheckHardDisk(6) 
		|| !IResourceChecker::TheResourceChecker()->CheckCPUSpeedinMhz(266))
	{
		PostQuitMessage(0);
		return -1;
	}

	ILogger::TheLogger()->CreateHeader();

	HWND	hwnd ;

	int iWidth = GetSystemMetrics(SM_CXSCREEN);
	int iHeight = GetSystemMetrics(SM_CYSCREEN);

	//Initialize the window class
	hwnd = IMainWindow::TheWindow()->Init( hInstance, nCmdShow, pGame->GetGameTitle(), iWidth, iHeight);

	if(hwnd == NULL)
	{
		PostQuitMessage(0) ;
	}
	else
	{
		IMainWindow::TheWindow()->Run();
	}
	
	Cleanup() ;

	return 0;
}
// ***************************************************************

// ***************************************************************
// Checks for memory leaks
// ***************************************************************
void CheckForMemoryLeaks() 
{
#ifdef	_DEBUG
	// Get Current flag
	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) ; 

	// Turn on leak-checking bit
	flag |= (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF) ; 

	// Set flag to the new value
	_CrtSetDbgFlag(flag) ; 
#endif	_DEBUG
}
// ***************************************************************

// ***************************************************************
// Cleanup
// ***************************************************************
void Cleanup() 
{
	SAFE_DELETE(pGame);

	if(ILogger::TheLogger())
		ILogger::TheLogger()->Destroy();

	if (IResourceChecker::TheResourceChecker())
		IResourceChecker::TheResourceChecker()->Destroy();

	if (IMainWindow::TheWindow())
		IMainWindow::TheWindow()->Destroy();
}
// ***************************************************************