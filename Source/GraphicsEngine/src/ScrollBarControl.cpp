// ****************************************************************************
//  ScrollBarControl   version:  1.0   Ankur Sheel  date: 2012/04/24
//  ---------------------------------------------------------------------------
//  
//  ---------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ****************************************************************************
// 
// ****************************************************************************
#include "stdafx.h"
#include "ScrollBarControl.h"
#include "ButtonControl.h"
#include "DxBase.hxx"
#include "Sprite.hxx"
#include "Structures.h"

using namespace Base;
using namespace Graphics;
using namespace Utilities;

// ****************************************************************************
cScrollBarControl::cScrollBarControl()
: m_iMinPos(0)
, m_iMaxPos(0)
, m_iThumbPos(0)
, m_iNoOfIncrements(0)
, m_bDragMode(false)
, m_pBtnThumb(NULL)
, m_pBtnDecrementArrow(NULL)
, m_pBtnIncrementArrow(NULL)
{

}

// ****************************************************************************
cScrollBarControl::~cScrollBarControl()
{
	VCleanup();
}

// ****************************************************************************
void cScrollBarControl::Initialize(const cScrollBarControlDef & def)
{
	m_pBGSprite = ISprite::CreateSprite();
	m_pBGSprite->VInitialize(def.strBGImage);

	m_pBtnThumb = IBaseControl::CreateButtonControl(def.thumbBtnDef);
	m_pBtnDecrementArrow = IBaseControl::CreateButtonControl(def.TopLeftArrowDef);
	m_pBtnIncrementArrow = IBaseControl::CreateButtonControl(def.BottomRightArrowDef);

	m_iMinPos = def.iMinPos;
	m_iMaxPos = def.iMaxPos;
	m_iNoOfIncrements = m_iMaxPos - m_iMinPos;
	m_iThumbPos = def.iInitialThumbPosition - m_iMinPos;

	m_callbackIncrementArrowPressed = bind(&cScrollBarControl::IncrementArrowPressed, this, _1);
	m_pBtnIncrementArrow->VRegisterCallBack(UIET_BTNRELEASED, m_callbackIncrementArrowPressed);
	
	m_callbackDecrementArrowPressed = bind(&cScrollBarControl::DecrementArrowPressed, this, _1);
	m_pBtnDecrementArrow->VRegisterCallBack(UIET_BTNRELEASED, m_callbackDecrementArrowPressed);

	m_callbackThumbPressed = bind(&cScrollBarControl::ThumbPressed, this, _1);
	m_pBtnThumb->VRegisterCallBack(UIET_BTNPRESSED, m_callbackThumbPressed);

	m_callbackThumbReleased = bind(&cScrollBarControl::ThumbReleased, this, _1);
	m_pBtnThumb->VRegisterCallBack(UIET_BTNRELEASED, m_callbackThumbReleased);

	cBaseControl::Initialize(def);
}


// ****************************************************************************
void cScrollBarControl::VRender(const ICamera * const pCamera)
{
	if(m_bVisible)
	{
		cBaseControl::VRender(pCamera);
	
		if (m_pBtnThumb)
		{
			m_pBtnThumb->VRender(pCamera);
		}
		if (m_pBtnDecrementArrow)
		{
			m_pBtnDecrementArrow->VRender(pCamera);
		}
		if (m_pBtnIncrementArrow)
		{
			m_pBtnIncrementArrow->VRender(pCamera);
		}
	}
}

// ****************************************************************************
bool cScrollBarControl::VOnLeftMouseButtonUp( const int X, const int Y )
{
	AppMsg msg;
	msg.m_uMsg = WM_LBUTTONUP;
	msg.m_lParam = MAKELONG(X, Y);

	if(m_pBtnIncrementArrow && m_pBtnIncrementArrow->VPostMsg(msg))
	{
		return true;
	}
	else if(m_pBtnDecrementArrow && m_pBtnDecrementArrow->VPostMsg(msg))
	{
		return true;
	}
	else if(m_pBtnThumb && m_pBtnThumb->VPostMsg(msg))
	{
		return true;
	}
	return cBaseControl::VOnLeftMouseButtonUp(X, Y);
}

// ****************************************************************************
bool cScrollBarControl::VOnLeftMouseButtonDown( const int X, const int Y )
{
	AppMsg msg;
	msg.m_uMsg = WM_LBUTTONDOWN;
	msg.m_lParam = MAKELONG(X, Y);

	if(m_pBtnIncrementArrow && m_pBtnIncrementArrow->VPostMsg(msg))
	{
		return true;
	}
	if(m_pBtnDecrementArrow && m_pBtnDecrementArrow->VPostMsg(msg))
	{
		return true;
	}
	if(m_pBtnThumb && m_pBtnThumb->VPostMsg(msg))
	{
		return true;
	}

	return cBaseControl::VOnLeftMouseButtonDown(X, Y);
}

// ******************************************************************************************
void cScrollBarControl::VSetThumbPosition(const int iNewPosition)
{
	m_iThumbPos = iNewPosition;
	if (m_iThumbPos < 0)
	{
		m_iThumbPos = 0;
	}
	else if (m_iThumbPos > m_iNoOfIncrements)
	{
		m_iThumbPos = m_iNoOfIncrements;
	}
	if (UIEventCallBackFn * pFn = GetCallbackFromMap(UIET_SCBCHANGED))
	{
		stUIEventCallbackParam param;
		param.iThumbPos = m_iThumbPos;
		(*pFn)(param);
	}
}

// ****************************************************************************
void cScrollBarControl::VCleanup()
{
	cBaseControl::VCleanup();
	
	SAFE_DELETE(m_pBtnDecrementArrow);
	SAFE_DELETE(m_pBtnIncrementArrow);
	SAFE_DELETE(m_pBtnThumb);
}
// ****************************************************************************
void cScrollBarControl::IncrementArrowPressed(const stUIEventCallbackParam & params)
{
	VSetThumbPosition(m_iThumbPos + 1);
}

// ****************************************************************************
void cScrollBarControl::DecrementArrowPressed(const stUIEventCallbackParam & params)
{
	VSetThumbPosition(m_iThumbPos - 1);
}

// ****************************************************************************
void cScrollBarControl::ThumbPressed(const stUIEventCallbackParam & params)
{
	Log_Write_L3(ILogger::LT_ERROR, "Drag Mode set");
	m_bDragMode = true;
}

// ****************************************************************************
void cScrollBarControl::ThumbReleased(const stUIEventCallbackParam & params)
{
	Log_Write_L3(ILogger::LT_ERROR, "Drag Mode unset");
	m_bDragMode = false;
}