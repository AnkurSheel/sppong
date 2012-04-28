// ***************************************************************
//  ButtonControl   version:  1.0   Ankur Sheel  date: 2011/11/23
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "ButtonControl.h"
#include "Texture.hxx"
#include "DxBase.hxx"
#include "Font.hxx"
#include "Sprite.hxx"

using namespace Graphics;
using namespace Utilities;

// ***************************************************************
Graphics::cButtonControl::cButtonControl()
: m_pLabelCaption(NULL)
, m_bPressed(false)
, m_pfnCallBack(NULL)
{

}

// ***************************************************************
Graphics::cButtonControl::~cButtonControl()
{
	Cleanup();
}

// ***************************************************************
void Graphics::cButtonControl::Init( const Base::cString & strDefaultImage,
									const Base::cString & strPressedImage, 
									const Base::cString & strCaption,
									const int iHeight, const UINT iWidth, 
									const UINT iWeight, const BOOL bItalic, 
									const BYTE charset, 
									const Base::cString & strFaceName, 
									DWORD dwFormat, const D3DXCOLOR & color,
									const bool bAutoSize)
{
	Init(strDefaultImage, strPressedImage);

	SAFE_DELETE(m_pLabelCaption);
	m_pLabelCaption = IBaseControl::CreateLabelControl(iHeight, iWidth, iWeight, bItalic, charset, strFaceName, dwFormat, color, strCaption);
	if(bAutoSize)
	{
		VSetSize(m_pLabelCaption->VGetWidth(), m_pLabelCaption->VGetHeight());
	}
}

// ***************************************************************
void Graphics::cButtonControl::Init( const Base::cString & strDefaultImage, const Base::cString & strPressedImage )
{
	if(m_pDefaultTexture == NULL)
	{
		m_pDefaultTexture = ITexture::CreateTexture();
	}
	m_pDefaultTexture->Init(IDXBase::GetInstance()->VGetDevice(), strDefaultImage);

	if(m_pPressedTexture == NULL)
	{
		m_pPressedTexture = ITexture::CreateTexture();
	}
	m_pPressedTexture->Init(IDXBase::GetInstance()->VGetDevice(), strPressedImage);

	m_pCanvasSprite = ISprite::CreateSprite();
	m_pCanvasSprite->Init(IDXBase::GetInstance()->VGetDevice(), m_pDefaultTexture);
	m_pCanvasSprite->SetFlags(D3DXSPRITE_ALPHABLEND);
}

// ***************************************************************
void Graphics::cButtonControl::VOnRender( const AppMsg & msg )
{
	if (m_pCanvasSprite)
	{
		m_pCanvasSprite->OnRender(IDXBase::GetInstance()->VGetDevice());
	}
	if (m_pLabelCaption)
	{	
		m_pLabelCaption->VOnRender(msg);
	}
}

// ***************************************************************
void Graphics::cButtonControl::VOnLostDevice()
{
	cBaseControl::VOnLostDevice();
	if(m_pLabelCaption)
	{
		m_pLabelCaption->VOnLostDevice();
	}
}

// ***************************************************************
HRESULT Graphics::cButtonControl::VOnResetDevice()
{
	if (m_pLabelCaption)
	{
		m_pLabelCaption->VOnResetDevice();
	}
	return cBaseControl::VOnResetDevice();
}

// ***************************************************************
bool Graphics::cButtonControl::VOnLeftMouseButtonUp( const int X, const int Y )
{
	if(m_bIsMouseDown)
	{
		Log_Write_L3(ILogger::LT_COMMENT, "cButtonControl :Button Released");
		m_bPressed = false;
		m_pCanvasSprite->SetTexture(m_pDefaultTexture);
		if (m_pfnCallBack)
		{
			m_pfnCallBack(false);
		}
		return cBaseControl::VOnLeftMouseButtonUp(X, Y);
	}
	return false;
}

// ***************************************************************
bool Graphics::cButtonControl::VOnLeftMouseButtonDown( const int X, const int Y )
{
	Log_Write_L3(ILogger::LT_COMMENT, "cButtonControl: Button Pressed");
	m_bPressed = true;
	m_pCanvasSprite->SetTexture(m_pPressedTexture);
	if (m_pfnCallBack)
	{
		m_pfnCallBack(true);
	}
	return cBaseControl::VOnLeftMouseButtonDown(X, Y);
}

// ***************************************************************
void Graphics::cButtonControl::VRegisterCallBack( function <void (bool)> callback )
{
	m_pfnCallBack = callback;
}

// ***************************************************************
void Graphics::cButtonControl::VUnregisterCallBack()
{
	m_pfnCallBack = NULL;
}

// ***************************************************************
void Graphics::cButtonControl::VSetAbsolutePosition()
{
	cBaseControl::VSetAbsolutePosition();
	
	if (m_pCanvasSprite)
	{
		m_pCanvasSprite->SetPosition(m_vControlAbsolutePosition);
	}
	if (m_pLabelCaption)
	{
		m_pLabelCaption->VSetPosition(m_vControlAbsolutePosition);
	}
}
// ***************************************************************
void Graphics::cButtonControl::VSetSize( const float fNewWidth, const float fNewHeight )
{
	cBaseControl::VSetSize(fNewWidth, fNewHeight);
	if (m_pLabelCaption)
	{
		m_pLabelCaption->VSetSize(fNewWidth, fNewHeight);
	}
}

// ***************************************************************
void Graphics::cButtonControl::Cleanup()
{
	SAFE_DELETE(m_pLabelCaption);
	VUnregisterCallBack();
}

// ***************************************************************
IBaseControl * IBaseControl::CreateButtonControl( const Base::cString & strDefaultImage, 
												 const Base::cString & strPressedImage,
												 const Base::cString & strCaption, 
												 const int iHeight, const UINT iWidth, 
												 const UINT iWeight, const BOOL bItalic, 
												 const BYTE charset, 
												 const Base::cString & strFaceName, 
												 DWORD dwFormat, const D3DXCOLOR & color,
												 const bool bAutoSize)
{
	cButtonControl * pControl = DEBUG_NEW cButtonControl();
	pControl->Init(strDefaultImage, strPressedImage, strCaption, iHeight, iWidth, iWeight, bItalic, charset, strFaceName, dwFormat, color, bAutoSize);
	return pControl;
}

// ***************************************************************
IBaseControl * IBaseControl::CreateButtonControl( const Base::cString & strDefaultImage, 
												 const Base::cString & strPressedImage )
{
	cButtonControl * pControl = DEBUG_NEW cButtonControl();
	pControl->Init(strDefaultImage, strPressedImage);
	return pControl;
}
