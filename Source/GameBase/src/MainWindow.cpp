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
: m_bFullScreen(false)
, m_Hwnd(NULL)
, m_hInstance(NULL)
, m_uClientHeight(0)
, m_uClientWidth(0)
, m_uFullScreenHeight(0)
, m_uFullScreenWidth(0)
, m_pGame(NULL)
, m_dwFullScreenStyle(WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE)
, m_dwWindowedStyle(WS_OVERLAPPEDWINDOW)
{
	ZeroMemory( &m_wp, sizeof( WINDOWPLACEMENT ) );
}
// ***************************************************************

cMainWindow::cMainWindow( const cMainWindow& )
: m_dwFullScreenStyle(WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE)
, m_dwWindowedStyle(WS_OVERLAPPEDWINDOW)

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
	m_bFullScreen = bFullScreen;
	m_uFullScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	m_uFullScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	//Register the Window Class
	RegisterWin();

	m_pGame = pGame;

	//Create the Window
	if (pGame)
	{
		hWnd = CreateMyWindow(nCmdShow, pGame->GetGameTitle()) ;
	}
	else
	{
		Log_Write_L1(ILogger::LT_ERROR, "No Game object");
	}
	
	OnCreateDevice(hInstance,hWnd);
	m_wp.length = sizeof(WINDOWPLACEMENT);
	GetWindowPlacement(m_Hwnd, &m_wp);

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
HWND cMainWindow::CreateMyWindow( const int &nCmdShow, const cString & lpWindowTitle)
{
	DWORD dwStyle; 
	if(m_bFullScreen)
	{
		dwStyle = m_dwFullScreenStyle;
	}
	else
	{
		dwStyle = m_dwWindowedStyle;
	}
		
	m_Hwnd = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			"Window",
			lpWindowTitle.GetData(),
			dwStyle,
			CW_USEDEFAULT, 0, 
			m_uFullScreenWidth,m_uFullScreenHeight,
			NULL, 
			NULL, 
			m_hInstance, 
			this) ;
	
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
	m_uClientWidth = (clientRect.right - clientRect.left) ;
	m_uClientHeight = (clientRect.bottom - clientRect.top) ;
	m_uTopPos = (windowRect.top - clientRect.top) ;
	m_uLeftPos = (windowRect.left - clientRect.left) ;
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
	case WM_KEYDOWN:
	case WM_KEYUP:
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
void cMainWindow::OnCreateDevice( const HINSTANCE hInst, const HWND hWnd)
{
	// initialize DirectX
	IDXBase::GetInstance()->Init(hWnd, TAN, m_bFullScreen);
	IResourceManager::TheResourceManager()->Init();
	SetForegroundWindow(m_Hwnd);

}
// ***************************************************************

// ***************************************************************
// Move the window
// ***************************************************************
void cMainWindow::MoveWin()
{
	MoveWindow(m_Hwnd,m_uLeftPos,m_uTopPos,m_uClientWidth,m_uClientHeight,true) ;
}
// ***************************************************************

void cMainWindow::Destroy()
{
	DestroyWindow(m_Hwnd);

	delete this;
	s_pWindow = NULL;
}
// ***************************************************************

void GameBase::cMainWindow::ToggleFullScreen()
{
	m_bFullScreen = !m_bFullScreen;

	if (m_bFullScreen)
	{
		// Save Current location/size
		GetWindowPlacement(m_Hwnd, &m_wp);

		//Going to Full Screen mode
		SetWindowLongPtr(m_Hwnd, GWL_STYLE, m_dwFullScreenStyle);

		// hide the window
		ShowWindow(m_Hwnd, SW_HIDE);
	}
	else
	{
		SetWindowLongPtr(m_Hwnd, GWL_STYLE, m_dwWindowedStyle);
	}

	IDXBase::GetInstance()->ToggleFullScreen();

	m_pGame->OnLostDevice();
	IDXBase::GetInstance()->ResetDevice() ;
	m_pGame->OnResetDevice();
	if (!m_bFullScreen)
	{
		SetWindowPlacement(m_Hwnd, &m_wp);
		Log_Write_L3(ILogger::LT_DEBUG, cString(100, "top %d, bottom %d, left %d, right %d", m_wp.rcNormalPosition.top, m_wp.rcNormalPosition.bottom, m_wp.rcNormalPosition.left, m_wp.rcNormalPosition.right));
		Log_Write_L3(ILogger::LT_DEBUG, cString(100, "Max X %d, Max Y %d", m_wp.ptMaxPosition.x, m_wp.ptMaxPosition.y));
		Log_Write_L3(ILogger::LT_DEBUG, cString(100, "Min X %d, Min Y %d", m_wp.ptMinPosition.x, m_wp.ptMinPosition.y));
		Log_Write_L3(ILogger::LT_DEBUG, cString(100, "Flags %d", m_wp.flags));
	}

	if (!IsWindowVisible(m_Hwnd))
	{
		ShowWindow(m_Hwnd, SW_SHOW);
	}

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