// ***************************************************************
//  TextBoxControl   version:  1.0   Ankur Sheel  date: 2011/12/01
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "TextBoxControl.h"
#include "Font.hxx"
#include "DxBase.hxx"
#include "Structures.h"
#include "Sprite.hxx"

using namespace Graphics;
using namespace Base;
using namespace Utilities;

Graphics::cTextBoxControl::cTextBoxControl()
: m_pFont(NULL)
, m_pCaretLine(NULL)
, m_bIsCaretVisible(false)
, m_iTextWidth(0)
, m_iCaretPos(0)
{

}
// ***************************************************************

Graphics::cTextBoxControl::~cTextBoxControl()
{
	SAFE_DELETE(m_pFont);
	SAFE_RELEASE(m_pCaretLine);
}
// ***************************************************************

void Graphics::cTextBoxControl::Init( const Base::cString & strDefaultImage, const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color )
{
	m_pFont = IFont::CreateMyFont();
	if (m_pFont != NULL)
	{
		m_pFont->InitFont(IDXBase::GetInstance()->GetDevice(), iHeight, iWidth, iWeight, bItalic, charset, strFaceName);
		m_pFont->SetFormat(dwFormat);
		m_pFont->SetTextColor(color);
	}

	m_pCanvasSprite = ISprite::CreateSprite();
	m_pCanvasSprite->Init(IDXBase::GetInstance()->GetDevice(), strDefaultImage);

}
// ***************************************************************

void Graphics::cTextBoxControl::OnRender( const AppMsg & msg )
{
	D3DXVECTOR3 vControlAbsolutePosition;
	bool bIsPositionChanged;
	RenderPrivate(vControlAbsolutePosition, bIsPositionChanged);

	if (bIsPositionChanged)
	{
		m_rectBoundary.left = (LONG)vControlAbsolutePosition.x;
		m_rectBoundary.top = (LONG)vControlAbsolutePosition.y;
		m_rectBoundary.right = m_rectBoundary.left + m_dwWidth;
		m_rectBoundary.bottom = m_rectBoundary.top + m_dwHeight;
		m_pFont->SetRect(m_rectBoundary);
		
		m_pCanvasSprite->SetPosition(vControlAbsolutePosition);
	}

	if(m_pCanvasSprite)
	{
		m_pCanvasSprite->Render(IDXBase::GetInstance()->GetDevice());
	}
	if (m_pFont)
	{
		m_pFont->Render(IDXBase::GetInstance()->GetDevice());
	}
}
// ***************************************************************

void Graphics::cTextBoxControl::OnKeyDown( const AppMsg & msg )
{
	switch (msg.m_wParam)
	{
	case VK_BACK:
	case VK_DELETE:
		RemoveText(1);
		break;

	case VK_LEFT:
		SetCaratPosition(m_iCaretPos - 1);
		break;

	case VK_RIGHT:
		SetCaratPosition(m_iCaretPos + 1);
		break;

	default:
		InsertText((char *)&msg.m_wParam);
	}
}
// ***************************************************************

void Graphics::cTextBoxControl::OnKeyUp( const AppMsg & msg )
{

}
// ***************************************************************

int Graphics::cTextBoxControl::GetStringWidth()
{
	return GetStringWidth(m_strText);
}
// ***************************************************************

int Graphics::cTextBoxControl::GetStringWidth( const Base::cString & strText )
{
	if (m_pFont)
	{
		RECT rectStringInfo = m_pFont->GetRect(strText);
		return rectStringInfo.right;
	}
}
// ***************************************************************

int Graphics::cTextBoxControl::GetStringHeight()
{
	if (m_pFont)
	{
		RECT rectStringInfo = m_pFont->GetRect();
		return rectStringInfo.bottom;
	}
}
// ***************************************************************

void Graphics::cTextBoxControl::SetText( const Base::cString & strText )
{
	int iWidth = GetStringWidth(strText);
	if(iWidth <= m_dwWidth)
	{
		m_strText = strText;
		m_iTextWidth = iWidth;
		m_pFont->SetText(m_strText);
	}

}
// ***************************************************************

void Graphics::cTextBoxControl::SetCaratPosition( const long iPos )
{
	if (iPos >= 0 && iPos <= m_strText.GetLength())
	{
		cString subStr = m_strText.GetSubString(0, iPos);
		m_avCaretVector[0].x = GetStringWidth(subStr);
		m_avCaretVector[1].x = m_avCaretVector[0].x ;
		m_iCaretPos = iPos;
	}
	else
	{
		Log_Write_L2(ILogger::LT_ERROR, "Pos is < 0 or pos > strlen");
	}
}
// ***************************************************************

bool Graphics::cTextBoxControl::InsertText( const Base::cString & strText )
{
	if((m_iTextWidth + GetStringWidth(strText)) <= m_dwWidth)
	{
		m_strText.Insert(m_iCaretPos, strText);
		m_iTextWidth = GetStringWidth();
		SetCaratPosition(m_iCaretPos + strText.GetLength());
		SetText(m_strText);
		return true;
	}
	return false;
}
// ***************************************************************

long Graphics::cTextBoxControl::RemoveText( const long iQuantity )
{
	SetCaratPosition(m_iCaretPos - iQuantity);
	m_strText.Remove(m_iCaretPos, iQuantity);
	SetText(m_strText);
	return m_iTextWidth;
}
// ***************************************************************

IBaseControl * Graphics::IBaseControl::CreateTextBoxControl(const Base::cString & strDefaultImage,  const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color )
{
	cTextBoxControl * pControl = DEBUG_NEW cTextBoxControl();
	pControl->Init(strDefaultImage, iHeight, iWidth, iWeight, bItalic, charset, strFaceName, dwFormat, color);
	return pControl;

}
// ***************************************************************