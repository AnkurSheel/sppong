// ***************************************************************
//  FPS   version:  1.0   Ankur Sheel  date: 05/23/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "FPS.h"
#include "2D/Font.hxx"
#include "Constants.h"

using namespace Graphics;
// ***************************************************************
// Constructor
// ***************************************************************
cFPS::cFPS()
: m_pFont(NULL)
, m_dwFormat(0)
, m_FontColor(BLACK)
{
}
// ***************************************************************

// ***************************************************************
// Destructor
// ***************************************************************
cFPS::~cFPS()
{
	Cleanup();
}
// ***************************************************************

// ***************************************************************
// Display the FPS
// ***************************************************************
void cFPS::Render( LPDIRECT3DDEVICE9 const pDevice, const float fFPSValue )
{
	//_stprintf_s(m_strValue, _countof(m_strValue) - 1, _T("%0.2f"), fFPSValue) ;
	sprintf_s(m_strValue, _countof(m_strValue) - 1, "%0.2f", fFPSValue) ;
	m_strValue[_countof(m_strValue) - 1] = TEXT('\0') ;

	m_pFont->DisplayText(pDevice, m_strValue, &m_BoundingRect, &m_dwFormat, m_FontColor);
}
// ***************************************************************

// ***************************************************************
// Initialize the FPS
// ***************************************************************
void cFPS::Init( LPDIRECT3DDEVICE9 const pDevice, 
				const D3DXVECTOR3& vInitialPos,
				const D3DXCOLOR& color /*= BLACK*/ )
{
	m_pFont = IFont::CreateMyFont();
	m_pFont->InitFont(pDevice, 14, 14, 20, false, DEFAULT_CHARSET, "Arial") ;

	m_BoundingRect.left = (long)vInitialPos.x- 75;
	m_BoundingRect.right = m_BoundingRect.left + 150;
	m_BoundingRect.top  = (long)vInitialPos.y;
	m_BoundingRect.bottom = m_BoundingRect.top + 30;
	m_dwFormat = DT_LEFT | DT_TOP;

	m_FontColor = color;
}
// ***************************************************************

// ***************************************************************
// function called when the device is reset
// ***************************************************************
void cFPS::OnResetDevice( LPDIRECT3DDEVICE9 const pDevice )
{
	m_pFont = IFont::CreateMyFont();
	m_pFont->InitFont(pDevice, 14, 14, 20, false, DEFAULT_CHARSET, "Arial") ;
}
// ***************************************************************

// ***************************************************************
// called when the device is lost
// ***************************************************************
void cFPS::OnLostDevice()
{
	SAFE_DELETE(m_pFont);
}
// ***************************************************************

// ***************************************************************
// Cleanup
// ***************************************************************
void cFPS::Cleanup()
{
	SAFE_DELETE(m_pFont);
}
// ***************************************************************

IFPS* IFPS::CreateFPS()
{
	cFPS * pFPS= DEBUG_NEW cFPS();
	return pFPS;

}