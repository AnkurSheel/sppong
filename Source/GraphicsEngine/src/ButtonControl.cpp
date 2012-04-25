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
cButtonControl::cButtonControl()
: m_pLabelCaption(NULL)
, m_bPressed(false)
, m_pfnCallBack(NULL)
{

}

// ***************************************************************
cButtonControl::~cButtonControl()
{
	Cleanup();
}

// ***************************************************************
void cButtonControl::Init( const Base::cString & strDefaultImage,
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
void cButtonControl::Init( const Base::cString & strDefaultImage, const Base::cString & strPressedImage )
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
}

// ***************************************************************
bool cButtonControl::VOnLeftMouseButtonUp( const int X, const int Y )
{
	Log_Write_L3(ILogger::LT_COMMENT, "cButtonControl :Button Released");
	m_bPressed = false;
	m_pCanvasSprite->SetTexture(m_pDefaultTexture);
	if (m_pfnCallBack)
	{
		m_pfnCallBack();
	}
	return cBaseControl::VOnLeftMouseButtonUp(X, Y);
	
}

// ***************************************************************
bool cButtonControl::VOnLeftMouseButtonDown( const int X, const int Y )
{
	Log_Write_L3(ILogger::LT_COMMENT, "cButtonControl: Button Pressed");
	m_bPressed = true;
	m_pCanvasSprite->SetTexture(m_pPressedTexture);
	return cBaseControl::VOnLeftMouseButtonDown(X, Y);
}

// ***************************************************************
void cButtonControl::VOnRender( const AppMsg & msg )
{
	D3DXVECTOR3 vControlAbsolutePosition;
	bool bIsPositionChanged;
	RenderPrivate(vControlAbsolutePosition, bIsPositionChanged);

	if (bIsPositionChanged)
	{
		m_pCanvasSprite->SetPosition(vControlAbsolutePosition);
		if (m_pLabelCaption)
		{
			m_pLabelCaption->VSetPosition(vControlAbsolutePosition);
		}
	}
	m_pCanvasSprite->OnRender(IDXBase::GetInstance()->VGetDevice());
	if (m_pLabelCaption)
	{	
		m_pLabelCaption->VOnRender(msg);
	}
}

// ***************************************************************
void cButtonControl::VOnLostDevice()
{
	cBaseControl::VOnLostDevice();
	if(m_pLabelCaption)
	{
		m_pLabelCaption->VOnLostDevice();
	}
}

// ***************************************************************
HRESULT cButtonControl::VOnResetDevice()
{
	if (m_pLabelCaption)
	{
		m_pLabelCaption->VOnResetDevice();
	}
	return cBaseControl::VOnResetDevice();
}

// ***************************************************************
void cButtonControl::VRegisterCallBack(function <void ()> callback)
{
	m_pfnCallBack = callback;
}

// ***************************************************************
void cButtonControl::VUnregisterCallBack()
{
	m_pfnCallBack = NULL;
}

// ***************************************************************
void cButtonControl::VSetSize( const float fNewWidth, const float fNewHeight )
{
	cBaseControl::VSetSize(fNewWidth, fNewHeight);
	if (m_pLabelCaption)
	{
		m_pLabelCaption->VSetSize(fNewWidth, fNewHeight);
	}
}

// ***************************************************************
void cButtonControl::Cleanup()
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
