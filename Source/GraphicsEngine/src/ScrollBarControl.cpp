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
cScrollBarControl* Graphics::cScrollBarControl::Create()
{
	return (DEBUG_NEW cScrollBarControl());
}

// ***************************************************************
bool Graphics::cScrollBarControl::VPostMsg( const AppMsg & msg )
{
	switch(msg.m_uMsg)
	{
	case WM_LBUTTONDOWN:
		if(IsCursorIntersect(LOWORD(msg.m_lParam), HIWORD(msg.m_lParam)))
		{
			if(m_pBtnIncrementArrow && m_pBtnIncrementArrow->VPostMsg(msg))
			{
				break;
			}
			if(m_pBtnDecrementArrow && m_pBtnDecrementArrow->VPostMsg(msg))
			{
				break;
			}
			if(m_pBtnThumb && m_pBtnThumb->VPostMsg(msg))
			{
				break;
			}
		}
		break;
	
	case WM_LBUTTONUP:
		if(m_pBtnIncrementArrow && m_pBtnIncrementArrow->VPostMsg(msg))
		{
			break;
		}
		else if(m_pBtnDecrementArrow && m_pBtnDecrementArrow->VPostMsg(msg))
		{
			break;
		}
		else if(m_pBtnThumb && m_pBtnThumb->VPostMsg(msg))
		{
			break;
		}
		break;
	}
	return 	cBaseControl::VPostMsg(msg);
	
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
bool Graphics::cScrollBarControl::VOnMouseMove( const int X, const int Y )
{
	if (m_bDragMode)
	{
		int iThumbPos = m_iThumbPos;
		float fVal = m_pBtnDecrementArrow->VGetHeight() + Y 
			- (m_vControlAbsolutePosition.y + m_pBtnIncrementArrow->VGetHeight());

		if(fVal >= m_pBtnIncrementArrow->VGetHeight())
		{
			if(fVal < (m_fHeight - m_pBtnDecrementArrow->VGetHeight()))
			{
				float fRange = (m_fHeight - m_pBtnIncrementArrow->VGetHeight()) -
					m_pBtnDecrementArrow->VGetHeight();
				float fIncrement = fRange / m_iNoOfIncrements;
				for(int counter = m_iMinPos; counter < m_iNoOfIncrements; counter++)
				{
					float fItem = m_pBtnDecrementArrow->VGetHeight() + (fIncrement * counter);
					if(((fVal >= fItem)) && (fVal<= (fItem + fIncrement)))
					{
						iThumbPos = counter;
						break;
					}
				}
			}
		}
		SetThumbPosition(iThumbPos);
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "ThumbPos % d" , iThumbPos));
		return true;
	}
	return  cBaseControl::VOnMouseMove(X, Y);
}

// ***************************************************************
void Graphics::cScrollBarControl::VSetAbsolutePosition()
{
	cBaseControl::VSetAbsolutePosition();
	D3DXVECTOR3 pos = m_vControlAbsolutePosition;
	if (m_pBtnDecrementArrow)
	{
		pos.y = m_vControlAbsolutePosition.y + m_iMinPos;
		m_pBtnDecrementArrow->VSetPosition(pos);
	}
	if (m_pBtnIncrementArrow)
	{
		pos.y = m_vControlAbsolutePosition.y + m_fHeight - m_pBtnIncrementArrow->VGetHeight();
		m_pBtnIncrementArrow->VSetPosition(pos);
	}	
	SetThumbPosition(m_iThumbPos);
}

// ***************************************************************
void Graphics::cScrollBarControl::VSetSize( const float fNewWidth, const float fNewHeight )
{
	cBaseControl::VSetSize(fNewWidth, fNewHeight);
	if (m_pBtnDecrementArrow)
	{
		m_pBtnDecrementArrow->VSetSize(fNewWidth, fNewWidth);
	}
	if (m_pBtnIncrementArrow)
	{
		m_pBtnIncrementArrow->VSetSize(fNewWidth, fNewWidth);
	}
	if (m_pBtnThumb)
	{
		AutoSize();
	}
	VSetAbsolutePosition();
}

