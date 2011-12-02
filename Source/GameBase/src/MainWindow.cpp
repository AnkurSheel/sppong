// ***************************************************************
//  MainWindow   version:  1.0   Ankur Sheel  date: 04/28/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "MainWindow.h"
#include "DxBase.hxx"
#include "BaseApp.hxx"
#include "Logger.hxx"
#include "ResourceManager.hxx"
#include "Constants.h"
#include "Structures.h"

using namespace Utilities;
using namespace Graphics;
using namespace Base;
using namespace GameBase;

// ***************************************************************
// Constructor
// ***************************************************************
cMainWindow::cMainWindow()
: m_Hwnd(NULL)
, m_hInstance(NULL)
, m_iClientHeight(0)
, m_iClientWidth(0)
, m_iFullScreenHeight(0)
, m_iFullScreenWidth(0)
, m_pGame(NULL)
{
}
// ***************************************************************

// ***************************************************************
// Destructor
// ***************************************************************
cMainWindow::~cMainWindow()
{
}
// ***************************************************************

// ***************************************************************
// Initializes, Registers and creates the window.
// Returns a handle to the created window.
// ***************************************************************
HWND cMainWindow::Init( const HINSTANCE &hInstance, const int &nCmdShow, IBaseApp * const pGame, const bool bFullScreen )
{
	HWND hWnd ;
	m_hInstance = hInstance;

	m_iFullScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	m_iFullScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	//Register the Window Class
	RegisterWin();

	m_pGame = pGame;

	//Create the Window
	if (pGame)
	{
		hWnd = CreateMyWindow(nCmdShow, pGame->GetGameTitle(), bFullScreen) ;
	}
	else
	{
		Log_Write_L1(ILogger::LT_ERROR, "No Game object");
	}
	

	OnCreateDevice(hInstance,hWnd, bFullScreen);

	return hWnd;
}
// ***************************************************************

// ***************************************************************
// Registers the window
// ***************************************************************
void cMainWindow::RegisterWin()
{
	WNDCLASSEX		wc ;

	wc.cbSize = sizeof(WNDCLASSEX) ;
	wc.style = 0 ;
	wc.lpfnWndProc = (WNDPROC)cMainWindow::StaticWndProc ;
	wc.cbClsExtra = 0 ;
	wc.cbWndExtra = 0 ;
	wc.hInstance = m_hInstance ;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION) ;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW) ;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1) ;
	wc.lpszMenuName = NULL ;
	wc.lpszClassName = "Window" ;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION) ;
	if(!RegisterClassEx(&wc))
	{
		Log_Write_L1(ILogger::LT_ERROR, "Window Registration Failed");
		exit(0) ;
	}
}
// ***************************************************************

// ***************************************************************
// Creates the window
// ***************************************************************
HWND cMainWindow::CreateMyWindow( const int &nCmdShow, const cString & lpWindowTitle, const bool bFullScreen)
{
	if(bFullScreen)
	{
		// create the window in full screen mode
		m_Hwnd = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			"Window",
			lpWindowTitle.GetData(),
			WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE,
			0, 0, 
			m_iFullScreenWidth,m_iFullScreenHeight,
			NULL, 
			NULL, 
			m_hInstance, 
			this) ;
	}
	else
	{
		// create the window in windowed mode
		m_Hwnd = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			"Window",
			lpWindowTitle.GetData(),
			WS_OVERLAPPEDWINDOW ,
			0, 0, 
			CW_USEDEFAULT, CW_USEDEFAULT,
			NULL, 
			NULL, 
			m_hInstance, 
			this) ;
	}

	if(m_Hwnd == NULL)
	{
		Log_Write_L1(ILogger::LT_ERROR, "Window Creation Failed");
		return NULL ;
	}

	GetWinRect() ;
	ShowWindow(m_Hwnd, nCmdShow) ;
	UpdateWindow(m_Hwnd) ;

	return m_Hwnd ;
}
// ***************************************************************

