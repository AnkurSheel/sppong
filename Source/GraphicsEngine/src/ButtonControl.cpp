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

Graphics::cButtonControl::cButtonControl()
: m_pLabelCaption(NULL)
, m_bPressed(false)
{

}

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
									DWORD dwFormat, const D3DXCOLOR & color )
{

	Init(strDefaultImage, strPressedImage);

	SAFE_DELETE(m_pLabelCaption);
	m_pLabelCaption = IBaseControl::CreateLabelControl(iHeight, iWidth, iWeight, bItalic, charset, strFaceName, dwFormat, color, strCaption);
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
}
// ***************************************************************

void Graphics::cButtonControl::Cleanup()
{
	SAFE_DELETE(m_pLabelCaption);
}
// ***************************************************************


bool Graphics::cButtonControl::OnMouseUp( const int iButton, const int X, const int Y )
{
	Log_Write_L3(ILogger::LT_COMMENT, "Button Released");
	m_bPressed = false;
	m_pCanvasSprite->SetTexture(m_pDefaultTexture);
	return cBaseControl::OnMouseUp(iButton, X, Y);
	
}
// ***************************************************************

bool Graphics::cButtonControl::OnMouseDown( const int iButton, const int X, const int Y )
{
	Log_Write_L3(ILogger::LT_COMMENT, "Button Pressed");
	m_bPressed = true;
	m_pCanvasSprite->SetTexture(m_pPressedTexture);
	return cBaseControl::OnMouseDown(iButton, X, Y);
}
// ***************************************************************

void Graphics::cButtonControl::OnRender( const AppMsg & msg )
{
	D3DXVECTOR3 vControlAbsolutePosition;
	bool bIsPositionChanged;
	RenderPrivate(vControlAbsolutePosition, bIsPositionChanged);

	if (bIsPositionChanged)
	{
		m_pCanvasSprite->SetPosition(vControlAbsolutePosition);
		if (m_pLabelCaption)
		{
			m_pLabelCaption->SetPosition(vControlAbsolutePosition);
		}
	}
	m_pCanvasSprite->OnRender(IDXBase::GetInstance()->VGetDevice());
	if (m_pLabelCaption)
	{	
		m_pLabelCaption->OnRender(msg);
	}
}

void Graphics::cButtonControl::SetSize( const float fNewWidth, const float fNewHeight )
{
	cBaseControl::SetSize(fNewWidth, fNewHeight);
	if (m_pLabelCaption)
	{
		m_pLabelCaption->SetSize(fNewWidth, fNewHeight);
	}
}
// ***************************************************************

void Graphics::cButtonControl::OnLostDevice()
{
	cBaseControl::OnLostDevice();
	if(m_pLabelCaption)
	{
		m_pLabelCaption->OnLostDevice();
	}
}
// ***************************************************************

HRESULT Graphics::cButtonControl::OnResetDevice()
{
	if (m_pLabelCaption)
	{
		m_pLabelCaption->OnResetDevice();
	}
	return cBaseControl::OnResetDevice();
}
// ***************************************************************

IBaseControl * Graphics::IBaseControl::CreateButtonControl( const Base::cString & strDefaultImage, const Base::cString & strPressedImage, const Base::cString & strCaption, const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color )
{
	cButtonControl * pControl = DEBUG_NEW cButtonControl();
	pControl->Init(strDefaultImage, strPressedImage, strCaption, iHeight, iWidth, iWeight, bItalic, charset, strFaceName, dwFormat, color);
	return pControl;
}
// ***************************************************************

IBaseControl * Graphics::IBaseControl::CreateButtonControl( const Base::cString & strDefaultImage, const Base::cString & strPressedImage )
{
	cButtonControl * pControl = DEBUG_NEW cButtonControl();
	pControl->Init(strDefaultImage, strPressedImage);
	return pControl;
}