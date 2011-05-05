// ***************************************************************
//  Font   version:  1.0   Ankur Sheel  date: 05/16/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "Font.h"
#include "DxBase.hxx"

using namespace Graphics;
using namespace Base;
// ***************************************************************
// Constructor
// ***************************************************************
cMyFont::cMyFont()
: m_pFont(NULL)
, m_Color(BLACK)
, m_bVisible(true)
{
}
// ***************************************************************

// ***************************************************************
// Constructor
// ***************************************************************
cMyFont::~cMyFont()
{
	Cleanup();
}
// ***************************************************************

// ***************************************************************
// Initializes the font
// ***************************************************************
void cMyFont::InitFont( IDirect3DDevice9 *pd3dDevice, const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const cString & strFaceName )
{
	ZeroMemory(&m_fonttype, sizeof(D3DXFONT_DESC)) ;
	m_fonttype.Height		= iHeight ;
	m_fonttype.Width		= iWidth ;
	m_fonttype.Weight		= iWeight ;
	m_fonttype.Italic		= bItalic ;
	m_fonttype.CharSet	= charset ;
	strcpy_s(m_fonttype.FaceName, LF_FACESIZE, strFaceName.GetData()) ;

	D3DXCreateFontIndirect(pd3dDevice, &m_fonttype, &m_pFont) ;
}
// ***************************************************************

// ***************************************************************
// Displays the text
// ***************************************************************
void cMyFont::Render(LPDIRECT3DDEVICE9 const pDevice)
{	
	m_pFont->DrawText(NULL, m_strString.GetData(), -1, &m_boundingRect, m_dwFormat, m_Color) ;
}
// ***************************************************************

void cMyFont::SetText(const cString & strString)
{
	m_strString = strString;
}
// ***************************************************************

void cMyFont::SetRect(const RECT & boundingRect)
{
	m_boundingRect = boundingRect;
}
// ***************************************************************

void cMyFont::SetFormat(const DWORD dwFormat)
{
	m_dwFormat = dwFormat;
}
// ***************************************************************

void cMyFont::SetTextColor(const D3DCOLOR & color)
{
	m_Color = color;
}
// ***************************************************************

void cMyFont::OnLostDevice()
{
	Cleanup();
}
// ***************************************************************

void cMyFont::OnResetDevice()
{
	D3DXCreateFontIndirect(IDXBase::GetInstance()->GetDevice(), &m_fonttype, &m_pFont);
}
// ***************************************************************

bool cMyFont::IsVisible()
{
	return m_bVisible;
}
// ***************************************************************

void cMyFont::Cleanup()
{
	SAFE_RELEASE(m_pFont);
}
// ***************************************************************

void cMyFont::SetVisible(const bool bVisible)
{
	m_bVisible = bVisible;
}
// ***************************************************************

// ***************************************************************
// Creates a font
// ***************************************************************
IFont * IFont::CreateMyFont()
{
	cMyFont * pFont = DEBUG_NEW cMyFont();
	return pFont;
}
// ***************************************************************
