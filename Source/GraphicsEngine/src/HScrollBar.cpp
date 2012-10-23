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
#include "Logger.hxx"

using namespace Graphics;
using namespace Utilities;
using namespace Base;

// ***************************************************************
Graphics::cHScrollBar::cHScrollBar()
{

}

// ***************************************************************
Graphics::cHScrollBar::~cHScrollBar()
{

}

// ***************************************************************
cHScrollBar* Graphics::cHScrollBar::Create()
{
	return (DEBUG_NEW cHScrollBar());
}

// ***************************************************************
bool Graphics::cHScrollBar::VOnMouseMove( const int X, const int Y )
{
	if (m_bDragMode)
	{
 		int iThumbPos = m_iThumbPos;
		float fVal = m_pBtnDecrementArrow->VGetWidth() + X 
			- (m_vControlAbsolutePosition.m_dX + m_pBtnIncrementArrow->VGetWidth());

		if(fVal >= m_pBtnIncrementArrow->VGetWidth())
		{
			if(fVal < (VGetWidth() - m_pBtnDecrementArrow->VGetWidth()))
			{
				float fRange = (VGetWidth() - m_pBtnIncrementArrow->VGetWidth()) -
					m_pBtnDecrementArrow->VGetWidth();
				float fIncrement = fRange / m_iNoOfIncrements;
				for(int counter = m_iMinPos; counter < m_iNoOfIncrements; counter++)
				{
					float fItem = m_pBtnDecrementArrow->VGetWidth() + (fIncrement * counter);
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
void Graphics::cHScrollBar::VSetAbsolutePosition()
{
	cScrollBarControl::VSetAbsolutePosition();
	cVector2 pos = m_vControlAbsolutePosition;
	if (m_pBtnDecrementArrow)
	{
		pos.m_dX += m_iMinPos;
		m_pBtnDecrementArrow->VSetPosition(pos);
		if (m_pCanvasSprite)
		{
			pos.m_dX += m_pBtnDecrementArrow->VGetWidth();
			m_pCanvasSprite->VSetPosition(pos);
		}
	}
	if (m_pBtnIncrementArrow)
	{
		pos.m_dX = m_vControlAbsolutePosition.m_dX + VGetWidth()- m_pBtnIncrementArrow->VGetWidth();
		m_pBtnIncrementArrow->VSetPosition(pos);
	}	
	VSetThumbPosition(m_iThumbPos);
}

// ***************************************************************
void Graphics::cHScrollBar::VSetSize(const cVector2 & vSize)
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
	if(m_pCanvasSprite)
	{
		m_pCanvasSprite->VSetSize(cVector2(fBackGroundWidth, VGetHeight()));
	}

	if (m_pBtnThumb)
	{
		AutoSize();
	}
	VSetAbsolutePosition();
}


// ***************************************************************
void Graphics::cHScrollBar::VSetThumbPosition( const int iNewPosition )
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

	cVector2 pos = m_vControlAbsolutePosition;
	if (m_pBtnThumb)
	{
		pos.m_dX += m_pBtnDecrementArrow->VGetWidth() + (m_pBtnThumb->VGetWidth() * m_iThumbPos);
		m_pBtnThumb->VSetPosition(pos);
	}
}

// ***************************************************************
void Graphics::cHScrollBar::AutoSize()
{
	m_fRange = VGetWidth() - m_pBtnIncrementArrow->VGetWidth() - m_pBtnDecrementArrow->VGetWidth();
	float fNewWidth = m_fRange / m_iNoOfIncrements ;
	m_pBtnThumb->VSetSize(cVector2(fNewWidth, VGetHeight()));
}

// ***************************************************************
IBaseControl * IBaseControl::CreateHScrollBarControl(const stScrollBarControlDef & def)
{
	cScrollBarControl * pControl = cHScrollBar::Create();
	pControl->Init(def);
	return pControl;
}