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
#include "GraphicsClass.hxx"
#include "BaseApp.hxx"
#include "ResourceManager.hxx"
#include "Color.h"
#include "Structures.h"
#include "ParamLoaders.hxx"

using namespace Utilities;
using namespace Graphics;
using namespace Base;
using namespace GameBase;
using namespace std;

IMainWindow * cMainWindow::s_pWindow = NULL;

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
, m_kdwWindowedStyle(WS_SYSMENU | WS_MINIMIZEBOX | WS_CAPTION)
{
}

// ***************************************************************
// Destructor
// ***************************************************************
cMainWindow::~cMainWindow()
{
}

// ***************************************************************
// Initializes, Registers and creates the window.
// Returns a handle to the created window.
// ***************************************************************
HWND cMainWindow::VOnInitialization( const HINSTANCE & hInstance,
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
		m_iFullScreenWidth = 640;
		Log_Write_L2(ILogger::LT_ERROR, "Full Screen Width < =0. Default width of 640 applied");
	}

	if (m_iFullScreenHeight <= 0)
	{
		m_iFullScreenHeight = 480;
		Log_Write_L2(ILogger::LT_ERROR, "Full Screen Width < =0. Default height of 480 applied");
	}

	RegisterWin();

	m_pGame = pGame;

	cString strGameTitle = "GameTitle";

	if (pGame)
	{
		strGameTitle = pGame->VGetGameTitle() ;
	}

	CreateMyWindow(nCmdShow, strGameTitle) ;

	OnWindowCreated();

	return m_Hwnd;
}

// ***************************************************************
// Toggles between full screen and windowed mode
// ***************************************************************
void cMainWindow::VToggleFullScreen()
{
	m_bFullScreen = !m_bFullScreen;

	if (m_bFullScreen)
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
	IGraphicsClass::GetInstance()->VSetFullScreenMode(m_bFullScreen);
}

// ***************************************************************
// Registers the window
// ***************************************************************
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