// ***************************************************************
void Graphics::cScrollBarControl::Init(const cString & strBackgroundImage,
									   const cString & strDefaultThumbImage,
									   const cString & strPressedThumbImage,
									   const cString & strDefaultTopRightImage,
									   const cString & strPressedTopRightImage,
									   const cString & strDefaultLeftBottomImage,
									   const cString & strPressedLeftBottomImage,
									   const int iLeftTopPos, const int iRightBottomPos)
{
	m_pCanvasSprite = ISprite::CreateSprite();
	m_pCanvasSprite->Init(IDXBase::GetInstance()->VGetDevice(), strBackgroundImage);

	m_pBtnThumb = IBaseControl::CreateButtonControl(strDefaultThumbImage, strPressedThumbImage);
	m_pBtnDecrementArrow = IBaseControl::CreateButtonControl(strDefaultTopRightImage, strDefaultTopRightImage);
	m_pBtnIncrementArrow = IBaseControl::CreateButtonControl(strDefaultLeftBottomImage, strPressedLeftBottomImage);

	SetLeftTopPosition(iLeftTopPos);
	SetRightBottomPosition(iRightBottomPos);
	m_iNoOfIncrements = m_iMaxPos - m_iMinPos;
	SetThumbPosition(0);

	m_callbackIncrementArrowPressed = bind(&cScrollBarControl::IncrementArrowPressed, this, _1);
	m_pBtnIncrementArrow->VRegisterCallBack(m_callbackIncrementArrowPressed);
	
	m_callbackDecrementArrowPressed = bind(&cScrollBarControl::DecrementArrowPressed, this, _1);
	m_pBtnDecrementArrow->VRegisterCallBack(m_callbackDecrementArrowPressed);

	m_callbackThumbPressed = bind(&cScrollBarControl::ThumbPressed, this, _1);
	m_pBtnThumb->VRegisterCallBack(m_callbackThumbPressed);
}

// ***************************************************************
void Graphics::cScrollBarControl::SetLeftTopPosition( const int iLeftTopPos )
{
	m_iMinPos = iLeftTopPos;
}

// ***************************************************************
void Graphics::cScrollBarControl::SetRightBottomPosition( const int iRightBottomPos )
{
	m_iMaxPos = iRightBottomPos;
}

// ***************************************************************
void Graphics::cScrollBarControl::AutoSize()
{
	m_fRange = m_fHeight - m_pBtnIncrementArrow->VGetHeight() - m_pBtnDecrementArrow->VGetHeight();
	float fNewHeight = m_fRange / m_iNoOfIncrements ;
	m_pBtnThumb->VSetSize(m_fWidth, fNewHeight);
}

// ***************************************************************
void Graphics::cScrollBarControl::SetThumbPosition( const int iNewPosition )
{
	m_iThumbPos = iNewPosition;
	if (m_iThumbPos < m_iMinPos)
	{
		m_iThumbPos = m_iMinPos;
	}
	else if (m_iThumbPos >= m_iNoOfIncrements)
	{
		m_iThumbPos = m_iNoOfIncrements - 1;
	}
	
	D3DXVECTOR3 pos = m_vControlAbsolutePosition;
	if (m_pBtnThumb)
	{
		pos.y = m_vControlAbsolutePosition.y + m_pBtnDecrementArrow->VGetHeight() + (m_pBtnThumb->VGetHeight() * m_iThumbPos);
		m_pBtnThumb->VSetPosition(pos);
	}
}

// ***************************************************************
void Graphics::cScrollBarControl::IncrementArrowPressed( bool bPressed )
{
	if (!bPressed)
	{
		SetThumbPosition(m_iThumbPos + 1);
	}
}

// ***************************************************************
void Graphics::cScrollBarControl::DecrementArrowPressed( bool bPressed )
{
	if(!bPressed)
	{
		SetThumbPosition(m_iThumbPos - 1);
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

// ***************************************************************
IBaseControl * IBaseControl::CreateScrollBarControl(const cString & strBackgroundImage,
													const cString & strDefaultThumbImage,
													const cString & strPressedThumbImage,
													const cString & strDefaultTopRightImage,
													const cString & strPressedTopRightImage,
													const cString & strDefaultLeftBottomImage,
													const cString & strPressedLeftBottomImage,
													const int iLeftTopPos, const int iRightBottomPos)
{
	cScrollBarControl * pControl = cScrollBarControl::Create();
	pControl->Init(strBackgroundImage, strDefaultThumbImage, strPressedThumbImage,
				strDefaultTopRightImage, strPressedTopRightImage, strDefaultLeftBottomImage,
				strPressedLeftBottomImage, iLeftTopPos, iRightBottomPos);
	return pControl;

}
