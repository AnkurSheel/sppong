// ***************************************************************
//  Main   version:  1.0   Ankur Sheel  date: 04/29/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************

#include "stdafx.h"
#include "Main.h"
#include "Essentials\MainWindow.h"
#include "Game\Game.h"
#include "Debugging\logger.h"

cGame *pGame = NULL;	// global ptr to the game

// ***************************************************************
// Main function
// ***************************************************************
int WINAPI WinMain(const HINSTANCE hInstance, 
				   HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, 
				   int nCmdShow)
{
	HWND	hwnd ;

	CheckForMemoryLeaks() ;

	IMainWindow::CreateMyWindow();
	pGame= DEBUG_NEW cGame();

	//Initialize the window class
	hwnd = IMainWindow::TheWindow()->Init( hInstance, nCmdShow, "MPong", 1280, 764, (IBaseApp*)pGame);

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
}
// ***************************************************************