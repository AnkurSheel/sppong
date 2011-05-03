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
#include "Timer.hxx"
#include "Input.hxx"
#include "FPS.hxx"
#include "ResCache.hxx"

using namespace Utilities;
using namespace Graphics;
using namespace Base;

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
, m_pFPS(NULL)
, m_pResourceCache(NULL)
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
HWND cMainWindow::Init( const HINSTANCE &hInstance, const int &nCmdShow, const cString & lpWindowTitle,const int iFullScreenWidth, const int iFullScreenHeight, const bool bFullScreen )
{
	HWND hWnd ;
	m_hInstance = hInstance;

	m_iFullScreenWidth = iFullScreenWidth ; 
	m_iFullScreenHeight = iFullScreenHeight ;

	//Register the Window Class
	RegisterWin();

	//Create the Window
	hWnd = CreateMyWindow(nCmdShow, lpWindowTitle, bFullScreen) ;

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
			200, 200,
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
LRESULT CALLBACK cMainWindow::WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT		ps ;
	HDC				hdc ;

	switch(msg)
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

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam) ;
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
	SAFE_DELETE(m_pFPS);

	SAFE_DELETE(m_pResourceCache);

	// release the graphic object
	if (IDXBase::GetInstance())
	{
		IDXBase::GetInstance()->Cleanup();
		IDXBase::GetInstance()->Destroy();
	}

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

	m_pFPS = IFPS::CreateFPS();
	m_pFPS->Init(IDXBase::GetInstance()->GetDevice(), D3DXVECTOR3((float)m_iClientWidth/2, 10.0f, 0.0f), BLACK);

	m_pResourceCache = IResCache::CreateResourceCache(30, "resources.zip");
	if(!m_pResourceCache->Init())
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Could not create Resource Cache.\n"));
		PostQuitMessage(0);
		return;
	}

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

// ***************************************************************
// Display the FPS
// ***************************************************************
void cMainWindow::DisplayFPS()
{
	//m_pFPS->Render(IDXBase::GetInstance()->GetDevice(), m_pGameTimer->GetFPS());
}
// ***************************************************************

IResCache * cMainWindow::GetResourceCache() const
{
	return m_pResourceCache;
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