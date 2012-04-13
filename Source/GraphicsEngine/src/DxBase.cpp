// ***************************************************************
//  DxBase   version:  1.0   Ankur Sheel  date: 04/29/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "DxBase.h" 

using namespace Utilities;
using namespace Graphics;

// ***************************************************************
// Constructor
// ***************************************************************
cDXBase::cDXBase()
: m_pD3D(NULL)
, m_pd3dDevice(NULL)
, m_Hwnd(NULL)
, m_BkColor(BLACK)
, m_bFullScreen(false)
, m_iWidth(0)
, m_iHeight(0)
{
}

// ***************************************************************
// Destructor
// ***************************************************************
cDXBase::~cDXBase()
{
	Cleanup();
}

// ***************************************************************
// Create and Returns an object of this class
// ***************************************************************
cDXBase* cDXBase::Create()
{
	return(DEBUG_NEW cDXBase());
}

// ***************************************************************
// Initializes the directX object
// ***************************************************************
void cDXBase::VOnInitialization( const HWND hWnd, const D3DCOLOR& bkColor, const bool bFullScreen, const int iWidth, const int iHeight)
{
	m_Hwnd = hWnd;
	m_BkColor = bkColor;
	m_bFullScreen = bFullScreen;
	m_iHeight = iHeight;
	m_iWidth = iWidth;

	DirectxInit() ;
	SetParameters() ;
	CreateDirectxDevice() ;
}

// ***************************************************************
// Resets the device
// ***************************************************************
HRESULT cDXBase::VOnResetDevice()
{
	if (m_pd3dDevice)
	{
		HRESULT		hr ;

		hr = m_pd3dDevice->Reset(&m_d3dpp) ;
		return hr ;
	}
	return 0;
}

// ***************************************************************
// Function to begin the rendering
// ***************************************************************
HRESULT cDXBase::VBeginRender()
{
	HRESULT hr;

	// clear the frame
	m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, m_BkColor, 1.0f, 0) ;

	hr = m_pd3dDevice->BeginScene() ;

	return hr;
}

// ***************************************************************
void cDXBase::VOnDestroy()
{
	Cleanup();
	delete this;
	s_pDXBase = NULL;
}

// ***************************************************************
void cDXBase::VToggleFullScreen()
{
	m_bFullScreen = !m_bFullScreen;
	SetParameters();
}

// ***************************************************************
// Initialize the directX Object
// ***************************************************************
void cDXBase::DirectxInit()
{
	//create the Direct3d Object
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION) ;

	if(m_pD3D == NULL)
	{
		Log_Write_L1(ILogger::LT_ERROR, "Direct3d object creation failed");
		PostQuitMessage(0);
	}

	// get the display mode
	m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &m_displayMode ); 

	// get the device caps
	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_Caps) ;
}

// ***************************************************************
// Create the directX device
// ***************************************************************
void cDXBase::CreateDirectxDevice() 
{
	int		vp = 0 ; // the typeof vertex processing

	if(m_Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
	{
		// hardware vertex processing is supported.
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING ;
	}
	else
	{
		// use software vertex processing.
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING ;
	}

	// Create the D3DDevice
	if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, 
		m_Hwnd,
		vp,
		&m_d3dpp,
		&m_pd3dDevice)))
	{
		Log_Write_L1(ILogger::LT_ERROR, "Direct3d object creation failed");
		PostQuitMessage(0) ;
		DestroyWindow(m_Hwnd) ;
	}
}

// ***************************************************************
// Sets the Presentation Parameters
// ***************************************************************
void cDXBase::SetParameters()
{
	ZeroMemory(&m_d3dpp, sizeof(m_d3dpp)) ;

	m_d3dpp.BackBufferCount = 1 ;
	m_d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE ;
	m_d3dpp.MultiSampleQuality = 0 ;
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD ;
	m_d3dpp.hDeviceWindow = m_Hwnd ;
	m_d3dpp.Flags = 0 ;
	m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT ;
	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE ;
	m_d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8 ; //pixel format
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8 ; // depth format
	m_d3dpp.EnableAutoDepthStencil = true ;
	m_d3dpp.BackBufferWidth = m_iWidth;
	m_d3dpp.BackBufferHeight = m_iHeight;
	m_d3dpp.Windowed = !m_bFullScreen;

	if(m_bFullScreen)
	{
		m_d3dpp.FullScreen_RefreshRateInHz = m_displayMode.RefreshRate;
	}
}

// ***************************************************************
// Release the Direct3D device
// ***************************************************************
void cDXBase::Cleanup()
{
	// release the Direct3d device
	SAFE_RELEASE(m_pd3dDevice) ;

	// release the Direct3d object
	SAFE_RELEASE(m_pD3D) ;
}

// ***************************************************************
// returns an instance of the class
// ***************************************************************
IDXBase* IDXBase::GetInstance()
{
	if(!s_pDXBase)
		s_pDXBase = cDXBase::Create();
	return s_pDXBase;
}