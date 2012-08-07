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
#include "EntityManager.hxx"
#include "MessageDispatchManager.hxx"

using namespace Utilities;
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

	ILogger::GetInstance()->StartConsoleWin(80,60, "");

	if(!IResourceChecker::GetInstance()->CheckMemory(32, 64) 
		|| !IResourceChecker::GetInstance()->CheckHardDisk(6) 
		|| !IResourceChecker::GetInstance()->CheckCPUSpeedinMhz(266))
	{
		PostQuitMessage(0);
		return -1;
	}

	ILogger::GetInstance()->CreateHeader();

	bool bFullScreen = false;
#ifndef _DEBUG
		bFullScreen = true;
#endif
	HWND hwnd;

	pGame = IGame::CreateGame("MPong");

#ifndef MULTIPLEINSTANCES
	if (!IResourceChecker::GetInstance()->IsOnlyInstance(pGame->VGetGameTitle()))
	{
		PostQuitMessage(0);
		return -1;
	}
#endif

	if(bFullScreen)
	{
		pGame->VOnInitialization(hInstance, nCmdShow, bFullScreen, 1024, 768, hwnd);
	}
	else
	{
		pGame->VOnInitialization(hInstance, nCmdShow, bFullScreen, 1024, 720, hwnd);
	}

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
	IEntityManager::Destroy();
	IMessageDispatchManager::Destroy();
	ILogger::Destroy();
}