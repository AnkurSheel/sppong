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
#include "Font.hxx"
#include "Constants.h"
#include "DxBase.hxx"

using namespace Graphics;
using namespace Base;
// ***************************************************************
// Constructor
// ***************************************************************
cFPS::cFPS()
: m_pFont(NULL)
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
void cFPS::Render(const float fFPSValue)
{
	m_pFont->SetText(cString(20, "%0.2f", fFPSValue));
	m_pFont->Render(IDXBase::GetInstance()->GetDevice());
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

	RECT boundingRect;
	boundingRect.left = (long)vInitialPos.x- 75;
	boundingRect.right = boundingRect.left + 150;
	boundingRect.top  = (long)vInitialPos.y;
	boundingRect.bottom = boundingRect.top + 30;
	m_pFont->SetRect(boundingRect);

	m_pFont->SetFormat(DT_LEFT | DT_TOP);
	m_pFont->SetTextColor(color);
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

IFont * cFPS::GetFont()
{
	return m_pFont;
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