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
#include "Timer.hxx"
#include "Input/Input.hxx"
#include "fps/FPS.hxx"
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
, m_pGameApp(NULL)
, m_iFullScreenHeight(0)
, m_iFullScreenWidth(0)
, m_pGameTimer(NULL)
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
HWND cMainWindow::Init( const HINSTANCE &hInstance, const int &nCmdShow, const cString & lpWindowTitle,const int iFullScreenWidth, const int iFullScreenHeight, IBaseApp* const pGameApp )
{
	HWND hWnd ;
	m_hInstance = hInstance;

	m_pGameApp = pGameApp;

	m_iFullScreenWidth = iFullScreenWidth ; 
	m_iFullScreenHeight = iFullScreenHeight ;

	//Register the Window Class
	RegisterWin();

	//Create the Window
	hWnd = CreateMyWindow(nCmdShow, lpWindowTitle) ;

	OnCreateDevice(hInstance,hWnd);
	//OnResetDevice();

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
HWND cMainWindow::CreateMyWindow( const int &nCmdShow, const cString & lpWindowTitle )
{
#ifdef WINDOWED
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
#else
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
#endif

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
// the message loop
// ***************************************************************
void cMainWindow::Run()
{
	MSG Msg ;

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

			OnRender();
		}
	}

	// a WM_Quit message has been sent so destroy the window
	DestroyWindow(m_Hwnd);
}
// ***************************************************************

// ***************************************************************
// Function called to handle the rendering
// ***************************************************************
void cMainWindow::OnRender()
{
	HRESULT hr;

	// update the game timer
	if (m_pGameTimer)
	{
		m_pGameTimer->Update();
	}

	// check if the device is available
	hr = IDXBase::GetInstance()->IsAvailable() ;

	if(hr == D3DERR_DEVICELOST || hr == D3DERR_DEVICENOTRESET)
	{
		HandleLostDevice(hr) ;
	}

	// get user inputs
	GetInput();

	if(SUCCEEDED(hr))
	{

		hr = IDXBase::GetInstance()->BeginRender();
		if (SUCCEEDED(hr))
		{
			// process the user inputs according to game logic
			m_pGameApp->ProcessInput(m_pInput->GetMouseXDelta(), m_pInput->GetMouseYDelta(), m_pInput->GetMouseZDelta(), m_pInput->GetPressedKeys(), m_pInput->GetPressedButtons(), m_pGameTimer->GetElapsedTime()) ;

			// render the game graphics
			m_pGameApp->Render();

			IDXBase::GetInstance()->EndRender(hr);
		}
	}
}
// ***************************************************************

// ***************************************************************
// Function called when the application quits
// ***************************************************************
void cMainWindow::OnDestroyDevice()
{
	// delete the game timer
	SAFE_DELETE(m_pGameTimer);

	// delete the input handler
	SAFE_DELETE(m_pInput);

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
// Function called when the device needs to be reset
// ***************************************************************
void cMainWindow::OnResetDevice()
{
	LPDIRECT3DDEVICE9 pDevice = IDXBase::GetInstance()->GetDevice();
	if (pDevice)
	{
		GetWinRect() ;
		IDXBase::GetInstance()->ResetDevice();
		if (m_pGameApp)
		{
			m_pGameApp->OnResetDevice() ;
		}

		if (m_pFPS)
		{
			m_pFPS->OnResetDevice(pDevice);
		}
	}
}
// ***************************************************************

// ***************************************************************
// Function called when the device is created
// ***************************************************************
void cMainWindow::OnCreateDevice( const HINSTANCE hInst, const HWND hWnd )
{
	// initialize DirectX
	IDXBase::GetInstance()->Init(hWnd, TAN);

	m_pGameTimer = ITimer::CreateTimer();
	m_pGameTimer->Start();

	m_pInput = IInput::CreateInputDevice();
	m_pInput->Init(hInst, hWnd, m_iClientWidth, m_iClientHeight);

	m_pFPS = IFPS::CreateFPS();
	m_pFPS->Init(IDXBase::GetInstance()->GetDevice(), D3DXVECTOR3((float)m_iClientWidth/2, 10.0f, 0.0f));

	m_pResourceCache = IResCache::CreateResourceCache(30, "resources.zip");
	if(!m_pResourceCache->Init())
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Could not create Resource Cache.\n"));
		PostQuitMessage(0);
		return;
	}

#ifdef WINDOWED
	m_pGameApp->OnInit(IDXBase::GetInstance()->GetDevice(), m_iClientHeight, m_iClientWidth);
#else
	m_pGameApp->OnInit(IDXBase::GetInstance()->GetDevice(), IDXBase::GetInstance()->GetDisplayHeight(), IDXBase::GetInstance()->GetDisplayWidth());
#endif

	SetForegroundWindow(m_Hwnd);

}
// ***************************************************************

// ***************************************************************
// Tries to restore a lost device
// ***************************************************************
void cMainWindow::HandleLostDevice(HRESULT hr)
{
	if(hr == D3DERR_DEVICELOST)
	{
		Sleep(50) ;
		return;
	}
	else 
	{
		if(hr == D3DERR_DEVICENOTRESET) 
		{
			OnLostDevice();
			hr = IDXBase::GetInstance()->ResetDevice() ;

			OnResetDevice();
		}
	}
}
// ***************************************************************

// ***************************************************************
// Function called when the device is  to free the resources
// ***************************************************************
void cMainWindow::OnLostDevice()
{
	if (m_pGameApp)
	{
		m_pGameApp->OnLostDevice();
	}

	if (m_pFPS)
	{
		m_pFPS->OnLostDevice();
	}
}
// ***************************************************************

// ***************************************************************
// Gets User Inputs 
// ***************************************************************
void cMainWindow::GetInput() const
{
	m_pInput->DetectKeys();
	m_pInput->DetectMouseMovement();
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
	m_pFPS->Render(IDXBase::GetInstance()->GetDevice(), m_pGameTimer->GetFPS());
}
// ***************************************************************

// ***************************************************************
// returns the time between the last and current frame
// ***************************************************************
float cMainWindow::GetElapsedTime() const
{
	return m_pGameTimer->GetElapsedTime();
}
// ***************************************************************

// ***************************************************************
// Gets the running time
// ***************************************************************
float cMainWindow::GetRunningTime() const
{
	return m_pGameTimer->GetRunningTime();
}
// ***************************************************************

// ***************************************************************
// Locks the key on the keyboard
// ***************************************************************
void cMainWindow::LockKey( const DWORD dwKey ) 
{
	m_pInput->LockKey(dwKey);
}
// ***************************************************************

// ***************************************************************
// Gets the absolute X position of the cursor
// ***************************************************************
long cMainWindow::GetAbsXMousePos() const
{
	return m_pInput->GetX();
}
// ***************************************************************

// ***************************************************************
// Locks the key on the keyboard
// ***************************************************************
long cMainWindow::GetAbsYMousePos() const
{
	return m_pInput->GetY();
}
// ***************************************************************

IResCache * cMainWindow::GetResourceCache() const
{
	return m_pResourceCache;
}

void cMainWindow::Destroy()
{
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


