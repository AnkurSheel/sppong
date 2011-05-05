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
{
}
// ***************************************************************

// ***************************************************************
// Destructor
// ***************************************************************
cDXBase::~cDXBase()
{
	Cleanup();
}
// ***************************************************************

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

// ***************************************************************
// Sets the Presentation Parameters
// ***************************************************************
void cDXBase::SetParameters(const BOOL bFullScreen)
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

	if(bFullScreen)
	{
		// if its a full screen app
		m_d3dpp.BackBufferWidth = GetSystemMetrics(SM_CXSCREEN);
		m_d3dpp.BackBufferHeight = GetSystemMetrics(SM_CYSCREEN);
		m_d3dpp.Windowed = false; // fullscreen
		m_d3dpp.FullScreen_RefreshRateInHz = m_displayMode.RefreshRate;
	}
	else
	{
		// if its a windowed app
		m_d3dpp.Windowed = true ;
		m_d3dpp.EnableAutoDepthStencil = TRUE ;
		m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16 ;
	}
}
// ***************************************************************

// ***************************************************************
// Resets the device
// ***************************************************************
HRESULT cDXBase::ResetDevice()
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

// ***************************************************************
// Initializes the directX object
// ***************************************************************
void cDXBase::Init( const HWND hWnd, const D3DCOLOR& bkColor, const bool bFullScreen)
{
	m_Hwnd = hWnd;
	m_BkColor = bkColor;

	DirectxInit() ;
	SetParameters(bFullScreen) ;
	CreateDirectxDevice() ;
}
// ***************************************************************

// ***************************************************************
// Function to begin the rendering
// ***************************************************************
HRESULT cDXBase::BeginRender()
{
	HRESULT hr;

	// clear the frame
	m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, m_BkColor, 1.0f, 0) ;

	hr = m_pd3dDevice->BeginScene() ;

	return hr;
}
// ***************************************************************

void cDXBase::CreateDXBase()
{
	s_pDXBase = DEBUG_NEW cDXBase();
}

void cDXBase::Destroy()
{
	delete this;
}

// ***************************************************************
// returns an instance of the class
// ***************************************************************
IDXBase* IDXBase::GetInstance()
{
	if(!s_pDXBase)
		cDXBase::CreateDXBase();
	return s_pDXBase;
}
// ******************	*********************************************

