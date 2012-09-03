// ***************************************************************
//  Score   version:  1.0   Ankur Sheel  date: 05/15/2008
//  -------------------------------------------------------------

//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "Score.h"
#include "font.hxx"
#include "DxBase.hxx"
#include "Color.h"

using namespace Graphics;
using namespace Base;

// ***************************************************************
// Constructor
// ***************************************************************
cScore::cScore()
//: m_pFont(NULL)
: m_iValue(0)
{
}
// ***************************************************************

// ***************************************************************
// Destructor
// ***************************************************************
cScore::~cScore()
{
	Cleanup();
}
// ***************************************************************

// ***************************************************************
// Initializes the font
// ***************************************************************
void cScore::Init( const D3DXVECTOR3& vInitialPos )
{
	m_pFont = IFont::CreateMyFont();
	m_pFont->InitFont(40, 30, 500, false, DEFAULT_CHARSET, "Forte");

	RECT boundingRect;
	if (vInitialPos.x > 0 )
	{
		boundingRect.left = (long)vInitialPos.x - 80;
		boundingRect.right = (long)vInitialPos.x;
		m_pFont->SetFormat(DT_RIGHT | DT_TOP);
	}
	else
	{
		boundingRect.left = (long)vInitialPos.x;
		boundingRect.right = 90;
		m_pFont->SetFormat(DT_LEFT | DT_TOP);
	}
	boundingRect.top  = (long)vInitialPos.y;
	boundingRect.bottom = 50;

	m_pFont->SetRect(boundingRect);
	m_pFont->SetText(cString(20, "%02d", m_iValue));
	m_pFont->SetTextColor(cColor::TURQUOISE.GetColor());

}
// ***************************************************************

// ***************************************************************
// Deletes the resources
// *************************************************************** 	
void cScore::Cleanup()
{
}
// ***************************************************************

// ***************************************************************
// Increment the score
// *************************************************************** 	
void cScore::IncrementScore()
{
	m_iValue++;
	m_pFont->SetText(cString(20, "%02d", m_iValue));
}
// ***************************************************************

shared_ptr<IFont> cScore::GetFont()
{
	return m_pFont;
}
// ***************************************************************