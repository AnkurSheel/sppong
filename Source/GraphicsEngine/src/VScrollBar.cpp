// ***************************************************************
//  VScrollBar   version:  1.0   Ankur Sheel  date: 2012/04/29
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "VScrollBar.h"
#include "Logger.hxx"
#include "Sprite.hxx"

using namespace Graphics;
using namespace Utilities;
using namespace Base;

// ***************************************************************
Graphics::cVScrollBar::cVScrollBar()
{

}

// ***************************************************************
Graphics::cVScrollBar::~cVScrollBar()
{

}

// ***************************************************************
cVScrollBar* Graphics::cVScrollBar::Create()
{
	return (DEBUG_NEW cVScrollBar());
}

// ***************************************************************
bool Graphics::cVScrollBar::VOnMouseMove( const int X, const int Y )
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
		VSetThumbPosition(iThumbPos);
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "ThumbPos % d" , iThumbPos));
		return true;
	}
	return  cBaseControl::VOnMouseMove(X, Y);
}

// ***************************************************************
void Graphics::cVScrollBar::VSetAbsolutePosition()
{
	cScrollBarControl::VSetAbsolutePosition();
	D3DXVECTOR3 pos = m_vControlAbsolutePosition;
	if (m_pBtnDecrementArrow)
	{
		pos.y = m_vControlAbsolutePosition.y + m_iMinPos;
		m_pBtnDecrementArrow->VSetPosition(pos);
		if (m_pCanvasSprite)
		{
			pos.y += m_pBtnDecrementArrow->VGetHeight();
			m_pCanvasSprite->SetPosition(pos);
		}
	}
	if (m_pBtnIncrementArrow)
	{
		pos.y = m_vControlAbsolutePosition.y + m_fHeight - m_pBtnIncrementArrow->VGetHeight();
		m_pBtnIncrementArrow->VSetPosition(pos);
	}	
	VSetThumbPosition(m_iThumbPos);
}

// ***************************************************************
void Graphics::cVScrollBar::VSetSize( const float fNewWidth, const float fNewHeight )
{
	cBaseControl::VSetSize(fNewWidth, fNewHeight);
	float fBackGroundHeight = fNewHeight;
	if (m_pBtnDecrementArrow)
	{
		m_pBtnDecrementArrow->VSetSize(fNewWidth, fNewWidth);
		fBackGroundHeight -= fNewWidth;
	}
	if (m_pBtnIncrementArrow)
	{
		m_pBtnIncrementArrow->VSetSize(fNewWidth, fNewWidth);
		fBackGroundHeight -= fNewWidth;
	}
	if(m_pCanvasSprite)
	{
		m_pCanvasSprite->SetSize(m_fWidth, fBackGroundHeight);
	}
	if (m_pBtnThumb)
	{
		AutoSize();
	}
	VSetAbsolutePosition();
}


// ***************************************************************
void Graphics::cVScrollBar::VSetThumbPosition( const int iNewPosition )
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
void Graphics::cVScrollBar::AutoSize()
{
	m_fRange = m_fHeight - m_pBtnIncrementArrow->VGetHeight() - m_pBtnDecrementArrow->VGetHeight();
	float fNewHeight = m_fRange / m_iNoOfIncrements ;
	m_pBtnThumb->VSetSize(m_fWidth, fNewHeight);
}

// ***************************************************************
IBaseControl * IBaseControl::CreateVScrollBarControl(const cString & strBackgroundImage,
													const cString & strDefaultThumbImage,
													const cString & strPressedThumbImage,
													const cString & strDefaultMinImage,
													const cString & strPressedMinImage,
													const cString & strDefaultMaxImage,
													const cString & strPressedMaxImage,
													const int iMinPos, const int iMaxPos)
{
	cScrollBarControl * pControl = cVScrollBar::Create();
	pControl->Init(strBackgroundImage, strDefaultThumbImage, strPressedThumbImage,
		strDefaultMinImage, strPressedMinImage, strDefaultMaxImage,
		strPressedMaxImage, iMinPos, iMaxPos);
	return pControl;

}