// ***************************************************************
//  WindowControl   version:  1.0   Ankur Sheel  date: 2011/11/21
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "WindowControl.h"
#include "Sprite.hxx"
#include "DxBase.hxx"

using namespace Graphics;
using namespace Utilities;
using namespace Base;

// ***************************************************************
Graphics::cWindowControl::cWindowControl(WINDOWTYPE wType, bool bAllowMovingControls)
: m_iLastNormalPosX(0)
, m_iLastNormalPosY(0)
, m_iLastNormalWidth(0)
, m_iLastNormalHeight(0)
, m_bIsMinimized(false)
, m_eWindowType(wType)
{
	m_bAllowMovingControls = bAllowMovingControls;
}

// ***************************************************************
Graphics::cWindowControl::~cWindowControl()
{
}

// ***************************************************************
bool Graphics::cWindowControl::VOnLeftMouseButtonUp( const int X, const int Y )
{
	if (m_eWindowType != WT_DESKTOP)
	{
		Log_Write_L3(ILogger::LT_ERROR, cString(100, "Graphics::cWindowControl::OnMouseUp"));
		return	cBaseControl::VOnLeftMouseButtonUp(X, Y);
	}
	return false;
}

// ***************************************************************
bool Graphics::cWindowControl::VOnLeftMouseButtonDown( const int X, const int Y )
{
	if (m_eWindowType != WT_DESKTOP)
	{
		Log_Write_L3(ILogger::LT_DEBUG, cString(100, "Graphics::cWindowControl::OnMouseDown" ));
		return cBaseControl::VOnLeftMouseButtonDown(X, Y);
	}
	return false;
}

// ***************************************************************
bool Graphics::cWindowControl::VOnMouseMove( const int X, const int Y )
{
	if (m_eWindowType != WT_DESKTOP)
	{
		return cBaseControl::VOnMouseMove(X, Y);
	}
	return false;
}

// ***************************************************************
void Graphics::cWindowControl::VSetAbsolutePosition()
{
	cBaseControl::VSetAbsolutePosition();
	if (m_pCanvasSprite)
	{
		m_pCanvasSprite->VSetPosition(m_vControlAbsolutePosition);
	}
}
// ***************************************************************
void Graphics::cWindowControl::LoadCanvasFromFile( const Base::cString & strFileName )
{
	if(m_eWindowType != WT_DESKTOP)
	{
		m_pCanvasSprite = ISprite::CreateSprite();
		m_pCanvasSprite->VInitialize(strFileName);

		m_pCanvasSprite->VGetSize(m_vSpriteSize);
	}
}

// ***************************************************************
void Graphics::cWindowControl::Minimize( const int iWidth, const int iHeight,
							  const int iX, const int iY )
{
	if (m_eWindowType != WT_DESKTOP)
	{
		cBaseControl * pTempControl = GetFirstChild();

		while(pTempControl)
		{
			cBaseControl * pNextControl = pTempControl->GetNextSibling();
			pNextControl->VSetVisible(false);
			pTempControl = pNextControl;
		}

		m_iLastNormalPosX = (int)m_vPosition.m_dX;
		m_iLastNormalPosY = (int)m_vPosition.m_dY;
		m_iLastNormalWidth = (int)m_vSpriteSize.m_dX;
		m_iLastNormalHeight = (int)m_vSpriteSize.m_dY;
		
		m_bIsMinimized = true;

		m_vPosition.m_dX = iX;
		m_vPosition.m_dY = iY;
		m_vSpriteSize.m_dX = iWidth;
		m_vSpriteSize.m_dY = iHeight;

	}
}

// ***************************************************************
void Graphics::cWindowControl::Restore()
{
	if (m_eWindowType != WT_DESKTOP)
	{
		m_vPosition.m_dX = m_iLastNormalPosX;
		m_vPosition.m_dY = m_iLastNormalPosY;
		m_vSpriteSize.m_dX = m_iLastNormalHeight;
		m_vSpriteSize.m_dY = m_iLastNormalWidth;

		m_bIsMinimized = false;
	}
}

// ***************************************************************
IBaseControl * IBaseControl::CreateWindowControl( WINDOWTYPE wType,
												 const Base::cString & strFileName, 
												 const bool bAllowMovingControls)
{
	cWindowControl * pControl = DEBUG_NEW cWindowControl(wType, bAllowMovingControls);
	if (!strFileName.IsEmpty())
	{
		pControl->LoadCanvasFromFile(strFileName);
	}
	return pControl;
}
