// *****************************************************************************
//  MainWindow   version:  1.0   Ankur Sheel  date: 04/28/2008
//  ----------------------------------------------------------------------------
//
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
//
// *****************************************************************************
#include "stdafx.h"
#include "MainWindow.h"
#include "GraphicsClass.hxx"
#include "BaseApp.hxx"
#include "Structures.h"
#include "GameOptions.h"

using namespace Utilities;
using namespace Base;
using namespace GameBase;
using namespace Graphics;

static IMainWindow * s_pWindow = NULL;

// *****************************************************************************
cMainWindow::cMainWindow()
: m_Hwnd(NULL)
, m_hInstance(NULL)
, m_pGame(NULL)
, m_kdwFullScreenStyle(WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE)
, m_kdwWindowedStyle(WS_SYSMENU | WS_MINIMIZEBOX | WS_CAPTION)
{
}

// *****************************************************************************
cMainWindow::~cMainWindow()
{
}

// *****************************************************************************
HWND cMainWindow::VOnInitialization( const HINSTANCE & hInstance,
									const int & nCmdShow, IBaseApp * const pGame)
{
	m_hInstance = hInstance;
	RegisterWin();

	m_pGame = pGame;

	cString strGameTitle = "GameTitle";

	if (pGame)
	{
		strGameTitle = pGame->VGetGameTitle() ;
	}

	CreateMyWindow(nCmdShow, strGameTitle) ;

	//Bring the window into the foreground and activates the window
	SetForegroundWindow(m_Hwnd);
	//Set the keyboard focus
	SetFocus(m_Hwnd);

	return m_Hwnd;
}

// *****************************************************************************
void cMainWindow::VToggleFullScreen()
{
	cGameOptions::GameOptions().bFullScreen = !(cGameOptions::GameOptions().bFullScreen);

	if (cGameOptions::GameOptions().bFullScreen)
	{
		//Set style for Full Screen mode
		SetWindowLongPtr(m_Hwnd, GWL_STYLE, m_kdwFullScreenStyle);

		// hide the window
		ShowWindow(m_Hwnd, SW_HIDE);
	}
	else
	{
	    //Set style for Windowed mode
		SetWindowLongPtr(m_Hwnd, GWL_STYLE, m_kdwWindowedStyle);
		
		CalculateWindowRect();
		SetWindowPos(m_Hwnd, HWND_NOTOPMOST,0,0,
			m_windowRect.right - m_windowRect.left,
 			m_windowRect.bottom - m_windowRect.top, 0);
	}
	SetDisplayResolution();

	if (!IsWindowVisible(m_Hwnd))
	{
		ShowWindow(m_Hwnd, SW_SHOW);
	}
	IGraphicsClass::GetInstance()->VSetFullScreenMode(cGameOptions::GameOptions().bFullScreen);
}

// *****************************************************************************
void cMainWindow::RegisterWin()
{
	WNDCLASSEX	wc;

	wc.cbSize = sizeof(WNDCLASSEX) ;
	wc.style = 0 ;
	wc.lpfnWndProc = (WNDPROC)cMainWindow::StaticWndProc ;
	wc.cbClsExtra = 0 ;
	wc.cbWndExtra = 0 ;
	wc.hInstance = m_hInstance ;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO) ;
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW) ;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL ;
	wc.lpszClassName = "Window" ;
	if(!RegisterClassEx(&wc))
	{
		Log_Write_L1(ILogger::LT_ERROR, "Window Registration Failed");
		exit(0) ;
	}
}

// *****************************************************************************
void cMainWindow::CreateMyWindow( const int &nCmdShow, const cString & lpWindowTitle)
{
	DWORD dwStyle;
	
	CalculateWindowRect();

	int x, y, height, width;
	if(cGameOptions::GameOptions().bFullScreen)
	{
		dwStyle = m_kdwFullScreenStyle;
		x = 0;
		y = 0;
		width = cGameOptions::GameOptions().iWidth;
		height = cGameOptions::GameOptions().iHeight;

	}
	else
	{
		dwStyle = m_kdwWindowedStyle;
		x = m_windowRect.left;
		y = m_windowRect.top;
		width = m_windowRect.right - m_windowRect.left;
		height = m_windowRect.bottom - m_windowRect.top;
	}


	m_Hwnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		"Window",
		lpWindowTitle.GetData(),
		dwStyle,
		x,
		y,
		width,
		height,
		NULL,
		NULL,
		m_hInstance,
		this) ; // pass "this" so that staticwndproc can access the non static data

	if(m_Hwnd == NULL)
	{
		Log_Write_L1(ILogger::LT_ERROR, "Window Creation Failed");
		PostQuitMessage(0);
	}

	ShowWindow(m_Hwnd, nCmdShow) ;
}

