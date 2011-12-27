// ***************************************************************
//  BaseControl   version:  1.0   Ankur Sheel  date: 2011/07/21
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "BaseControl.h"
#include "Sprite.hxx"
#include "Structures.h"

using namespace Graphics;
using namespace Utilities;
using namespace Base;

cBaseControl::cBaseControl()
: m_dwWidth(0)
, m_dwHeight(0)
, m_bVisible(true)
, m_pChildControls(NULL) 
, m_pNextSibling(NULL) 
, m_pPreviousSibling(NULL) 
, m_pParentControl(NULL) 
, m_iNoOfChildren(0)
, m_vPosition(D3DXVECTOR2(0.0f, 0.0f))
, m_bFocus(false)
, m_pFocusControl(NULL)
, m_bIsMouseDown(false)
, m_vPrevControlPosition(D3DXVECTOR3(0.f, 0.f, 0.f))
{

}
// ***************************************************************

cBaseControl::~cBaseControl()
{
	RemoveAllChildren();

}
// ***************************************************************

IBaseControl * cBaseControl::AddChildControl(IBaseControl * const pChildControl )
{
	cBaseControl * const pControl = dynamic_cast<cBaseControl * const>(pChildControl);
	if (pControl)
	{
		pControl->SetParentControl(this);

		if (!m_pChildControls)
		{
			m_pChildControls = pControl;
		}
		else
		{
			cBaseControl * temp = GetFirstChild();

			while (temp->GetNextSibling())
			{
				temp = temp->GetNextSibling();
			}

			temp->SetNextSibling(pControl);
			pControl->SetPreviousSibling(temp);
		}
		m_iNoOfChildren++;
		return pControl;
	}
	return NULL;
}
// ***************************************************************

const cBaseControl * cBaseControl::RemoveChildControl( const cBaseControl * pChildControl )
{
	cBaseControl * pNextControl = pChildControl->GetNextSibling();
	cBaseControl * pPreviousControl = pChildControl->GetPreviousSibling();
	SAFE_DELETE(pChildControl);
	pNextControl->SetPreviousSibling(pPreviousControl);
	pPreviousControl->SetNextSibling(pNextControl);
	pChildControl = pNextControl;

	m_iNoOfChildren--;

	return pChildControl;
}
// ***************************************************************

void cBaseControl::RemoveAllChildren()
{
	cBaseControl * temp = GetFirstChild();

	while(temp)
	{
		cBaseControl * pNextControl = temp->GetNextSibling();
		SAFE_DELETE(temp);
		temp = pNextControl;
	}
	m_iNoOfChildren = 0;
}
// ***************************************************************

void cBaseControl::GetAbsolutePosition( D3DXVECTOR3 & vPosition ) const
{
	vPosition.x += m_vPosition.x;
	vPosition.y += m_vPosition.y;

	if (m_pParentControl)
	{
		m_pParentControl->GetAbsolutePosition(vPosition);
	}
}
// ***************************************************************

bool Graphics::cBaseControl::IsCursorIntersect( const float fX, const float fY )
{
	D3DXVECTOR3 vControlAbsolutePosition = D3DXVECTOR3(0.f,0.f, 0.f);

	GetAbsolutePosition(vControlAbsolutePosition);


	if((fX >= vControlAbsolutePosition.x) && (fX <= vControlAbsolutePosition.x + GetWidth()))
	{
		if((fY >= vControlAbsolutePosition.y) && (fY <= vControlAbsolutePosition.y + GetHeight()))
		{
			return true;
		}
	}
	return false;
}
// ***************************************************************

