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
int WINAPI WinMain(const HINSTANCE hInstance, HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, int nCmdShow)
{
	cLogger log;
	log.StartConsoleWin();
	//log.Log(_T("%s %d"),__WFILE__, __LINE__);
	log.Log("%s %d",__FILE__, __LINE__);

	HWND	hwnd ;

	CheckForMemoryLeaks() ;

	pGame= new cGame();

	//Initialize the window class
	hwnd = cMainWindow::GetInstance().Init( hInstance, nCmdShow, "MPong", 1280, 764, (cBaseApp*)pGame);

	if(hwnd == NULL)
	{
		PostQuitMessage(0) ;
	}
	else
	{
		cMainWindow::GetInstance().Run();
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