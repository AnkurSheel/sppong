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
#include "ShaderManager.hxx"
#include "TextureManager.hxx"
#include "Camera.hxx"
#include "GraphicUtils.h"
#include "FontManager.hxx"
#include "ObjModelLoader.hxx"
#include "CollisionChecker.hxx"

using namespace Graphics;
using namespace Utilities;
using namespace Base;

IGraphicsClass * cGraphicsClass::s_pGraphic= NULL;

// ***************************************************************
Graphics::cGraphicsClass::cGraphicsClass()
{

}

// ***************************************************************
Graphics::cGraphicsClass::~cGraphicsClass()
{
	Cleanup();
}

// ***************************************************************
void Graphics::cGraphicsClass::VInitialize( const HWND & hWnd,
										   const Base::cColor & bkColor, 
										   const bool bFullScreen, 
										   const bool bVsyncEnabled,
										   const int iWidth,
										   const int iHeight,
										   const float fScreenDepth,
										   const float fScreenNear )
{
	if (IDXBase::GetInstance() == NULL)
	{
		Log_Write_L1(ILogger::LT_ERROR, " Could not create DXBase");
		PostQuitMessage(0);
		return;
	}
	IDXBase::GetInstance()->VInitialize(hWnd, bkColor, bFullScreen, bVsyncEnabled, iWidth,
		iHeight, fScreenDepth, fScreenNear);
}

// *************************************************************************
void Graphics::cGraphicsClass::VSetFullScreenMode(const bool bIsFullScreen)
{
	IDXBase::GetInstance()->VSetFullScreenMode(bIsFullScreen);
}

// ***************************************************************
void Graphics::cGraphicsClass::Cleanup()
{
	IFontManager::Destroy();
	IShaderManager::Destroy();
	ITextureManager::Destroy();
	IObjModelLoader::Destroy();
	ICollisionChecker::Destroy();
	IGraphicUtils::Destroy();
	IDXBase::Destroy();
}

// ***************************************************************
void Graphics::cGraphicsClass::VBeginRender()
{
	IDXBase::GetInstance()->VBeginRender();
}

// ***************************************************************
void Graphics::cGraphicsClass::VEndRender()
{
	IDXBase::GetInstance()->VEndRender();
}

// ***************************************************************
IGraphicsClass * IGraphicsClass::GetInstance()
{
	if(cGraphicsClass::s_pGraphic == NULL)
		cGraphicsClass::s_pGraphic = DEBUG_NEW cGraphicsClass();
	return cGraphicsClass::s_pGraphic ;
}

// ***************************************************************
void IGraphicsClass::Destroy()
{
	SAFE_DELETE(cGraphicsClass::s_pGraphic);
}
