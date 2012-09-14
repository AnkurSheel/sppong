// ***************************************************************
//  GraphicsClass   version:  1.0   Ankur Sheel  date: 2012/09/13
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "GraphicsClass.h"
#include "DxBase.hxx"

using namespace Graphics;
using namespace Utilities;

IGraphicsClass * cGraphicsClass::s_pGraphic= NULL;

// ***************************************************************
Graphics::cGraphicsClass::cGraphicsClass()
: m_pD3D(NULL)
{

}

// ***************************************************************
Graphics::cGraphicsClass::~cGraphicsClass()
{
	Cleanup();
}

// ***************************************************************
void Graphics::cGraphicsClass::VInitialize( const HWND hWnd,
										   const Base::cColor & bkColor, 
										   const bool bFullScreen, 
										   const bool bVsyncEnabled,
										   const int iWidth,
										   const int iHeight,
										   const float fScreenDepth,
										   const float fScreenNear )
{
	m_pD3D = IDXBase::Create();
	if (m_pD3D == NULL)
	{
		Log_Write_L1(ILogger::LT_ERROR, " Could not create DXBase");
		PostQuitMessage(0);
		return;
	}
	m_pD3D->VInitialize(hWnd, bkColor, bFullScreen, bVsyncEnabled, iWidth,
		iHeight, fScreenDepth, fScreenNear);
}

// ***************************************************************
void Graphics::cGraphicsClass::Update()
{
	//Render();
}

// ***************************************************************
void Graphics::cGraphicsClass::Cleanup()
{
	SAFE_DELETE(m_pD3D);
}

// ***************************************************************
IGraphicsClass * Graphics::cGraphicsClass::Create()
{
	return DEBUG_NEW cGraphicsClass();
}

// ***************************************************************
void Graphics::cGraphicsClass::VBeginRender()
{
	m_pD3D->VBeginRender();
}

// ***************************************************************
void Graphics::cGraphicsClass::VEndRender()
{
	m_pD3D->VEndRender();
}

// ***************************************************************
IGraphicsClass * Graphics::IGraphicsClass::GetInstance()
{
	if(cGraphicsClass::s_pGraphic == NULL)
		cGraphicsClass::s_pGraphic = cGraphicsClass::Create();
	return cGraphicsClass::s_pGraphic ;
}

// ***************************************************************
void Graphics::IGraphicsClass::Destroy()
{
	SAFE_DELETE(cGraphicsClass::s_pGraphic);
}
