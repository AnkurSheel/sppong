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
#include "Vector3.h"

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
}

// ***************************************************************
bool Graphics::cWindowControl::VOnLeftMouseButtonDown( const int X, const int Y )
{
	if (m_eWindowType != WT_DESKTOP)
	{
		Log_Write_L3(ILogger::LT_DEBUG, cString(100, "Graphics::cWindowControl::OnMouseDown" ));
		return cBaseControl::VOnLeftMouseButtonDown(X, Y);
	}
}

// ***************************************************************
bool Graphics::cWindowControl::VOnMouseMove( const int X, const int Y )
{
	if (m_eWindowType != WT_DESKTOP)
	{
		return cBaseControl::VOnMouseMove(X, Y);
	}
}

// ***************************************************************
void Graphics::cWindowControl::VSetAbsolutePosition()
{
	cBaseControl::VSetAbsolutePosition();
	if (m_pCanvasSprite)
	{
		m_pCanvasSprite->SetPosition(D3DXVEC3ToVector3(m_vControlAbsolutePosition));
	}
}
// ***************************************************************
void Graphics::cWindowControl::LoadCanvasFromFile( const Base::cString & strFileName )
{
	if(m_eWindowType != WT_DESKTOP)
	{
		m_pCanvasSprite = ISprite::CreateSprite();
		m_pCanvasSprite->Init(IDXBase::GetInstance()->VGetDevice(), strFileName);

		m_fHeight = m_pCanvasSprite->GetScaledHeight();
		m_fWidth = m_pCanvasSprite->GetScaledWidth();
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

		m_iLastNormalPosX = m_vPosition.x;
		m_iLastNormalPosY = m_vPosition.y;
		m_iLastNormalWidth = m_fWidth;
		m_iLastNormalHeight = m_fHeight;
		
		m_bIsMinimized = true;

		m_vPosition.x = iX;
		m_vPosition.y = iY;
		m_fHeight = iHeight;
		m_fWidth = iWidth;
	}
}

// ***************************************************************
void Graphics::cWindowControl::Restore()
{
	if (m_eWindowType != WT_DESKTOP)
	{
		m_vPosition.x = m_iLastNormalPosX;
		m_vPosition.y = m_iLastNormalPosY;
		m_fHeight = m_iLastNormalHeight;
		m_fWidth = m_iLastNormalWidth;

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
