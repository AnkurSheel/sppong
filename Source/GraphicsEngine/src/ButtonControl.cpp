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
void cButtonControl::Init(const ButtonControlDef & def)
{
	if (!def.strDefaultImage.IsEmpty())
	{
		if(m_pDefaultTexture == NULL)
		{
			m_pDefaultTexture = ITexture::CreateTexture();
		}
		m_pDefaultTexture->VInitialize(def.strDefaultImage);

	}

	if (!def.strPressedImage.IsEmpty())
	{
		if(m_pPressedTexture == NULL)
		{
			m_pPressedTexture = ITexture::CreateTexture();
		}
		m_pPressedTexture->VInitialize(def.strPressedImage);
	}

	//if ((m_pDefaultTexture || m_pPressedTexture))
	{
		m_pCanvasSprite = ISprite::CreateSprite();
		if (m_pDefaultTexture)
		{
			m_pCanvasSprite->VInitialize(m_pDefaultTexture);
		}
	}

	SAFE_DELETE(m_pLabelCaption);
	
	if (def.pFont)
	{
		LabelControlDef labelDef;
		labelDef.pFont = def.pFont;
		labelDef.textColor = def.textColor;
		labelDef.strText = def.strCaption;
		labelDef.fTextHeight = 35;

		m_pLabelCaption = IBaseControl::CreateLabelControl(labelDef);
		if(def.bAutoSize)
		{
			VSetSize(cVector2(m_pLabelCaption->VGetWidth(), m_pLabelCaption->VGetHeight()));
		}
	}
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
		if(m_pDefaultTexture)
		{
			m_pCanvasSprite->VSetTexture(m_pDefaultTexture);
		}
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
	if (m_pPressedTexture)
	{
		m_pCanvasSprite->VSetTexture(m_pPressedTexture);
	}
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
	cBaseControl::VCleanup();
	SAFE_DELETE(m_pLabelCaption);
}

// ***************************************************************
IBaseControl * IBaseControl::CreateButtonControl(const ButtonControlDef & def)
{
	cButtonControl * pControl = DEBUG_NEW cButtonControl();
	pControl->Init(def);
	return pControl;
}