bool Graphics::cBaseControl::PostMsg( const AppMsg & msg )
{
	cBaseControl * pTempControl = NULL;
	switch(msg.m_uMsg)
	{
	case WM_LBUTTONDOWN:
		if(IsCursorIntersect(LOWORD(msg.m_lParam), HIWORD(msg.m_lParam)))
		{
			pTempControl = PostToAll(msg);
			if(!pTempControl)
			{
				OnMouseDown(msg.m_uMsg, LOWORD(msg.m_lParam), HIWORD(msg.m_lParam));
				if (m_pParentControl)
				{
					m_pParentControl->MoveToFront(this);
				}
				SetFocusControl(this);
			}
			return true;
		}
		break;

	case WM_LBUTTONUP:
		pTempControl = PostToAll(msg);
		if(!pTempControl)
		{
			if (m_pFocusControl)
			{
				m_pFocusControl->OnMouseUp(msg.m_uMsg, LOWORD(msg.m_lParam), HIWORD(msg.m_lParam));
			}
		}
		break;

	case WM_MOUSEMOVE:
		pTempControl = PostToAll(msg);
		if(!pTempControl)
		{
			if (m_pFocusControl)
			{
				return m_pFocusControl->OnMouseMove(LOWORD(msg.m_lParam), HIWORD(msg.m_lParam));
			}
		}
		break;

	case WM_KEYUP:
		pTempControl = PostToAll(msg);
		if(!pTempControl)
		{
			if(m_pFocusControl)
			{
				return m_pFocusControl->OnKeyUp(msg);
			}
		}
		break;

	case WM_KEYDOWN:
	case WM_CHAR:
		pTempControl = PostToAll(msg);
		if(!pTempControl)
		{
			if(m_pFocusControl)
			{
				return m_pFocusControl->OnKeyDown(msg);
			}
		}
		break;

	case WM_RENDER:
		if (m_bVisible)
		{
			OnRender(msg);
			if (m_pChildControls)
			{
				PostToAllReverse(m_pChildControls, msg);
			}
		}
		break;

	case WM_DEVICELOST:
		OnLostDevice();
		if (m_pChildControls)
		{
			PostToAll(msg);
		}
		break;

	case WM_DEVICERESET:
		OnResetDevice();
		if (m_pChildControls)
		{
			PostToAllReverse(m_pChildControls, msg);
		}
		break;
	}
	return false;
}
// ***************************************************************

cBaseControl * Graphics::cBaseControl::PostToAll( const AppMsg & msg )
{
	cBaseControl * pTempControl = GetFirstChild();

	while(pTempControl)
	{
		cBaseControl * pNextControl = pTempControl->GetNextSibling();
		if (pTempControl->PostMsg(msg))
		{
			return pTempControl;
		}
		pTempControl = pNextControl;
	}
	return NULL;
}
// ***************************************************************

void Graphics::cBaseControl::SetFocusControl( const cBaseControl * const pControl )
{
	if (!m_bFocus || m_pFocusControl != pControl)
	{
		if (m_pParentControl)
		{
			m_pParentControl->SetFocusControl(pControl);
		}
		else
		{
			m_bFocus =true;
			if(m_pFocusControl)
			{
				m_pFocusControl->m_bFocus = false;
			}
			
			m_pFocusControl = const_cast<cBaseControl *>(pControl);
			if (m_pFocusControl)
			{
				m_pFocusControl->m_bFocus = true;
			}
		}
	}
}
// ***************************************************************

void Graphics::cBaseControl::PostToAllReverse( cBaseControl * const pControl, const AppMsg & msg )
{
	cBaseControl *  pNextControl = pControl->GetNextSibling();
	if(pNextControl)
	{
		pNextControl->PostToAllReverse(pNextControl, msg);
	}
	pControl->PostMsg(msg);
}
// ***************************************************************

void Graphics::cBaseControl::MoveToFront( cBaseControl * const pControl )
{
	cBaseControl * pNextControl = pControl->GetNextSibling();
	cBaseControl * pPrevControl = pControl->GetPreviousSibling();

	if (pPrevControl) // not in front
	{
		pPrevControl->SetNextSibling(pNextControl);
		if (pNextControl)
		{
			pNextControl->SetPreviousSibling(pPrevControl);
		}
	}
	else
	{
		return;
	}

	pControl->SetNextSibling(m_pChildControls);
	m_pChildControls->SetPreviousSibling(pControl);
	pControl->SetPreviousSibling(NULL);
	m_pChildControls = pControl;

}
// ***************************************************************

