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
#include "GraphicUtils.h"

using namespace Graphics;
using namespace Utilities;
using namespace Base;

// ***************************************************************
cBaseControl::cBaseControl()
: m_vSize(cVector2::Zero())
, m_bVisible(true)
, m_pChildControls(NULL) 
, m_pNextSibling(NULL) 
, m_pPreviousSibling(NULL) 
, m_pParentControl(NULL) 
, m_iNoOfChildren(0)
, m_vPosition(cVector2::Zero())
, m_bFocus(false)
, m_pFocusControl(NULL)
, m_bIsMouseDown(false)
, m_bAllowMovingControls(false)
, m_vControlAbsolutePosition(cVector2::Zero())
{

}

// ***************************************************************
cBaseControl::~cBaseControl()
{
	VCleanup();
}

// ***************************************************************
bool cBaseControl::VPostMsg( const AppMsg & msg )
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
				VOnLeftMouseButtonDown(LOWORD(msg.m_lParam), HIWORD(msg.m_lParam));
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
				return m_pFocusControl->VOnLeftMouseButtonUp(LOWORD(msg.m_lParam), HIWORD(msg.m_lParam));
			}
		}
		break;

	case WM_MOUSEMOVE:
		pTempControl = PostToAll(msg);
		if(!pTempControl)
		{
			if (m_pFocusControl)
			{
				return m_pFocusControl->VOnMouseMove(LOWORD(msg.m_lParam), HIWORD(msg.m_lParam));
			}
		}
		break;

	case WM_KEYUP:
		pTempControl = PostToAll(msg);
		if(!pTempControl)
		{
			if(m_pFocusControl)
			{
				return m_pFocusControl->VOnKeyUp(msg);
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
				return m_pFocusControl->VOnKeyDown(msg);
			}
		}
		break;
	}
	return false;
}

// ***************************************************************
bool cBaseControl::VOnKeyDown( const AppMsg & msg )
{
	return false;
}

// ***************************************************************
bool cBaseControl::VOnKeyUp( const AppMsg & msg )
{
	return false;
}

// ***************************************************************
bool cBaseControl::VOnLeftMouseButtonDown( const int X, const int Y )
{
	m_iMouseDownXPos = X - (int)m_vControlAbsolutePosition.m_dX;
	m_iMouseDownYPos = Y - (int)m_vControlAbsolutePosition.m_dY;
	m_bIsMouseDown = true;
	return true;
}

// ***************************************************************
bool cBaseControl::VOnLeftMouseButtonUp( const int X, const int Y )
{
	if(AllowMovingControl() && m_bIsMouseDown)
		Log_Write_L3(ILogger::LT_ERROR, cString(100, "New Position - X : %f , Y : %f", m_vPosition.m_dX, m_vPosition.m_dY ));

	m_bIsMouseDown = false;
	return true;
}

// ***************************************************************
bool cBaseControl::VOnMouseMove( const int X, const int Y )
{
	if (AllowMovingControl() && m_bIsMouseDown)
	{
		double x = m_vPosition.m_dX + (X - (int)m_vControlAbsolutePosition.m_dX) - m_iMouseDownXPos;
		double y = m_vPosition.m_dY + (Y - (int)m_vControlAbsolutePosition.m_dY) - m_iMouseDownYPos;

		ConstrainChildControl(x, y);
		VSetPosition(cVector2(x, y));
		return true;
	}
	return false;
}

// ***************************************************************
void cBaseControl::VAddChildControl(IBaseControl * const pChildControl )
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
	}
}

// ***************************************************************
void cBaseControl::VRemoveAllChildren()
{
	if (m_bFocus)
	{
		m_pFocusControl = this;
	}
	cBaseControl * temp = GetFirstChild();
	while(temp)
	{
		cBaseControl * pNextControl = temp->GetNextSibling();
		SAFE_DELETE(temp);
		temp = pNextControl;
	}
	m_iNoOfChildren = 0;
	m_pChildControls = NULL;
}

// ***************************************************************
void cBaseControl::VSetSize( const cVector2 vSize)
{
	m_vSize = vSize;

	if(m_pCanvasSprite)
	{
		m_pCanvasSprite->VSetSize(m_vSize);
	}
}

// ***************************************************************
void cBaseControl::VRemoveChildControl(const IBaseControl * pChildControl)
{
	const cBaseControl * pControl = dynamic_cast<const cBaseControl * >(pChildControl);
	if(pControl)
	{
		cBaseControl * pNextControl = pControl->GetNextSibling();
		cBaseControl * pPreviousControl = pControl->GetPreviousSibling();

		SAFE_DELETE(pChildControl);
		if (pNextControl)
		{
			pNextControl->SetPreviousSibling(pPreviousControl);
		}
		if(pPreviousControl)
		{
			pPreviousControl->SetNextSibling(pNextControl);
		}
		else
		{
			m_pChildControls = pNextControl;
		}
		m_iNoOfChildren--;
	}
}

