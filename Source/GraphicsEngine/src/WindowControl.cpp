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
using namespace std;

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
		return	cBaseControl::VOnLeftMouseButtonUp(X, Y);
	}
	return false;
}

// ***************************************************************
bool Graphics::cWindowControl::VOnLeftMouseButtonDown( const int X, const int Y )
{
	if (m_eWindowType != WT_DESKTOP)
	{
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

		m_vSize = m_pCanvasSprite->VGetSize();
	}
}

// ***************************************************************
void Graphics::cWindowControl::Minimize( const int iWidth, const int iHeight,
							  const int iX, const int iY )
{
	if (m_eWindowType != WT_DESKTOP)
	{
		ControlList::const_iterator iter;
		for(iter = m_pChildControl.begin(); iter != m_pChildControl.end(); iter++)
		{
			(*iter)->VSetVisible(false);
		}

		m_iLastNormalPosX = (int)m_vPosition.m_dX;
		m_iLastNormalPosY = (int)m_vPosition.m_dY;
		m_iLastNormalWidth = (int)m_vSize.m_dX;
		m_iLastNormalHeight = (int)m_vSize.m_dY;
		
		m_bIsMinimized = true;

		m_vPosition.m_dX = iX;
		m_vPosition.m_dY = iY;
		m_vSize.m_dX = iWidth;
		m_vSize.m_dY = iHeight;
	}
}

// ***************************************************************
void Graphics::cWindowControl::Restore()
{
	if (m_eWindowType != WT_DESKTOP)
	{
		m_vPosition.m_dX = m_iLastNormalPosX;
		m_vPosition.m_dY = m_iLastNormalPosY;
		m_vSize.m_dX = m_iLastNormalHeight;
		m_vSize.m_dY = m_iLastNormalWidth;

		m_bIsMinimized = false;
	}
}

// ***************************************************************
IBaseControl * IBaseControl::CreateWindowControl(const stWindowControlDef & def)
{
	cWindowControl * pControl = DEBUG_NEW cWindowControl(def.wType, def.bAllowMovingControls);
	if (!def.strBGImageFile.IsEmpty())
	{
		pControl->LoadCanvasFromFile(def.strBGImageFile);
	}
	return pControl;
}
