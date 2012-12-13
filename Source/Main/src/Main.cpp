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
#include "Checks.hxx"
#include "BaseApp.hxx"
#include "Game/Game.hxx"

using namespace Utilities;
using namespace GameBase;
using namespace Base;

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

	ILogger::GetInstance()->StartConsoleWin(80,60, "");

	if(!IResourceChecker::GetInstance()->CheckMemory(32, 64) 
		|| !IResourceChecker::GetInstance()->CheckHardDisk(6) 
		|| !IResourceChecker::GetInstance()->CheckCPUSpeedinMhz(266))
	{
		PostQuitMessage(0);
		return -1;
	}

	ILogger::GetInstance()->CreateHeader();

	cString strOptionsFileName;
#ifdef _DEBUG
	strOptionsFileName = "OptionsDebug.ini";
#else
	strOptionsFileName = "OptionsRetail.ini";
#endif

	pGame = IGame::CreateGame("Game");
	pGame->VOnInitialization(hInstance, nCmdShow, strOptionsFileName);
	pGame->VRun();
	Cleanup() ;

	return 0;
}

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
// Cleanup
// ***************************************************************
void Cleanup() 
{
	SAFE_DELETE(pGame);

	IResourceChecker::Destroy();
	ILogger::Destroy();
}