// ***************************************************************
void cBaseControl::VSetPosition( const cVector2 & vPosition )
{
	m_vPosition = vPosition;
	ConstrainChildControl(m_vPosition.m_dX, m_vPosition.m_dY);
	VSetAbsolutePosition();
}

// ***************************************************************
void cBaseControl::VSetAbsolutePosition()
{
	m_vControlAbsolutePosition = m_vPosition;
	if (m_pParentControl)
	{
		m_vControlAbsolutePosition += m_pParentControl->m_vControlAbsolutePosition;
	}
	if (m_pCanvasSprite)
	{
		m_pCanvasSprite->VSetPosition(m_vControlAbsolutePosition);
	}

	cBaseControl * pTempControl = GetFirstChild();

	while(pTempControl)
	{
		pTempControl->VSetAbsolutePosition();
		pTempControl = pTempControl->GetNextSibling();
	}
}

// ***************************************************************
void cBaseControl::VRender(const ICamera * const pCamera)
{
	if (!m_bVisible)
	{
		return;
	}

	if(m_pCanvasSprite)
	{
		m_pCanvasSprite->VRender(pCamera);
	}

	if (m_pChildControls)
	{
		RenderInReverse(m_pChildControls, pCamera);
	}

}

// ***************************************************************
float cBaseControl::VGetHeight() const
{
	return (float)m_vSize.m_dY;
}

// ***************************************************************
float cBaseControl::VGetWidth() const
{
	return (float)m_vSize.m_dX;
}

// ***************************************************************
void cBaseControl::VSetVisible( bool bIsVisible )
{
	m_bVisible = bIsVisible;
}

// *************************************************************************
void cBaseControl::VCleanup()
{
	VRemoveAllChildren();
}

// ***************************************************************
bool cBaseControl::IsCursorIntersect( const float fX, const float fY )
{
	if((fX >= m_vControlAbsolutePosition.m_dX) 
		&& (fX <= m_vControlAbsolutePosition.m_dX + VGetWidth())
		&& (fY >= m_vControlAbsolutePosition.m_dY)
		&& (fY <= m_vControlAbsolutePosition.m_dY + VGetHeight()))
		{
			return true;
		}
	return false;
}

// ***************************************************************
cBaseControl * cBaseControl::PostToAll( const AppMsg & msg )
{
	cBaseControl * pTempControl = GetFirstChild();

	while(pTempControl)
	{
		cBaseControl * pNextControl = pTempControl->GetNextSibling();
		if (pTempControl->VPostMsg(msg))
		{
			return pTempControl;
		}
		pTempControl = pNextControl;
	}
	return NULL;
}

// ***************************************************************
void cBaseControl::SetFocusControl( const cBaseControl * const pControl )
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
void cBaseControl::MoveToFront( cBaseControl * const pControl )
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
void cBaseControl::ConstrainChildControl( double & dx, double & dy )
{
	// constrain child control in parent control
	if (m_pParentControl)
	{
		if (dx < 0)
		{
			dx = 0; 
		}
		if ((dx + m_vSize.m_dX) > m_pParentControl->VGetWidth())
		{
			dx = m_pParentControl->VGetWidth() - m_vSize.m_dX; 
		}
		if (dy < 0)
		{
			dy = 0; 
		}
		if ((dy + m_vSize.m_dY) > m_pParentControl->VGetHeight())
		{
			dy = m_pParentControl->VGetHeight() - m_vSize.m_dY; 
		}
	}
}

cBaseControl * cBaseControl::GetFirstChild() const
{
	return m_pChildControls;
}

// ***************************************************************
cBaseControl * cBaseControl::GetNextSibling() const
{
	return m_pNextSibling;
}

// ***************************************************************
void cBaseControl::SetParentControl( cBaseControl * pParentControl )
{
	m_pParentControl = pParentControl;
}

// ***************************************************************
void cBaseControl::SetNextSibling( cBaseControl * pControl )
{
	m_pNextSibling = pControl;
}

// ***************************************************************
cBaseControl * cBaseControl::GetPreviousSibling() const
{
	return m_pPreviousSibling;
}

// ***************************************************************
void cBaseControl::SetPreviousSibling( cBaseControl * pControl )
{
	m_pPreviousSibling = pControl;
}

// ***************************************************************
bool cBaseControl::AllowMovingControl()
{
	if (m_pParentControl)
	{
		return m_pParentControl->AllowMovingControl();
	}
	return m_bAllowMovingControls;
}

// ***************************************************************
void cBaseControl::RenderInReverse(cBaseControl * const pControl,
											const ICamera * const pCamera)
{
	cBaseControl *  pNextControl = pControl->GetNextSibling();
	if(pNextControl)
	{
		pNextControl->RenderInReverse(pNextControl, pCamera);
	}
	pControl->VRender(pCamera);
}