bool Graphics::cBaseControl::OnMouseDown( const int iButton, const int X, const int Y )
{
	D3DXVECTOR3 vControlAbsolutePosition = D3DXVECTOR3(0.f, 0.f, 0.f);
	GetAbsolutePosition(vControlAbsolutePosition);

	m_iMouseDownXPos = X - vControlAbsolutePosition.x;
	m_iMouseDownYPos = Y - vControlAbsolutePosition.y;
	m_bIsMouseDown = true;
	return true;
}
// ***************************************************************

bool Graphics::cBaseControl::OnMouseMove( const int X, const int Y )
{
	if (m_bIsMouseDown)
	{
		D3DXVECTOR3 vControlAbsolutePosition = D3DXVECTOR3(0.f, 0.f, 0.f);
		GetAbsolutePosition(vControlAbsolutePosition);

		float x = m_vPosition.x + (X - vControlAbsolutePosition.x) - m_iMouseDownXPos;
		float y = m_vPosition.y + (Y - vControlAbsolutePosition.y) - m_iMouseDownYPos;

		ConstrainChildControl(x, y);
		m_vPosition.x = x;
		m_vPosition.y = y;
		return true;
	}
	return false;
}
// ***************************************************************

bool Graphics::cBaseControl::OnMouseUp( const int iButton, const int X, const int Y )
{
	m_bIsMouseDown = false;
	return true;
}
// ***************************************************************

bool Graphics::cBaseControl::IsPositionChanged( const D3DXVECTOR3 & vControlPosition )
{
	if (m_vPrevControlPosition != vControlPosition)
	{
		return true;
	}
	return false;
}
// ***************************************************************

void Graphics::cBaseControl::SetSize( const float fNewWidth, const float fNewHeight )
{
	m_dwHeight = fNewHeight;
	m_dwWidth = fNewWidth;

	if(m_pCanvasSprite)
	{
		m_pCanvasSprite->SetSize(m_dwWidth, m_dwHeight);
	}
}
// ***************************************************************

void Graphics::cBaseControl::RenderPrivate( D3DXVECTOR3 & vControlAbsolutePosition, bool & bIsPositionChanged )
{

	vControlAbsolutePosition = D3DXVECTOR3(0.f, 0.f, 0.f);
	GetAbsolutePosition(vControlAbsolutePosition);

	bIsPositionChanged = IsPositionChanged(vControlAbsolutePosition);
	if (bIsPositionChanged)
	{
		if (m_dwWidth == 0 || m_dwHeight == 0)
		{
			Log_Write_L1(ILogger::LT_ERROR, cString(100, "Label control height or width is 0"));
		}
		m_vPrevControlPosition = vControlAbsolutePosition;
	}
}
// ***************************************************************

void Graphics::cBaseControl::ConstrainChildControl( float &x, float &y )
{
	// constrain child control in parent control
	if (m_pParentControl)
	{
		if (x < 0)
		{
			x = 0; 
		}
		if ((x + m_dwWidth) > m_pParentControl->GetWidth())
		{
			x = m_pParentControl->GetWidth() - m_dwWidth; 
		}
		if (y < 0)
		{
			y = 0; 
		}
		if ((y + m_dwHeight) > m_pParentControl->GetHeight())
		{
			y = m_pParentControl->GetHeight() - m_dwHeight; 
		}
	}
}
// ***************************************************************

bool Graphics::cBaseControl::OnKeyDown( const AppMsg & msg )
{
	return false;
}
// ***************************************************************

bool Graphics::cBaseControl::OnKeyUp( const AppMsg & msg )
{
	return false;
}
// ***************************************************************

void Graphics::cBaseControl::OnLostDevice()
{
	if (m_pCanvasSprite)
	{
		m_pCanvasSprite->OnLostDevice();
	}
		
}
// ***************************************************************

HRESULT Graphics::cBaseControl::OnResetDevice()
{
	if (m_pCanvasSprite)
	{
		m_pCanvasSprite->OnResetDevice();
		return S_OK;
	}

}
// ***************************************************************
