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
using namespace Utilities;
// ***************************************************************
// Constructor
// ***************************************************************
cMyFont::cMyFont()
: m_pFont(NULL)
, m_Color(BLACK)
, m_bVisible(true)
{
	m_boundingRect.top = 0;
	m_boundingRect.bottom = 0;
	m_boundingRect.left = 0;
	m_boundingRect.right = 0;
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

void cMyFont::Cleanup()
{
	SAFE_RELEASE(m_pFont);
}
// ***************************************************************

void Graphics::cMyFont::CalculateAndSetRect()
{
	if (m_strString.IsEmpty())
	{
		Log_Write_L2(ILogger::LT_ERROR, "m_strString is empty");
	}
	m_pFont->DrawText(NULL, m_strString.GetData(), -1, &m_boundingRect, DT_CALCRECT, m_Color);
}
// ***************************************************************

const RECT Graphics::cMyFont::GetRect( const Base::cString & strText ) const
{
	if (strText.IsEmpty())
	{
		Log_Write_L2(ILogger::LT_ERROR, "Calculating Boundary Rectangle for Empty String");
	}
	RECT boundingRect;
	boundingRect.top = 0;
	boundingRect.bottom = 0;
	boundingRect.left = 0;
	boundingRect.right = 0;
	m_pFont->DrawText(NULL, strText.GetData(), -1, &boundingRect, DT_CALCRECT, m_Color);
	return boundingRect;
}
// ***************************************************************
// Creates a font
// ***************************************************************
IFont * IFont::CreateMyFont()
{
	cMyFont * pFont = DEBUG_NEW cMyFont();
	return pFont;
}
// ***************************************************************