// ***************************************************************
// Gets the window rectangle
// ***************************************************************
void cMainWindow::GetWinRect()
{
	RECT	clientRect, windowRect ;

	GetClientRect(m_Hwnd,&clientRect) ;
	GetWindowRect(m_Hwnd,&windowRect) ;
	m_iClientWidth = (clientRect.right - clientRect.left) ;
	m_iClientHeight = (clientRect.bottom - clientRect.top) ;
	m_iTopPos = (windowRect.top - clientRect.top) ;
	m_iLeftPos = (windowRect.left - clientRect.left) ;
}
// ***************************************************************

// ***************************************************************
// Window procedure to handle the window messages
// ***************************************************************
LRESULT CALLBACK cMainWindow::WndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT		ps ;
	HDC				hdc ;

	switch(uMsg)
	{
	case WM_PAINT:
		hdc = BeginPaint (hwnd, &ps) ;
		EndPaint (hwnd, &ps) ;
		return 0 ;

	case WM_CLOSE:
		OnDestroyDevice();
		return 0 ;

	case WM_DESTROY:
		OnDestroyDevice();
		return 0 ;

	case WM_LBUTTONDBLCLK:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MBUTTONDBLCLK:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEMOVE:
	case WM_RBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	//case WM_KEYDOWN:
	//case WM_KEYUP:
	case WM_CHAR:
		Graphics::AppMsg msg;
		msg.m_hWnd = hwnd;
		msg.m_uMsg = uMsg;
		msg.m_wParam = wParam;
		msg.m_lParam = lParam;

		if (m_pGame)
		{
			m_pGame->OnMsgProc(msg);
		}
		return 0;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam) ;
	}
}
// ***************************************************************

// ***************************************************************
// Static Window procedure used to fill the WNDCLASSEX struct
// ***************************************************************
LRESULT CALLBACK cMainWindow::StaticWndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	if ( msg == WM_CREATE )
	{
		SetWindowLongPtr( hwnd, GWLP_USERDATA, (LONG)((CREATESTRUCT *)lParam)->lpCreateParams );
	}

	cMainWindow *targetApp = (cMainWindow*)GetWindowLongPtr( hwnd, GWLP_USERDATA );

	if ( targetApp )
	{
		return targetApp->WndProc( hwnd, msg, wParam, lParam );
	}

	return DefWindowProc( hwnd, msg, wParam, lParam ); 
}
// ***************************************************************

// ***************************************************************
// Function called when the application quits
// ***************************************************************
void cMainWindow::OnDestroyDevice()
{
	// release the graphic object
	if (IDXBase::GetInstance())
	{
		IDXBase::GetInstance()->Destroy();
	}
	
	IResourceManager::TheResourceManager()->OnDestroyDevice();

	ReleaseCapture() ;
	PostQuitMessage(0) ;
}
// ***************************************************************

// ***************************************************************
// Function called when the device is created
// ***************************************************************
void cMainWindow::OnCreateDevice( const HINSTANCE hInst, const HWND hWnd, const bool bFullScreen )
{
	// initialize DirectX
	IDXBase::GetInstance()->Init(hWnd, TAN, bFullScreen);
	IResourceManager::TheResourceManager()->Init();
	SetForegroundWindow(m_Hwnd);

}
// ***************************************************************

// ***************************************************************
// Move the window
// ***************************************************************
void cMainWindow::MoveWin()
{
	MoveWindow(m_Hwnd,m_iLeftPos,m_iTopPos,m_iClientWidth,m_iClientHeight,true) ;
}
// ***************************************************************

int cMainWindow::GetClientWindowHeight()
{
	return m_iClientHeight;
}
// ***************************************************************

int cMainWindow::GetClientWindowWidth()
{
	return m_iClientWidth;
}
// ***************************************************************

void cMainWindow::Destroy()
{
	DestroyWindow(m_Hwnd);

	delete this;
	s_pWindow = NULL;
}
// ***************************************************************

// ***************************************************************
// returns an instance of the class
// ***************************************************************
IMainWindow * IMainWindow::TheWindow()
{
	if(!s_pWindow)
		s_pWindow = DEBUG_NEW cMainWindow();
	return s_pWindow;
}
// ***************************************************************