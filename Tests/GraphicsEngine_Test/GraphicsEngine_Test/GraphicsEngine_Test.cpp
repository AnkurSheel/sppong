// Utilities_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BaseApp.hxx"
#include "Game.h"

using namespace Graphics;
using namespace Utilities;
using namespace Base;
using namespace GameBase;

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

int WINAPI WinMain(const HINSTANCE hInstance, 
				   HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, 
				   int nCmdShow)
{
	CheckForMemoryLeaks() ;
	ILogger::GetInstance()->StartConsoleWin(80,60, "Log.txt");

	int * p = DEBUG_NEW int;

	bool bFullScreen = false;
#ifndef _DEBUG
	bFullScreen = true;
#endif
	cString strOptionsFileName;
#ifdef _DEBUG
	strOptionsFileName = "GraphicsTestDebug.ini";
#else
	strOptionsFileName = "GraphicsTestRelease.ini";
#endif
	IBaseApp * pGame = DEBUG_NEW cGame("Graphic Engine Test");

	pGame->VOnInitialization(hInstance, nCmdShow, strOptionsFileName);
	pGame->VRun();
	
	SAFE_DELETE(pGame);
	ILogger::Destroy();
}

