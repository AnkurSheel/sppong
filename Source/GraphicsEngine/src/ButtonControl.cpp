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
#include "TextureManager.hxx"
#include "DxBase.hxx"
#include "Font.hxx"
#include "Sprite.hxx"

using namespace Graphics;
using namespace Utilities;
using namespace Base;

// ***************************************************************
cButtonControl::cButtonControl()
: m_bPressed(false)
{

}

// ***************************************************************
cButtonControl::~cButtonControl()
{
}

// ***************************************************************
void cButtonControl::Initialize(const cButtonControlDef & def)
{
	if (!def.strDefaultImage.IsEmpty())
	{
		if(m_pDefaultTexture == NULL)
		{
			m_pDefaultTexture = ITextureManager::GetInstance()->VGetTexture(def.strDefaultImage);
		}
	}

	if (!def.strPressedImage.IsEmpty())
	{
		if(m_pPressedTexture == NULL)
		{
			m_pPressedTexture = ITextureManager::GetInstance()->VGetTexture(def.strPressedImage);
		}
	}

	m_pBGSprite = ISprite::CreateSprite();
	if (m_pDefaultTexture)
	{
		m_pBGSprite->VInitialize(m_pDefaultTexture);
	}
	if (def.labelControlDef.pFont && !def.labelControlDef.strText.IsEmpty())
	{
		m_pLabel = shared_ptr<IBaseControl>(IBaseControl::CreateLabelControl(def.labelControlDef));
	}

	cBaseControl::Initialize(def);

	if(def.bAutoSize)
	{
		VSetSize(cVector2(m_pLabel->VGetWidth(), m_pLabel->VGetHeight()));
	}

}

// *************************************************************************
void cButtonControl::VRender(const ICamera * const pCamera)
{
	if(m_bVisible)
	{
		cBaseControl::VRender(pCamera);
		if (m_pLabel)
		{
			m_pLabel->VRender(pCamera);
		}
	}
}

// ***************************************************************
bool cButtonControl::VOnLeftMouseButtonUp( const int X, const int Y )
{
	if(m_bIsLeftMouseDown)
	{
		Log_Write_L3(ILogger::LT_COMMENT, "cButtonControl :Button Released");
		m_bPressed = false;
		if(m_pDefaultTexture)
		{
			m_pBGSprite->VSetTexture(m_pDefaultTexture);
		}
		if (UIEventCallBackFn * pFn = GetCallbackFromMap(UIET_BTNRELEASED))
		{
			unUIEventCallbackParam param;
			(*pFn)(param);
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
	if (m_pPressedTexture)
	{
		m_pBGSprite->VSetTexture(m_pPressedTexture);
	}
	if (UIEventCallBackFn * pFn = GetCallbackFromMap(UIET_BTNPRESSED))
	{
		unUIEventCallbackParam param;
		(*pFn)(param);
	}
	return cBaseControl::VOnLeftMouseButtonDown(X, Y);
}

// *************************************************************************
void cButtonControl::VSetAbsolutePosition()
{
	cBaseControl::VSetAbsolutePosition();
	if (m_pLabel)
	{
		float fcenterX = m_vControlAbsolutePosition.x + VGetWidth()/2.0f - m_pLabel->VGetWidth()/2.0f;
		float fcenterY = m_vControlAbsolutePosition.y + VGetHeight()/2.0f- m_pLabel->VGetHeight()/2.0f;
		m_pLabel->VSetPosition(cVector2(fcenterX, fcenterY));
	}
}

// ***************************************************************
IBaseControl * IBaseControl::CreateButtonControl(const cButtonControlDef & def)
{
	cButtonControl * pControl = DEBUG_NEW cButtonControl();
	pControl->Initialize(def);
	return pControl;
}
