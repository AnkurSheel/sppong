// ***************************************************************
//  HScrollBar   version:  1.0   Ankur Sheel  date: 2012/04/29
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "HScrollBar.h"
#include "Sprite.hxx"

using namespace Graphics;
using namespace Utilities;
using namespace Base;

// ***************************************************************
cHScrollBar::cHScrollBar()
{

}

// ***************************************************************
cHScrollBar::~cHScrollBar()
{

}

// ***************************************************************
cHScrollBar* cHScrollBar::Create()
{
	return (DEBUG_NEW cHScrollBar());
}

// ***************************************************************
bool cHScrollBar::VOnMouseMove( const int X, const int Y )
{
	if (m_bDragMode)
	{
 		int iThumbPos = m_iThumbPos;
		// get the position of the mouse in the scrollbar
		float fPosRelativeToScrollbar = m_pBtnDecrementArrow->VGetWidth() + X 
			- (m_vControlAbsolutePosition.x + m_pBtnIncrementArrow->VGetWidth());

		//check if the mouse position is still within the scrollbar
		if(fPosRelativeToScrollbar >= m_pBtnIncrementArrow->VGetWidth() 
			&& fPosRelativeToScrollbar < (VGetWidth() - m_pBtnDecrementArrow->VGetWidth()))
		{
			// get the area in which the thumb can move
			float fThumbRange = (VGetWidth() - m_pBtnIncrementArrow->VGetWidth()) -
				m_pBtnDecrementArrow->VGetWidth();
			
			float fPixelsMovedPerIncrement = fThumbRange / m_iNoOfIncrements;
			
			// get the cuurent pos of the thum
			for(int counter = 0; counter < m_iNoOfIncrements; counter++)
			{
				// get the current pos for this counter
				float fPosForCounter = m_pBtnDecrementArrow->VGetWidth() + (fPixelsMovedPerIncrement * counter);
				if(((fPosRelativeToScrollbar >= fPosForCounter))
					&& (fPosRelativeToScrollbar<= (fPosForCounter + fPixelsMovedPerIncrement)))
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
void cHScrollBar::VSetAbsolutePosition()
{
	cScrollBarControl::VSetAbsolutePosition();
	cVector2 pos = m_vControlAbsolutePosition;
	if (m_pBtnDecrementArrow)
	{
		pos.x += m_iMinPos;
		m_pBtnDecrementArrow->VSetPosition(pos);
		if (m_pBGSprite)
		{
			pos.x += m_pBtnDecrementArrow->VGetWidth();
			m_pBGSprite->VSetPosition(pos);
		}
	}
	if (m_pBtnIncrementArrow)
	{
		pos.x = m_vControlAbsolutePosition.x + VGetWidth()- m_pBtnIncrementArrow->VGetWidth();
		m_pBtnIncrementArrow->VSetPosition(pos);
	}	
	VSetThumbPosition(m_iThumbPos);
}

// ***************************************************************
void cHScrollBar::VSetSize(const cVector2 & vSize)
{
	cBaseControl::VSetSize(vSize);
	float fBackGroundWidth = VGetWidth();
	float fHeight = VGetHeight();
	if (m_pBtnDecrementArrow)
	{
		m_pBtnDecrementArrow->VSetSize(cVector2(fHeight, fHeight));
		fBackGroundWidth -= fHeight;
	}
	if (m_pBtnIncrementArrow)
	{
		m_pBtnIncrementArrow->VSetSize(cVector2(fHeight, fHeight));
		fBackGroundWidth -= fHeight;
	}
	if(m_pBGSprite)
	{
		m_pBGSprite->VSetSize(cVector2(fBackGroundWidth, VGetHeight()));
	}

	if (m_pBtnThumb)
	{
		AutoSizeThumb();
	}
	VSetAbsolutePosition();
}


// ***************************************************************
void cHScrollBar::VSetThumbPosition( const int iNewPosition )
{
	cScrollBarControl::VSetThumbPosition(iNewPosition);
	
	if (m_pBtnThumb)
	{
		cVector2 pos = m_vControlAbsolutePosition;
		pos.x += m_pBtnDecrementArrow->VGetWidth() + (m_pBtnThumb->VGetWidth() * m_iThumbPos);
		m_pBtnThumb->VSetPosition(pos);
	}
	Log_Write_L1(ILogger::LT_DEBUG, cString(100, "ThumbPos % d" , (m_iThumbPos + m_iMinPos)));
}

// ***************************************************************
void cHScrollBar::AutoSizeThumb()
{
	float fThumbRange = VGetWidth() - m_pBtnIncrementArrow->VGetWidth() - m_pBtnDecrementArrow->VGetWidth();
	float fNewThumbWidth = fThumbRange / (m_iNoOfIncrements + 1) ;
	m_pBtnThumb->VSetSize(cVector2(fNewThumbWidth, VGetHeight()));
}

// ***************************************************************
IBaseControl * IBaseControl::CreateHScrollBarControl(const cScrollBarControlDef & def)
{
	cScrollBarControl * pControl = cHScrollBar::Create();
	pControl->Initialize(def);
	return pControl;
}