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

Graphics::cWindowControl::cWindowControl(WINDOWTYPE wType)
: m_bIsParentWindow(false)
, m_bIsMouseDown(false)
, m_iLastNormalPosX(0)
, m_iLastNormalPosY(0)
, m_iLastNormalWidth(0)
, m_iLastNormalHeight(0)
, m_bIsMinimized(false)
, m_eWindowType(wType)
{

}
// ***************************************************************

Graphics::cWindowControl::~cWindowControl()
{

}
// ***************************************************************

void Graphics::cWindowControl::LoadCanvasFromFile( const Base::cString & strFileName )
{
	if(m_eWindowType != WT_DESKTOP)
	{
		m_pCanvasSprite = ISprite::CreateSprite();
		m_pCanvasSprite->Init(IDXBase::GetInstance()->GetDevice(), strFileName);

		m_dwHeight = m_pCanvasSprite->GetScaledHeight();
		m_dwWidth = m_pCanvasSprite->GetScaledWidth();
	}
}
// ***************************************************************

void Graphics::cWindowControl::OnRender( const AppMsg & msg )
{
	if (m_eWindowType != WT_DESKTOP)
	{
		D3DXVECTOR3 vControlAbsolutePosition = D3DXVECTOR3(0.f, 0.f, 0.f);
		GetAbsolutePosition(vControlAbsolutePosition);

		m_pCanvasSprite->SetPosition(vControlAbsolutePosition);
		m_pCanvasSprite->Render(IDXBase::GetInstance()->GetDevice());
	}
}
// ***************************************************************

void Graphics::cWindowControl::OnMouseDown( const int iButton, const int X, const int Y )
{
	if (m_eWindowType != WT_DESKTOP)
	{
		D3DXVECTOR3 vControlAbsolutePosition = D3DXVECTOR3(0.f, 0.f, 0.f);
		GetAbsolutePosition(vControlAbsolutePosition);
		
		m_iX = X - vControlAbsolutePosition.x;
		m_iY = Y - vControlAbsolutePosition.y;
		m_bIsMouseDown = true;
	}
}
// ***************************************************************

void Graphics::cWindowControl::OnMouseMove( const int X, const int Y )
{
	if (m_eWindowType != WT_DESKTOP)
	{
		if (!m_bIsMouseDown)
		{
			D3DXVECTOR3 vControlAbsolutePosition = D3DXVECTOR3(0.f, 0.f, 0.f);
			GetAbsolutePosition(vControlAbsolutePosition);

			m_vPosition.x = m_vPosition.x + (X - vControlAbsolutePosition.x) - m_iX;
			m_vPosition.y = m_vPosition.y + (Y - vControlAbsolutePosition.y) - m_iY;
		}
	}
}
// ***************************************************************

void Graphics::cWindowControl::OnMouseUp( const int iButton, const int X, const int Y )
{
	if (m_eWindowType != WT_DESKTOP)
	{
		m_bIsMouseDown = false;
	}
}

void Graphics::cWindowControl::Minimize( const int iWidth, const int iHeight, const int iX, const int iY )
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

void Graphics::cWindowControl::Restore()
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

IBaseControl * Graphics::IBaseControl::CreateWindowControl(WINDOWTYPE wType)
{
	cWindowControl * pControl = DEBUG_NEW cWindowControl(wType);
	return pControl;
}
// ***************************************************************