// *****************************************************************************
LRESULT CALLBACK cMainWindow::StaticWndProc( HWND hwnd, UINT msg, WPARAM wParam,
											LPARAM lParam )
{
	if ( msg == WM_CREATE )
	{
	    // store the this pointer which is passed when we create the window in lparam
	    // lpCreateParams contains the value of the lpParam parameter specified in the function call.
		SetWindowLongPtr( hwnd, GWLP_USERDATA, (LONG)((CREATESTRUCT *)lParam)->lpCreateParams );
	}

    // get the this pointer for this class using GWLP_USERDATA
	cMainWindow *targetApp = (cMainWindow*)GetWindowLongPtr( hwnd, GWLP_USERDATA );

	if ( targetApp )
	{
	    // let our window handle the msg
		return targetApp->WndProc( hwnd, msg, wParam, lParam );
	}

	return DefWindowProc( hwnd, msg, wParam, lParam );
}

// *****************************************************************************
LRESULT CALLBACK cMainWindow::WndProc( HWND hwnd, UINT uMsg, WPARAM wParam,
									  LPARAM lParam)
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
		OnWindowDestroyed();
		return 0 ;

	case WM_DESTROY:
		OnWindowDestroyed();
		return 0 ;

	case WM_ACTIVATE:
	{
		if (LOWORD(wParam) == WA_ACTIVE)
		{
			if(cGameOptions::GameOptions().bFullScreen)
			{
				SetDisplayResolution();
			}
			ShowWindow(hwnd, SW_RESTORE);
		}
		else if (LOWORD(wParam) == WA_INACTIVE)
		{
			if(cGameOptions::GameOptions().bFullScreen)
			{
				SetDisplayResolution();
			}
			ShowWindow(hwnd, SW_MINIMIZE);
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
		Base::AppMsg msg;
		msg.m_hWnd = hwnd;
		msg.m_uMsg = uMsg;
		msg.m_wParam = wParam;
		msg.m_lParam = lParam;

		if (m_pGame)
		{
			m_pGame->VOnMsgProc(msg);
		}
		return 0;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam) ;
	}
}

// *****************************************************************************
void cMainWindow::OnWindowDestroyed()
{
    // return to the default mode
	ChangeDisplaySettings(NULL, 0);

	// release the graphic object
	ReleaseCapture() ;
	UnregisterClass("Window", m_hInstance);
	PostQuitMessage(0);
}

// *****************************************************************************
void cMainWindow::SetDisplayResolution()
{
	if (cGameOptions::GameOptions().bFullScreen)
	{
		DEVMODE dmScreenSettings;
		SecureZeroMemory(&dmScreenSettings, sizeof(dmScreenSettings));
		if (!EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmScreenSettings))
		{
			Log_Write_L2(ILogger::LT_DEBUG, "Could not get current display Settings");
			return;
		}

		// set the full screen height and width
		dmScreenSettings.dmPelsHeight = (unsigned long)cGameOptions::GameOptions().iHeight;
		dmScreenSettings.dmPelsWidth = (unsigned long)cGameOptions::GameOptions().iWidth;
		dmScreenSettings.dmFields = (DM_PELSWIDTH | DM_PELSHEIGHT);

        // Test if the requested graphics mode could be set.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_TEST) == DISP_CHANGE_SUCCESSFUL)
		{
		    // Set the requested graphics mode.
			if(ChangeDisplaySettings(&dmScreenSettings, 0) == DISP_CHANGE_SUCCESSFUL)
			{
				Log_Write_L2(ILogger::LT_COMMENT, cString(100, "Resolution set to width %d and height %d", cGameOptions::GameOptions().iWidth, cGameOptions::GameOptions().iHeight));
				return;
			}
		}
		Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Could not set resolution with width %d and height %d", cGameOptions::GameOptions().iWidth, cGameOptions::GameOptions().iHeight));
	}

	// return to the default mode
	ChangeDisplaySettings(NULL, 0);
	return;
}

// *****************************************************************************
void cMainWindow::CalculateWindowRect()
{
	m_windowRect.left = (GetSystemMetrics(SM_CXSCREEN) - cGameOptions::GameOptions().iWidth)  / 2;
	m_windowRect.top = (GetSystemMetrics(SM_CYSCREEN) - cGameOptions::GameOptions().iHeight) / 2;
	m_windowRect.right =  m_windowRect.left + cGameOptions::GameOptions().iWidth;
	m_windowRect.bottom = m_windowRect.top + cGameOptions::GameOptions().iHeight;

	//get the required size of the window rectangle, based on the desired size of the client rectangle
	AdjustWindowRectEx(&m_windowRect, m_kdwWindowedStyle, false, 0);
}

// *****************************************************************************
void cMainWindow::VCleanup()
{
	DestroyWindow(m_Hwnd);
}

// *****************************************************************************
IMainWindow * const IMainWindow::GetInstance()
{
	if(s_pWindow == NULL)
		s_pWindow = DEBUG_NEW cMainWindow();
	return s_pWindow;
}

// *****************************************************************************
void IMainWindow::Destroy()
{
	if(s_pWindow != NULL)
		s_pWindow->VCleanup();
	SAFE_DELETE(s_pWindow);
	Log_Write_L2(ILogger::LT_COMMENT, cString(100, "Window destroyed"));
}
