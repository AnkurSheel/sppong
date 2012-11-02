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
cVScrollBar::cVScrollBar()
{

}

// ***************************************************************
cVScrollBar::~cVScrollBar()
{

}

// ***************************************************************
cVScrollBar* cVScrollBar::Create()
{
	return (DEBUG_NEW cVScrollBar());
}

// ***************************************************************
bool cVScrollBar::VOnMouseMove( const int X, const int Y )
{
	if (m_bDragMode)
	{
		int iThumbPos = m_iThumbPos;
		float fVal = m_pBtnDecrementArrow->VGetHeight() + Y 
			- (m_vControlAbsolutePosition.m_dY + m_pBtnIncrementArrow->VGetHeight());

		if(fVal >= m_pBtnIncrementArrow->VGetHeight())
		{
			if(fVal < (VGetHeight() - m_pBtnDecrementArrow->VGetHeight()))
			{
				float fRange = (VGetHeight() - m_pBtnIncrementArrow->VGetHeight()) -
					m_pBtnDecrementArrow->VGetHeight();
				float fIncrement = fRange / m_iNoOfIncrements;
				for(int counter = 0; counter < m_iNoOfIncrements; counter++)
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
		return true;
	}
	return  cBaseControl::VOnMouseMove(X, Y);
}

// ***************************************************************
void cVScrollBar::VSetAbsolutePosition()
{
	cScrollBarControl::VSetAbsolutePosition();
	cVector2 pos = m_vControlAbsolutePosition;
	if (m_pBtnDecrementArrow)
	{
		m_pBtnDecrementArrow->VSetPosition(pos);
		if (m_pCanvasSprite)
		{
			pos.m_dY += m_pBtnDecrementArrow->VGetHeight();
			m_pCanvasSprite->VSetPosition(pos);
		}
	}
	if (m_pBtnIncrementArrow)
	{
		pos.m_dY = m_vControlAbsolutePosition.m_dY + VGetHeight()- m_pBtnIncrementArrow->VGetHeight();
		m_pBtnIncrementArrow->VSetPosition(pos);
	}	
	VSetThumbPosition(m_iThumbPos);
}

// ***************************************************************
void cVScrollBar::VSetSize(const cVector2 & vSize)
{
	cBaseControl::VSetSize(vSize);
	float fBackGroundHeight = VGetHeight();
	float fWidth = VGetWidth();
	if (m_pBtnDecrementArrow)
	{
		m_pBtnDecrementArrow->VSetSize(cVector2(fWidth, fWidth));
		fBackGroundHeight -=fWidth;
	}
	if (m_pBtnIncrementArrow)
	{
		m_pBtnIncrementArrow->VSetSize(cVector2(fWidth, fWidth));
		fBackGroundHeight -= fWidth;
	}
	if(m_pCanvasSprite)
	{
		m_pCanvasSprite->VSetSize(cVector2(VGetWidth(), fBackGroundHeight));
	}
	if (m_pBtnThumb)
	{
		AutoSize();
	}
	VSetAbsolutePosition();
}

// ***************************************************************
void cVScrollBar::VSetThumbPosition( const int iNewPosition )
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

	cVector2 pos = m_vControlAbsolutePosition;
	if (m_pBtnThumb)
	{
		pos.m_dY += m_pBtnDecrementArrow->VGetHeight() + (m_pBtnThumb->VGetHeight() * m_iThumbPos);
		m_pBtnThumb->VSetPosition(pos);
	}
	Log_Write_L1(ILogger::LT_DEBUG, cString(100, "ThumbPos % d" , (m_iThumbPos + m_iMinPos)));
}

// ***************************************************************
void cVScrollBar::AutoSize()
{
	m_fRange = VGetHeight() - m_pBtnIncrementArrow->VGetHeight() - m_pBtnDecrementArrow->VGetHeight();
	float fNewHeight = m_fRange / m_iNoOfIncrements ;
	m_pBtnThumb->VSetSize(cVector2(VGetWidth(), fNewHeight));
}

// ***************************************************************
IBaseControl * IBaseControl::CreateVScrollBarControl(const stScrollBarControlDef & def)
{
	cScrollBarControl * pControl = cVScrollBar::Create();
	pControl->Init(def);
	return pControl;

}