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
using namespace std;
// ***************************************************************
cBaseControl::cBaseControl()
: m_vSize(cVector2::Zero())
, m_bVisible(true)
, m_pParentControl(NULL) 
, m_vPosition(cVector2::Zero())
, m_bFocus(false)
, m_pFocusControl(NULL)
, m_bIsMouseDown(false)
, m_bAllowMovingControls(false)
, m_vControlAbsolutePosition(cVector2::Zero())
, m_pfnCallBack(NULL)
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
void cBaseControl::VAddChildControl(IBaseControl * const pChildControl )
{
	cBaseControl * const pControl = static_cast<cBaseControl * const>(pChildControl);
	if (pControl)
	{
		pControl->SetParentControl(this);
		m_pChildControl.push_back(pControl);
	}
}

// ***************************************************************
void cBaseControl::VRemoveAllChildren()
{
	if (m_bFocus)
	{
		m_pFocusControl = this;
	}
	/*list<IBaseControl * const>::iterator iter;
	for(iter = m_pChildControl.begin(); iter != m_pChildControl.end(); iter++)
	{
		SAFE_DELETE(*iter);
	}*/
	m_pChildControl.clear();
}

// ***************************************************************
void cBaseControl::VRemoveChildControl(const IBaseControl * const pChildControl)
{
	list<cBaseControl * const>::iterator iter = GetChildControlIterator(pChildControl);
	if(iter != m_pChildControl.end())
	{
		m_pChildControl.erase(iter);
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
void cBaseControl::VSetSize( const cVector2 & vSize)
{
	m_vSize = vSize;

	if(m_pCanvasSprite)
	{
		m_pCanvasSprite->VSetSize(m_vSize);
	}
}

// *************************************************************************
void cBaseControl::VRegisterCallBack(function <void (bool)> callback)
{
	m_pfnCallBack = callback;
}

// *************************************************************************
void cBaseControl::VUnregisterCallBack()
{
	m_pfnCallBack = NULL;
}

// ***************************************************************
void cBaseControl::VSetText(const Base::cString & strText)
{
	Log_Write_L1(ILogger::LT_ERROR, "This function should be implemented in a child class.")
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
bool cBaseControl::VOnLeftMouseButtonDown( const int X, const int Y )
{
	m_iMouseDownXPos = X - (int)m_vControlAbsolutePosition.m_dX;
	m_iMouseDownYPos = Y - (int)m_vControlAbsolutePosition.m_dY;
	m_bIsMouseDown = true;
	return true;
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

	list<cBaseControl * const>::reverse_iterator iter;
	for(iter = m_pChildControl.rbegin(); iter != m_pChildControl.rend(); iter++)
	{
		(*iter)->VRender(pCamera);
	}
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

	list<cBaseControl * const>::iterator iter;
	for(iter = m_pChildControl.begin(); iter != m_pChildControl.end(); iter++)
	{
		(*iter)->VSetAbsolutePosition();
	}
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
	list<cBaseControl * const>::iterator iter;
	for(iter = m_pChildControl.begin(); iter != m_pChildControl.end(); iter++)
	{
		if((*iter)->VPostMsg(msg))
		{
			return (*iter);
		}
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
	list<cBaseControl * const>::iterator iter = GetChildControlIterator(pControl);
	if(iter != m_pChildControl.end() && iter != m_pChildControl.begin())
	{
		m_pChildControl.splice(m_pChildControl.begin(), m_pChildControl, iter);
	}
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

// ***************************************************************
void cBaseControl::SetParentControl( cBaseControl * pParentControl )
{
	m_pParentControl = pParentControl;
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
list<cBaseControl * const>::iterator cBaseControl::GetChildControlIterator(const IBaseControl * const pChildControl)
{
	list<cBaseControl * const>::iterator iter;
	for(iter = m_pChildControl.begin(); iter != m_pChildControl.end(); iter++)
	{
		if(*iter == pChildControl)
		{
			break;
		}
	}
	if(iter == m_pChildControl.end())
	{
		Log_Write_L1(ILogger::LT_ERROR, "Could not find Child contron in Base Control");
	}
	return iter;
}