// ***************************************************************
// Creates the window
// ***************************************************************
void cMainWindow::CreateMyWindow( const int &nCmdShow, const cString & lpWindowTitle)
{
	DWORD dwStyle;
	
	CalculateWindowRect();

	int x, y, height, width;
	if(m_bFullScreen)
	{
		dwStyle = m_kdwFullScreenStyle;
		x = 0;
		y = 0;
		width = m_iFullScreenWidth;
		height = m_iFullScreenHeight;

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

// ***************************************************************
// Event handler. Routes messages to appropriate instance
// ***************************************************************
LRESULT CALLBACK cMainWindow::StaticWndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
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
		OnWindowDestroyed();
		return 0 ;

	case WM_DESTROY:
		OnWindowDestroyed();
		return 0 ;

	case WM_ACTIVATE:
	{
		if (LOWORD(wParam) == WA_ACTIVE)
		{
			if(m_bFullScreen)
			{
				SetDisplayResolution();
			}
			ShowWindow(hwnd, SW_RESTORE);
		}
		else if (LOWORD(wParam) == WA_INACTIVE)
		{
			if(m_bFullScreen)
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

// ***************************************************************
// Function called when the device is created
// ***************************************************************
void cMainWindow::OnWindowCreated()
{
    //Bring the window into the foreground and activates the window
	SetForegroundWindow(m_Hwnd);
	//Set the keyboard focus
	SetFocus(m_Hwnd);

	vector<int> vBGColor;
	if(IBaseApp::VGetParamLoader() != NULL)
	{
		IBaseApp::VGetParamLoader()->VGetParameterValueAsIntList("-BackGroundColor", vBGColor);
	}
	cColor bgColor = cColor::BLACK;
	if(!vBGColor.empty() && vBGColor.size() == 4)
	{
		bgColor = cColor(vBGColor[0], vBGColor[1], vBGColor[2], vBGColor[3]);
	}
	bool bVSyncEnabled = false;
	if(IBaseApp::VGetParamLoader() != NULL)
	{
		bVSyncEnabled = IBaseApp::VGetParamLoader()->VGetParameterValueAsBool("-VSyncEnabled", false);
	}

	float fScreenFar = 1000.0f;
	if(IBaseApp::VGetParamLoader() != NULL)
	{
		fScreenFar = IBaseApp::VGetParamLoader()->VGetParameterValueAsFloat("-ScreenFar", 1000.0f);
	}

	float fScreenNear = 0.1f;
	if(IBaseApp::VGetParamLoader() != NULL)
	{
		fScreenNear = IBaseApp::VGetParamLoader()->VGetParameterValueAsFloat("-ScreenNear", 0.1f);
	}

	IGraphicsClass::GetInstance()->VInitialize(m_Hwnd, bgColor, m_bFullScreen, 
		bVSyncEnabled, m_iFullScreenWidth, m_iFullScreenHeight, fScreenFar, fScreenNear );

	// initialize resource manager
	IResourceManager::GetInstance()->VInitialize("resources.zip");
}

// ***************************************************************
// Function called when the application quits
// ***************************************************************
void cMainWindow::OnWindowDestroyed()
{
    // return to the default mode
	ChangeDisplaySettings(NULL, 0);

	// release the graphic object
	IGraphicsClass::Destroy();

	IResourceManager::Destroy();

	ReleaseCapture() ;
	UnregisterClass("Window", m_hInstance);
	PostQuitMessage(0);
}

// ***************************************************************
// Sets the settings of the default display device to the specified graphics mode
// ***************************************************************
void cMainWindow::SetDisplayResolution()
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

		// set the full screen height and width
		dmScreenSettings.dmPelsHeight = (unsigned long)m_iFullScreenHeight;
		dmScreenSettings.dmPelsWidth = (unsigned long)m_iFullScreenWidth;
		dmScreenSettings.dmFields = (DM_PELSWIDTH | DM_PELSHEIGHT);

        // Test if the requested graphics mode could be set.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_TEST) == DISP_CHANGE_SUCCESSFUL)
		{
		    // Set the requested graphics mode.
			if(ChangeDisplaySettings(&dmScreenSettings, 0) == DISP_CHANGE_SUCCESSFUL)
			{
				Log_Write_L2(ILogger::LT_COMMENT, cString(100, "Resolution set to width %d and height %d", m_iFullScreenWidth, m_iFullScreenHeight));
				return;
			}
		}
		Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Could not set resolution with width %d and height %d", m_iFullScreenWidth, m_iFullScreenHeight));
	}

	// return to the default mode
	ChangeDisplaySettings(NULL, 0);
	return;
}

// *************************************************************************
void cMainWindow::CalculateWindowRect()
{
	m_windowRect.left = (GetSystemMetrics(SM_CXSCREEN) - m_iFullScreenWidth)  / 2;
	m_windowRect.top = (GetSystemMetrics(SM_CYSCREEN) - m_iFullScreenHeight) / 2;
	m_windowRect.right =  m_windowRect.left + m_iFullScreenWidth;
	m_windowRect.bottom = m_windowRect.top + m_iFullScreenHeight;

	//get the required size of the window rectangle, based on the desired size of the client rectangle
	AdjustWindowRectEx(&m_windowRect, m_kdwWindowedStyle, false, 0);
}

// ***************************************************************
// Destroys the Window
// ***************************************************************
void cMainWindow::VCleanup()
{
	DestroyWindow(m_Hwnd);
}

// ***************************************************************
// Create and Returns an object of this class
// ***************************************************************
void cMainWindow::Create()
{
	s_pWindow = DEBUG_NEW cMainWindow();
}

// ***************************************************************
// Destroys the window and the singleton object
// ***************************************************************
void cMainWindow::Destroy()
{
	if(s_pWindow != NULL)
		s_pWindow->VCleanup();
	SAFE_DELETE(s_pWindow);
	Log_Write_L2(ILogger::LT_COMMENT, cString(100, "Window destroyed"));
}

// ***************************************************************
// returns an instance of the class
// ***************************************************************
IMainWindow * IMainWindow::GetInstance()
{
	if(cMainWindow::s_pWindow == NULL)
		cMainWindow::Create();
	return cMainWindow::s_pWindow;
}

void IMainWindow::Destroy()
{
	cMainWindow::Destroy();
}

