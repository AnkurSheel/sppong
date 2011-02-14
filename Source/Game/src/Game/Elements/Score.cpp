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
#include "2D/font.hxx"
#include "Constants.h"

using namespace Graphics;

// ***************************************************************
// Constructor
// ***************************************************************
cScore::cScore()
: m_pFont(NULL)
, m_dwFormat(0)
, m_iValue(0)
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
// Renders the text
// ***************************************************************
void cScore::Render( LPDIRECT3DDEVICE9 const pDevice )
{
	m_pFont->DisplayText(pDevice, m_strValue, &m_BoundingRect, &m_dwFormat, TURQUOISE );
}

// ***************************************************************

// ***************************************************************
// Initializes the font
// ***************************************************************
void cScore::Init( const D3DXVECTOR3& vInitialPos )
{
	if (vInitialPos.x > 0 )
	{
		m_BoundingRect.left = (long)vInitialPos.x - 80;
		m_BoundingRect.right = (long)vInitialPos.x;
		m_dwFormat = DT_RIGHT | DT_TOP;
	}
	else
	{
		m_BoundingRect.left = (long)vInitialPos.x;
		m_BoundingRect.right = 90;
		m_dwFormat = DT_LEFT | DT_TOP;
	}
	m_BoundingRect.top  = (long)vInitialPos.y;
	m_BoundingRect.bottom = 50;
	

	//_stprintf_s(m_strValue, _countof(m_strValue) - 1, _T("%02d"), m_iValue) ;
	sprintf_s(m_strValue, "%02d", m_iValue) ;
	m_strValue[_countof(m_strValue) - 1] = TEXT('\0') ;

}
// ***************************************************************

// ***************************************************************
// called when the device is reset
// ***************************************************************
void cScore::OnResetDevice( LPDIRECT3DDEVICE9 const pDevice )
{
	m_pFont = IFont::CreateMyFont();
	m_pFont->InitFont(pDevice, 40, 30, 500, false, DEFAULT_CHARSET, "Forte");
}
// ***************************************************************

// ***************************************************************
// called when the device is lost
// *************************************************************** 
void cScore::OnLostDevice()
{
	SAFE_DELETE(m_pFont);
}
// ***************************************************************

// ***************************************************************
// Deletes the resources
// *************************************************************** 	
void cScore::Cleanup()
{
	SAFE_DELETE(m_pFont);
}
// ***************************************************************

// ***************************************************************
// Increment the score
// *************************************************************** 	
void cScore::IncrementScore()
{
	m_iValue++;

	//_stprintf_s(m_strValue, _countof(m_strValue) - 1, _T("%02d"), m_iValue) ;
	sprintf_s(m_strValue, _countof(m_strValue) - 1, "%02d", m_iValue) ;
	m_strValue[_countof(m_strValue) - 1] = TEXT('\0') ;
}
// ***************************************************************