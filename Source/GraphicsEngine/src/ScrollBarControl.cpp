// ***************************************************************
//  ScrollBarControl   version:  1.0   Ankur Sheel  date: 2012/04/24
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "ScrollBarControl.h"
#include "ButtonControl.h"
#include "DxBase.hxx"
#include "Sprite.hxx"
#include "Logger.hxx"
#include "Structures.h"

using namespace Base;
using namespace Graphics;
using namespace Utilities;

// ***************************************************************
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

// ***************************************************************
cScrollBarControl::~cScrollBarControl()
{
	VCleanup();
}

// ***************************************************************
void cScrollBarControl::Initialize(const stScrollBarControlDef & def)
{
	m_pBGSprite = ISprite::CreateSprite();
	m_pBGSprite->VInitialize(def.strBGImage);

	m_pBtnThumb = IBaseControl::CreateButtonControl(def.thumbBtnDef);
	m_pBtnDecrementArrow = IBaseControl::CreateButtonControl(def.TopLeftArrowDef);
	m_pBtnIncrementArrow = IBaseControl::CreateButtonControl(def.BottomRightArrowDef);

	m_iMinPos = def.iMinPos;
	m_iMaxPos = def.iMaxPos;
	m_iNoOfIncrements = m_iMaxPos - m_iMinPos;
	VSetThumbPosition(def.iInitialThumbPosition - m_iMinPos);

	m_callbackIncrementArrowPressed = bind(&cScrollBarControl::IncrementArrowPressed, this, _1);
	m_pBtnIncrementArrow->VRegisterCallBack(m_callbackIncrementArrowPressed);
	
	m_callbackDecrementArrowPressed = bind(&cScrollBarControl::DecrementArrowPressed, this, _1);
	m_pBtnDecrementArrow->VRegisterCallBack(m_callbackDecrementArrowPressed);

	m_callbackThumbPressed = bind(&cScrollBarControl::ThumbPressed, this, _1);
	m_pBtnThumb->VRegisterCallBack(m_callbackThumbPressed);
}

// ***************************************************************
void cScrollBarControl::VRender(const ICamera * const pCamera)
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

// ***************************************************************
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

// ***************************************************************
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

// ***************************************************************
void cScrollBarControl::IncrementArrowPressed( bool bPressed )
{
	if (!bPressed)
	{
		VSetThumbPosition(m_iThumbPos + 1);
	}
}

// ***************************************************************
void cScrollBarControl::DecrementArrowPressed( bool bPressed )
{
	if(!bPressed)
	{
		VSetThumbPosition(m_iThumbPos - 1);
	}
}

// ***************************************************************
void cScrollBarControl::ThumbPressed( bool bPressed )
{
	Log_Write_L1(ILogger::LT_ERROR, cString(100, " Drag Mode %d", bPressed));
	m_bDragMode = bPressed;
}
// ***************************************************************
void cScrollBarControl::VCleanup()
{
	cBaseControl::VCleanup();
	
	SAFE_DELETE(m_pBtnDecrementArrow);
	SAFE_DELETE(m_pBtnIncrementArrow);
	SAFE_DELETE(m_pBtnThumb);
}