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
		
		// get the position of the mouse in the scrollbar
		float fPosRelativeToScrollbar = m_pBtnDecrementArrow->VGetHeight() + Y 
			- (m_vControlAbsolutePosition.y + m_pBtnIncrementArrow->VGetHeight());

		//check if the mouse position is still within the scrollbar
		if(fPosRelativeToScrollbar >= m_pBtnIncrementArrow->VGetHeight() 
			&& fPosRelativeToScrollbar < (VGetHeight() - m_pBtnDecrementArrow->VGetHeight()))
		{
			// get the area in which the thumb can move
			float fThumbRange = (VGetHeight() - m_pBtnIncrementArrow->VGetHeight()) -
				m_pBtnDecrementArrow->VGetHeight();

			float fPixelsMovedPerIncrement = fThumbRange / m_iNoOfIncrements;
			
			// get the cuurent pos of the thum
			for(int counter = 0; counter < m_iNoOfIncrements; counter++)
			{
				// get the current pos for this counter
				float fPosForCounter = m_pBtnDecrementArrow->VGetHeight() + (fPixelsMovedPerIncrement * counter);

				if(((fPosRelativeToScrollbar >= fPosForCounter)) 
					&& (fPosRelativeToScrollbar < (fPosForCounter + fPixelsMovedPerIncrement)))
				{
					iThumbPos = counter;
					break;
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
		if (m_pBGSprite)
		{
			pos.y += m_pBtnDecrementArrow->VGetHeight();
			m_pBGSprite->VSetPosition(pos);
		}
	}
	if (m_pBtnIncrementArrow)
	{
		pos.y = m_vControlAbsolutePosition.y + VGetHeight()- m_pBtnIncrementArrow->VGetHeight();
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
	if(m_pBGSprite)
	{
		m_pBGSprite->VSetSize(cVector2(VGetWidth(), fBackGroundHeight));
	}
	if (m_pBtnThumb)
	{
		AutoSizeThumb();
	}
	VSetAbsolutePosition();
}

// ***************************************************************
void cVScrollBar::VSetThumbPosition( const int iNewPosition )
{
	cScrollBarControl::VSetThumbPosition(iNewPosition);
	
	if (m_pBtnThumb)
	{
		cVector2 pos = m_vControlAbsolutePosition;
		pos.y += m_pBtnDecrementArrow->VGetHeight() + (m_pBtnThumb->VGetHeight() * m_iThumbPos);
		m_pBtnThumb->VSetPosition(pos);
	}
	Log_Write_L3(ILogger::LT_DEBUG, cString(100, "ThumbPos % d" , (m_iThumbPos + m_iMinPos)));
}

// ***************************************************************
void cVScrollBar::AutoSizeThumb()
{
	float fThumbRange = VGetHeight() - m_pBtnIncrementArrow->VGetHeight() - m_pBtnDecrementArrow->VGetHeight();
	float fNewThumbHeight = fThumbRange / m_iNoOfIncrements ;
	m_pBtnThumb->VSetSize(cVector2(VGetWidth(), fNewThumbHeight));
}

// ***************************************************************
IBaseControl * IBaseControl::CreateVScrollBarControl(const cScrollBarControlDef & def)
{
	cScrollBarControl * pControl = cVScrollBar::Create();
	pControl->Initialize(def);
	return pControl;

}