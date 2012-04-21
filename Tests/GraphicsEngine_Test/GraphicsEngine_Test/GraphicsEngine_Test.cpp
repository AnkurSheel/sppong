// Utilities_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Logger.hxx"
#include "MainWindow.hxx"
#include "Timer.hxx"
#include "DxBase.hxx"
#include "Input.hxx"
#include "Game.h"
#include "BaseControl.hxx"

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
	ILogger::TheLogger()->StartConsoleWin(80,60, "Log.txt");

	bool bFullScreen = false;
#ifndef _DEBUG
	bFullScreen = true;
#endif

	cGame * pGame = new cGame();

	HWND hWnd = pGame-> VOnInitialization(hInstance, nCmdShow, bFullScreen, 1024, 768);

	Log_Write_L1(ILogger::LT_COMMENT, cString(100, "Window initialized"));
	
	//Graphics::IInput * pInput;
	//pInput= IInput::CreateInputDevice();
	//pInput->Init(hInstance, hWnd, iWidth, iHeight);

	MSG Msg;
	PeekMessage(&Msg, NULL, 0, 0, PM_NOREMOVE) ;
	// run till completed
	while (Msg.message!=WM_QUIT)
	{
		// is there a message to process?
		if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
		{
			// dispatch the message
			TranslateMessage(&Msg) ;
			DispatchMessage(&Msg) ;
		}
		else
		{
			//No message to process?
			// Then do your game stuff here
			HRESULT hr = IDXBase::GetInstance()->VIsAvailable() ;

			if(hr == D3DERR_DEVICELOST || hr == D3DERR_DEVICENOTRESET)
			{
				if(hr == D3DERR_DEVICELOST)
				{
					Sleep(50);
				}
				else 
				{
					if(hr == D3DERR_DEVICENOTRESET) 
					{
						pGame->VOnLostDevice();
						hr = IDXBase::GetInstance()->VOnResetDevice() ;
						pGame->VOnResetDevice();
					}
				}
			}

			if(SUCCEEDED(hr))
			{
				hr = IDXBase::GetInstance()->VBeginRender();
			}
			if (SUCCEEDED(hr))
			{
				pGame->VRun();

				/*pInput->DetectKeys();

				const bool* const pbPressedKeys = pInput->GetPressedKeys();
				if (pbPressedKeys[DIK_ESCAPE])
				{
					// lock the ESC key
					pInput->LockKey(DIK_ESCAPE) ;

					PostQuitMessage(0);
				}

				pInput->DetectMouseMovement();*/

				IDXBase::GetInstance()->VEndRender(hr);
			}
		}
	}

	if (IMainWindow::GetInstance())
	{
		IMainWindow::GetInstance()-> VOnDestroy();
		Log_Write_L1(ILogger::LT_COMMENT, cString(100, "Window destroyed"));
	}

	//SAFE_DELETE(pInput);

	SAFE_DELETE(pGame);

	if (ILogger::TheLogger())
	{
		ILogger::TheLogger()->Destroy();
	}

#ifdef _DEBUG
	system("pause");
#endif // _DEBUG
}

