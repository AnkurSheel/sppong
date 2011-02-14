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

using namespace Graphics;
// ***************************************************************
// Constructor
// ***************************************************************
cMyFont::cMyFont()
: m_pFont(NULL)
{
}
// ***************************************************************

// ***************************************************************
// Constructor
// ***************************************************************
cMyFont::~cMyFont()
{
	SAFE_RELEASE(m_pFont) ;
}
// ***************************************************************

// ***************************************************************
// Initializes the font
// ***************************************************************
void cMyFont::InitFont( IDirect3DDevice9 *pd3dDevice, const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const char * const szFaceName )
{
	D3DXFONT_DESC		fonttype ;

	ZeroMemory(&fonttype, sizeof(D3DXFONT_DESC)) ;
	fonttype.Height		= iHeight ;
	fonttype.Width		= iWidth ;
	fonttype.Weight		= iWeight ;
	fonttype.Italic		= bItalic ;
	fonttype.CharSet	= charset ;
	strcpy_s(fonttype.FaceName, LF_FACESIZE, szFaceName) ;

	D3DXCreateFontIndirect(pd3dDevice, &fonttype, &m_pFont) ;
}
// ***************************************************************

// ***************************************************************
// Displays the text
// ***************************************************************
void cMyFont::DisplayText( IDirect3DDevice9 *pd3dDevice, const char * const szString, const LPRECT pRect, DWORD *pformat, D3DCOLOR Col )
{	
	m_pFont->DrawText(NULL, szString, -1, pRect, *pformat, Col) ;
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
