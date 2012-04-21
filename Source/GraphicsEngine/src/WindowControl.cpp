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
cWindowControl::cWindowControl(WINDOWTYPE wType, bool bAllowMovingControls)
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
cWindowControl::~cWindowControl()
{
}

// ***************************************************************
bool cWindowControl::VOnLeftMouseButtonUp( const int X, const int Y )
{
	if (m_eWindowType != WT_DESKTOP)
	{
		Log_Write_L3(ILogger::LT_ERROR, cString(100, "cWindowControl::OnMouseUp"));
		return	cBaseControl::VOnLeftMouseButtonUp(X, Y);
	}
}

// ***************************************************************
bool cWindowControl::VOnLeftMouseButtonDown( const int X, const int Y )
{
	if (m_eWindowType != WT_DESKTOP)
	{
		Log_Write_L3(ILogger::LT_DEBUG, cString(100, "cWindowControl::OnMouseDown" ));
		return cBaseControl::VOnLeftMouseButtonDown(X, Y);
	}
}

// ***************************************************************
bool cWindowControl::VOnMouseMove( const int X, const int Y )
{
	if (m_eWindowType != WT_DESKTOP)
	{
		return cBaseControl::VOnMouseMove(X, Y);
	}
}

// ***************************************************************
void cWindowControl::VOnRender( const AppMsg & msg )
{
	if (m_eWindowType != WT_DESKTOP)
	{
		D3DXVECTOR3 vControlAbsolutePosition = D3DXVECTOR3(0.f, 0.f, 0.f);
		GetAbsolutePosition(vControlAbsolutePosition);

		m_pCanvasSprite->SetPosition(vControlAbsolutePosition);
		m_pCanvasSprite->OnRender(IDXBase::GetInstance()->VGetDevice());
	}
}

// ***************************************************************
void cWindowControl::LoadCanvasFromFile( const Base::cString & strFileName )
{
	if(m_eWindowType != WT_DESKTOP)
	{
		m_pCanvasSprite = ISprite::CreateSprite();
		m_pCanvasSprite->Init(IDXBase::GetInstance()->VGetDevice(), strFileName);

		m_dwHeight = m_pCanvasSprite->GetScaledHeight();
		m_dwWidth = m_pCanvasSprite->GetScaledWidth();
	}
}

// ***************************************************************
void cWindowControl::Minimize( const int iWidth, const int iHeight,
							  const int iX, const int iY )
{
	if (m_eWindowType != WT_DESKTOP)
	{
		cBaseControl * pTempControl = GetFirstChild();

		while(pTempControl)
		{
			cBaseControl * pNextControl = pTempControl->GetNextSibling();
			pNextControl->SetVisible(false);
			pTempControl = pNextControl;
		}

		m_iLastNormalPosX = m_vPosition.x;
		m_iLastNormalPosY = m_vPosition.y;
		m_iLastNormalWidth = m_dwWidth;
		m_iLastNormalHeight = m_dwHeight;
		
		m_bIsMinimized = true;

		m_vPosition.x = iX;
		m_vPosition.y = iY;
		m_dwHeight = iHeight;
		m_dwWidth = iWidth;
	}
}

// ***************************************************************
void cWindowControl::Restore()
{
	if (m_eWindowType != WT_DESKTOP)
	{
		m_vPosition.x = m_iLastNormalPosX;
		m_vPosition.y = m_iLastNormalPosY;
		m_dwHeight = m_iLastNormalHeight;
		m_dwWidth = m_iLastNormalWidth;

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
