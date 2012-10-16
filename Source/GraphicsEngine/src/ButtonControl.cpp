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
using namespace Base;

// ***************************************************************
cButtonControl::cButtonControl()
: m_pLabelCaption(NULL)
, m_bPressed(false)
{

}

// ***************************************************************
cButtonControl::~cButtonControl()
{
	VCleanup();
}

// ***************************************************************
void cButtonControl::Init(const Base::cString & strDefaultImage,
									const Base::cString & strPressedImage,
									const Base::cString & strCaption,
									const shared_ptr<IMyFont> m_pFont,
									const Base::cColor & textColor,
									const bool bAutoSize)
{
	Init(strDefaultImage, strPressedImage);

	SAFE_DELETE(m_pLabelCaption);
	m_pLabelCaption = IBaseControl::CreateLabelControl(m_pFont, textColor, strCaption, 35);
	if(bAutoSize)
	{
		VSetSize(cVector2(m_pLabelCaption->VGetWidth(), m_pLabelCaption->VGetHeight()));
	}
}

// ***************************************************************
void cButtonControl::Init( const Base::cString & strDefaultImage,
									const Base::cString & strPressedImage )
{
	if(m_pDefaultTexture == NULL)
	{
		m_pDefaultTexture = ITexture::CreateTexture();
	}
	m_pDefaultTexture->VInitialize(strDefaultImage);

	if(m_pPressedTexture == NULL)
	{
		m_pPressedTexture = ITexture::CreateTexture();
	}
	m_pPressedTexture->VInitialize(strPressedImage);

	m_pCanvasSprite = ISprite::CreateSprite();
	m_pCanvasSprite->VInitialize(m_pDefaultTexture);
}

// ***************************************************************
void cButtonControl::VRender(const ICamera * const pCamera )
{
	cBaseControl::VRender(pCamera);
	if (m_pLabelCaption)
	{	
		m_pLabelCaption->VRender(pCamera);
	}
}

// ***************************************************************
bool cButtonControl::VOnLeftMouseButtonUp( const int X, const int Y )
{
	if(m_bIsMouseDown)
	{
		Log_Write_L3(ILogger::LT_COMMENT, "cButtonControl :Button Released");
		m_bPressed = false;
		m_pCanvasSprite->VSetTexture(m_pDefaultTexture);
		if (m_pfnCallBack)
		{
			m_pfnCallBack(false);
		}
		return cBaseControl::VOnLeftMouseButtonUp(X, Y);
	}
	return false;
}

// ***************************************************************
bool cButtonControl::VOnLeftMouseButtonDown( const int X, const int Y )
{
	Log_Write_L3(ILogger::LT_COMMENT, "cButtonControl: Button Pressed");
	m_bPressed = true;
	m_pCanvasSprite->VSetTexture(m_pPressedTexture);
	if (m_pfnCallBack)
	{
		m_pfnCallBack(true);
	}
	return cBaseControl::VOnLeftMouseButtonDown(X, Y);
}

// ***************************************************************
void cButtonControl::VSetAbsolutePosition()
{
	cBaseControl::VSetAbsolutePosition();
	if (m_pLabelCaption)
	{
		float fcenterX = m_vControlAbsolutePosition.m_dX + VGetWidth()/2.0f - m_pLabelCaption->VGetWidth()/2.0f;
		float fcenterY = m_vControlAbsolutePosition.m_dY + VGetHeight()/2.0f- m_pLabelCaption->VGetHeight()/2.0f;;
		m_pLabelCaption->VSetPosition(cVector2(fcenterX, fcenterY));
	}
 }

// ***************************************************************
void cButtonControl::VCleanup()
{
	SAFE_DELETE(m_pLabelCaption);
	VUnregisterCallBack();
}

// ***************************************************************
IBaseControl * IBaseControl::CreateButtonControl(const Base::cString & strDefaultImage,
												 const Base::cString & strPressedImage,
												 const Base::cString & strCaption,
												 const shared_ptr<IMyFont> m_pFont,
												 const Base::cColor & textColor,
												 const bool bAutoSize)
{
	cButtonControl * pControl = DEBUG_NEW cButtonControl();
	pControl->Init(strDefaultImage, strPressedImage, strCaption, m_pFont, textColor, bAutoSize);
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
