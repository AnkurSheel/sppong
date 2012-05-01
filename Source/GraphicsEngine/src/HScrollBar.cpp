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
			- (m_vControlAbsolutePosition.x + m_pBtnIncrementArrow->VGetWidth());

		if(fVal >= m_pBtnIncrementArrow->VGetWidth())
		{
			if(fVal < (m_fWidth - m_pBtnDecrementArrow->VGetWidth()))
			{
				float fRange = (m_fWidth - m_pBtnIncrementArrow->VGetWidth()) -
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
	cBaseControl::VSetAbsolutePosition();
	D3DXVECTOR3 pos = m_vControlAbsolutePosition;
	if (m_pBtnDecrementArrow)
	{
		pos.x = m_vControlAbsolutePosition.x + m_iMinPos;
		m_pBtnDecrementArrow->VSetPosition(pos);
	}
	if (m_pBtnIncrementArrow)
	{
		pos.x = m_vControlAbsolutePosition.x + m_fWidth - m_pBtnIncrementArrow->VGetWidth();
		m_pBtnIncrementArrow->VSetPosition(pos);
	}	
	VSetThumbPosition(m_iThumbPos);
}

// ***************************************************************
void Graphics::cHScrollBar::VSetSize( const float fNewWidth, const float fNewHeight )
{
	cBaseControl::VSetSize(fNewWidth, fNewHeight);
	if (m_pBtnDecrementArrow)
	{
		m_pBtnDecrementArrow->VSetSize(fNewHeight, fNewHeight);
	}
	if (m_pBtnIncrementArrow)
	{
		m_pBtnIncrementArrow->VSetSize(fNewHeight, fNewHeight);
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

	D3DXVECTOR3 pos = m_vControlAbsolutePosition;
	if (m_pBtnThumb)
	{
		pos.x = m_vControlAbsolutePosition.x + m_pBtnDecrementArrow->VGetWidth() + (m_pBtnThumb->VGetWidth() * m_iThumbPos);
		m_pBtnThumb->VSetPosition(pos);
	}
}

// ***************************************************************
void Graphics::cHScrollBar::AutoSize()
{
	m_fRange = m_fWidth - m_pBtnIncrementArrow->VGetWidth() - m_pBtnDecrementArrow->VGetWidth();
	float fNewWidth = m_fRange / m_iNoOfIncrements ;
	m_pBtnThumb->VSetSize(fNewWidth, m_fHeight);
}

// ***************************************************************
IBaseControl * IBaseControl::CreateHScrollBarControl(const cString & strBackgroundImage,
													 const cString & strDefaultThumbImage,
													 const cString & strPressedThumbImage,
													 const cString & strDefaultMinImage,
													 const cString & strPressedMinImage,
													 const cString & strDefaultMaxImage,
													 const cString & strPressedMaxImage,
													 const int iMinPos, const int iMaxPos)
{
	cScrollBarControl * pControl = cHScrollBar::Create();
	pControl->Init(strBackgroundImage, strDefaultThumbImage, strPressedThumbImage,
		strDefaultMinImage, strPressedMinImage, strDefaultMaxImage,
		strPressedMaxImage, iMinPos, iMaxPos);
	return pControl;
}