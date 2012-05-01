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
Graphics::cScrollBarControl::cScrollBarControl()
: m_iMinPos(0)
, m_iMaxPos(0)
, m_iThumbPos(0)
, m_iNoOfIncrements(0)
, m_fRange(0)
, m_bDragMode(false)
, m_pBtnThumb(NULL)
, m_pBtnDecrementArrow(NULL)
, m_pBtnIncrementArrow(NULL)
{

}

// ***************************************************************
Graphics::cScrollBarControl::~cScrollBarControl()
{
	Cleanup();
}

// ***************************************************************
void Graphics::cScrollBarControl::VOnRender( const AppMsg & msg )
{
	if (m_pBtnThumb)
	{
		m_pBtnThumb->VOnRender(msg);
	}
	if (m_pBtnDecrementArrow)
	{
		m_pBtnDecrementArrow->VOnRender(msg);
	}
	if (m_pBtnIncrementArrow)
	{
		m_pBtnIncrementArrow->VOnRender(msg);
	}
}

// ***************************************************************
void Graphics::cScrollBarControl::VOnLostDevice()
{
	if (m_pBtnThumb)
	{
		m_pBtnThumb->VOnLostDevice();
	}
	if (m_pBtnDecrementArrow)
	{
		m_pBtnDecrementArrow->VOnLostDevice();
	}
	if (m_pBtnIncrementArrow)
	{
		m_pBtnIncrementArrow->VOnLostDevice();
	}
	cBaseControl::VOnLostDevice();
}

// ***************************************************************
HRESULT Graphics::cScrollBarControl::VOnResetDevice()
{
	if (m_pBtnThumb)
	{
		m_pBtnThumb->VOnResetDevice();
	}
	if (m_pBtnDecrementArrow)
	{
		m_pBtnDecrementArrow->VOnResetDevice();
	}
	if (m_pBtnIncrementArrow)
	{
		m_pBtnIncrementArrow->VOnResetDevice();
	}
	return cBaseControl::VOnResetDevice();
	
}

// ***************************************************************
bool Graphics::cScrollBarControl::VOnLeftMouseButtonUp( const int X, const int Y )
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
bool Graphics::cScrollBarControl::VOnLeftMouseButtonDown( const int X, const int Y )
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
void Graphics::cScrollBarControl::Init( const Base::cString & strBackgroundImage,
									   const Base::cString & strDefaultThumbImage,
									   const Base::cString & strPressedThumbImage,
									   const Base::cString & strDefaultMinImage,
									   const Base::cString & strPressedMinImage,
									   const Base::cString & strDefaultMaxImage,
									   const Base::cString & strPressedMaxImage,
									   const int iMinPos, const int iMaxPos )
{
	m_pCanvasSprite = ISprite::CreateSprite();
	m_pCanvasSprite->Init(IDXBase::GetInstance()->VGetDevice(), strBackgroundImage);

	m_pBtnThumb = IBaseControl::CreateButtonControl(strDefaultThumbImage, strPressedThumbImage);
	m_pBtnDecrementArrow = IBaseControl::CreateButtonControl(strDefaultMinImage, strDefaultMinImage);
	m_pBtnIncrementArrow = IBaseControl::CreateButtonControl(strDefaultMaxImage, strPressedMaxImage);

	m_iMinPos = iMinPos;
	m_iMaxPos = iMaxPos;
	m_iNoOfIncrements = m_iMaxPos - m_iMinPos;
	VSetThumbPosition(0);

	m_callbackIncrementArrowPressed = bind(&cScrollBarControl::IncrementArrowPressed, this, _1);
	m_pBtnIncrementArrow->VRegisterCallBack(m_callbackIncrementArrowPressed);
	
	m_callbackDecrementArrowPressed = bind(&cScrollBarControl::DecrementArrowPressed, this, _1);
	m_pBtnDecrementArrow->VRegisterCallBack(m_callbackDecrementArrowPressed);

	m_callbackThumbPressed = bind(&cScrollBarControl::ThumbPressed, this, _1);
	m_pBtnThumb->VRegisterCallBack(m_callbackThumbPressed);
}

// ***************************************************************
void Graphics::cScrollBarControl::VSetThumbPosition( const int iNewPosition )
{

}
// ***************************************************************
void Graphics::cScrollBarControl::IncrementArrowPressed( bool bPressed )
{
	if (!bPressed)
	{
		VSetThumbPosition(m_iThumbPos + 1);
	}
}

// ***************************************************************
void Graphics::cScrollBarControl::DecrementArrowPressed( bool bPressed )
{
	if(!bPressed)
	{
		VSetThumbPosition(m_iThumbPos - 1);
	}
}

// ***************************************************************
void Graphics::cScrollBarControl::ThumbPressed( bool bPressed )
{
	Log_Write_L1(ILogger::LT_ERROR, cString(100, " Drag Mode %d", bPressed));
	m_bDragMode = bPressed;
}
// ***************************************************************
void Graphics::cScrollBarControl::Cleanup()
{
	SAFE_DELETE(m_pBtnDecrementArrow);
	SAFE_DELETE(m_pBtnIncrementArrow);
	SAFE_DELETE(m_pBtnThumb);
}
