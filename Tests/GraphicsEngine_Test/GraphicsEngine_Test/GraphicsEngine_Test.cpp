// Utilities_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Logger.hxx"
#include "MainWindow.hxx"
#include "Timer.hxx"
#include "DxBase.hxx"
#include "Input.hxx"

using namespace Graphics;
using namespace Utilities;
using namespace Base;

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

	int iWidth = GetSystemMetrics(SM_CXSCREEN);
	int iHeight = GetSystemMetrics(SM_CYSCREEN);


	bool bFullScreen = false;
#ifndef _DEBUG
	bFullScreen = true;
#endif
	//Initialize the window class
	HWND hwnd = IMainWindow::TheWindow()->Init( hInstance, nCmdShow, "Graphics Engine Test", iWidth, iHeight, bFullScreen);

	if (hwnd == NULL)
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Could not initialize window"));
		PostQuitMessage(0);
	}

	Log_Write_L1(ILogger::LT_COMMENT, cString(100, "Window initialized"));
	
	Graphics::IInput * pInput;
	pInput= IInput::CreateInputDevice();
	pInput->Init(hInstance, hwnd, iWidth, iHeight);

	HRESULT hr;

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
			hr = IDXBase::GetInstance()->BeginRender();
			if (SUCCEEDED(hr))
			{
				pInput->DetectKeys();

				const bool* const pbPressedKeys = pInput->GetPressedKeys();
				if (pbPressedKeys[DIK_ESCAPE])
				{
					// lock the ESC key
					pInput->LockKey(DIK_ESCAPE) ;

					PostQuitMessage(0);
				}

				pInput->DetectMouseMovement();

				IDXBase::GetInstance()->EndRender(hr);
			}
		}
	}

	if (IMainWindow::TheWindow())
	{
		IMainWindow::TheWindow()->Destroy();
		Log_Write_L1(ILogger::LT_COMMENT, cString(100, "Window destroyed"));
	}

	if (ILogger::TheLogger())
	{
		ILogger::TheLogger()->Destroy();
	}
	
	SAFE_DELETE(pInput);
#ifdef _DEBUG
	system("pause");
#endif // _DEBUG
}

