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
, m_iFullScreenHeight(0)
, m_iFullScreenWidth(0)
, m_pGame(NULL)
, m_kdwFullScreenStyle(WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE)
, m_kdwWindowedStyle(WS_OVERLAPPEDWINDOW)
{
	ZeroMemory( &m_wp, sizeof( WINDOWPLACEMENT ) );
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
HWND cMainWindow::Init( const HINSTANCE & hInstance, 
						const int & nCmdShow,
						IBaseApp* const pGame,
						const bool bFullScreen,
						const int iFullScreenWidth,
						const int iFullScreenHeight )
{
	m_hInstance = hInstance;
	m_bFullScreen = bFullScreen;
	m_iFullScreenWidth = iFullScreenWidth;
	m_iFullScreenHeight = iFullScreenHeight;
	if (m_iFullScreenWidth <= 0)
	{
		m_iFullScreenWidth = 1;
		Log_Write_L2(ILogger::LT_ERROR, "Full Screen Width < =0");
	}

	if (m_iFullScreenHeight <= 0)
	{
		m_iFullScreenHeight = 1;
		Log_Write_L2(ILogger::LT_ERROR, "Full Screen Width < =0");
	}

	//Register the Window Class
	RegisterWin();

	SetDisplayResolution();

	m_pGame = pGame;

	cString strGameTitle = "GameTitle";
	//Create the Window
	if (pGame)
	{
		strGameTitle = pGame->GetGameTitle() ;
	}

	CreateMyWindow(nCmdShow, strGameTitle) ;

	OnCreateDevice();

	m_wp.length = sizeof(WINDOWPLACEMENT);

	GetWindowPlacement(m_Hwnd, &m_wp);

	return m_Hwnd;
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
void cMainWindow::CreateMyWindow( const int &nCmdShow, const cString & lpWindowTitle)
{
	DWORD dwStyle; 
	if(m_bFullScreen)
	{
		dwStyle = m_kdwFullScreenStyle;
	}
	else
	{
		dwStyle = m_kdwWindowedStyle;
	}

	RECT windowRect;
	windowRect.left = 0;
	windowRect.top = 0;
	windowRect.right = m_iFullScreenWidth;
	windowRect.bottom = m_iFullScreenHeight;
	AdjustWindowRectEx(&windowRect, dwStyle, false, 0);

	m_Hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"Window",
		lpWindowTitle.GetData(),
		dwStyle,
		CW_USEDEFAULT, 0, 
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL, 
		NULL, 
		m_hInstance, 
		this) ;

	if(m_Hwnd == NULL)
	{
		Log_Write_L1(ILogger::LT_ERROR, "Window Creation Failed");
		PostQuitMessage(0);
	}
	
	ShowWindow(m_Hwnd, nCmdShow) ;
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

	case WM_ACTIVATE:                       
	{
		if (!HIWORD(wParam))
		{
			//active
		}
		else
		{
			//inactive
		}
		return 0;
	}
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
	ChangeDisplaySettings(NULL, 0);
	// release the graphic object
	IDXBase::GetInstance()->Destroy();

	IResourceManager::TheResourceManager()->OnDestroyDevice();

	ReleaseCapture() ;
	PostQuitMessage(0) ;
}
// ***************************************************************

// ***************************************************************
// Function called when the device is created
// ***************************************************************
void cMainWindow::OnCreateDevice()
{
	SetForegroundWindow(m_Hwnd);
	SetFocus(m_Hwnd);

	// initialize DirectX
	IDXBase::GetInstance()->Init(m_Hwnd, TAN, m_bFullScreen);
	IResourceManager::TheResourceManager()->Init();
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

	SetDisplayResolution();

	if (m_bFullScreen)
	{
		// Save Current location/size
		GetWindowPlacement(m_Hwnd, &m_wp);

		//Going to Full Screen mode
		SetWindowLongPtr(m_Hwnd, GWL_STYLE, m_kdwFullScreenStyle);

		// hide the window
		ShowWindow(m_Hwnd, SW_HIDE);
	}
	else
	{
		SetWindowLongPtr(m_Hwnd, GWL_STYLE, m_kdwWindowedStyle);
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

void GameBase::cMainWindow::SetDisplayResolution()
{
	if (m_bFullScreen)
	{
		DEVMODE dmScreenSettings;
		SecureZeroMemory(&dmScreenSettings, sizeof(dmScreenSettings));
		if (!EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmScreenSettings))
		{
			Log_Write_L2(ILogger::LT_DEBUG, "Could not get current display Settings");
			return;
		}
		dmScreenSettings.dmPelsHeight = m_iFullScreenHeight;
		dmScreenSettings.dmPelsWidth = m_iFullScreenWidth;
		dmScreenSettings.dmFields = (DM_PELSWIDTH | DM_PELSHEIGHT);

		if (ChangeDisplaySettings(&dmScreenSettings, CDS_TEST) == DISP_CHANGE_SUCCESSFUL)
		{
			if(ChangeDisplaySettings(&dmScreenSettings, 0) == DISP_CHANGE_SUCCESSFUL)
			{
				Log_Write_L2(ILogger::LT_COMMENT, cString(100, "Resolution set to width %d and height %d", m_iFullScreenWidth, m_iFullScreenHeight));
				return;
			}
		}
		Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Could not set resolution with width %d and height %d", m_iFullScreenWidth, m_iFullScreenHeight));
	}
	ChangeDisplaySettings(NULL, 0);
	return;
}
// ***************************************************************

// ***************************************************************
// returns an instance of the class
// ***************************************************************
IMainWindow * IMainWindow::GetInstance()
{
	if(!s_pWindow)
		s_pWindow = DEBUG_NEW cMainWindow();
	return s_pWindow;
}