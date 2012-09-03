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

// ***************************************************************
Graphics::cTextBoxControl::cTextBoxControl()
: m_pCaretLine(NULL)
, m_bIsCaretVisible(false)
, m_iTextWidth(0)
, m_iCaretPos(0)
, m_bTextBoxFull(false)
{

}

// ***************************************************************
Graphics::cTextBoxControl::~cTextBoxControl()
{
	SAFE_RELEASE(m_pCaretLine);
}

// ***************************************************************
void Graphics::cTextBoxControl::Init( const Base::cString & strDefaultImage, const int iHeight, 
						   const UINT iWidth, const UINT iWeight, const BOOL bItalic, 
						   const BYTE charset, const Base::cString & strFaceName, 
						   DWORD dwFormat, const D3DXCOLOR & color )
{
	m_pFont = IFont::CreateMyFont();
	if (m_pFont != NULL)
	{
		m_pFont->InitFont(IDXBase::GetInstance()->VGetDevice(), iHeight, iWidth, iWeight, bItalic, charset, strFaceName);
		m_pFont->SetFormat(dwFormat);
		m_pFont->SetTextColor(color);
	}

	m_pCanvasSprite = ISprite::CreateSprite();
	m_pCanvasSprite->Init(strDefaultImage);

	m_avCaretVector[0] = D3DXVECTOR2(0.f, 0.f);
	m_avCaretVector[1] = D3DXVECTOR2(0.f, 0.f);
	D3DXCreateLine(IDXBase::GetInstance()->VGetDevice(), &m_pCaretLine);
}

// ***************************************************************
void Graphics::cTextBoxControl::VOnRender( const AppMsg & msg )
{
	cBaseControl::VOnRender(msg);
	if (m_pFont)
	{
		m_pFont->VOnRender(msg);
	}
	
	if(m_bFocus)
	{
		if (m_bIsCaretVisible)
		{
			if (m_pCaretLine)
			{
				m_pCaretLine->Draw(m_vAbsoluteCaratPosition, 2, D3DCOLOR_XRGB(255,255,255));
			}
			m_bIsCaretVisible = false;
		}
		else
		{
			m_bIsCaretVisible = true;
		}
	}
}

// ***************************************************************
void Graphics::cTextBoxControl::VOnLostDevice()
{
	if (m_pFont)
	{
		m_pFont->VOnLostDevice();
	}

	if (m_pCaretLine)
	{
		m_pCaretLine->OnLostDevice();
	}
	cBaseControl::VOnLostDevice();
}

// ***************************************************************
HRESULT Graphics::cTextBoxControl::VOnResetDevice()
{
	if (m_pFont)
	{
		m_pFont->VOnResetDevice();
	}

	if (m_pCaretLine)
	{
		m_pCaretLine->OnResetDevice();
	}

	return cBaseControl::VOnResetDevice();
}

// ***************************************************************
bool Graphics::cTextBoxControl::VOnKeyDown( const AppMsg & msg )
{
	cBaseControl::VOnKeyDown(msg);
	
	// some messages are handled by both keydown and char
	if (msg.m_uMsg == WM_CHAR)
	{
		switch (msg.m_wParam)
		{
		case VK_BACK:
			RemoveText(1);
			return true;

		case VK_ESCAPE:
			SetFocusControl(NULL);
			return true;

		default:
			InsertText((char *)&msg.m_wParam);
			return true;
		}
	}
	else if (msg.m_uMsg == WM_KEYDOWN)
	{
		switch (msg.m_wParam)
		{
		case VK_DELETE:
			//if (m_iCaretPos < m_strText.GetLength())
			{
				if(SetCaratPosition(m_iCaretPos + 1))
				{
					RemoveText(1);
				}
			}
			return true;

		case VK_LEFT:
			SetCaratPosition(m_iCaretPos - 1);
			return true;

		case VK_RIGHT:
			SetCaratPosition(m_iCaretPos + 1);
			return true;
		}
	}
	return false;
}

// ***************************************************************
void Graphics::cTextBoxControl::VSetAbsolutePosition()
{
	cBaseControl::VSetAbsolutePosition();
	
	m_rectBoundary.left = (LONG)m_vControlAbsolutePosition.x;
	m_rectBoundary.top = (LONG)m_vControlAbsolutePosition.y;
	m_rectBoundary.right = m_rectBoundary.left + m_fWidth;
	m_rectBoundary.bottom = m_rectBoundary.top + m_fHeight;
	if (m_pFont)
	{
		m_pFont->SetRect(m_rectBoundary);
	}
	SetCaratAbsolutePosition();
}

// ***************************************************************
bool Graphics::cTextBoxControl::InsertText( const Base::cString & strText )
{
	if(!m_bTextBoxFull 
		&& (m_iTextWidth + GetStringWidth(strText)) <= m_fWidth)
	{
		m_strText.Insert(m_iCaretPos, strText);
		m_iTextWidth = GetStringWidth();
		SetCaratPosition(m_iCaretPos + strText.GetLength());
		SetText(m_strText);
		return true;
	}
	m_bTextBoxFull = true;
	return false;
}

// ***************************************************************
long Graphics::cTextBoxControl::RemoveText( const long iQuantity )
{
	if(SetCaratPosition(m_iCaretPos - iQuantity))
	{
		m_strText.Remove(m_iCaretPos, iQuantity);
		SetText(m_strText);
		m_bTextBoxFull = false;
	}
	return m_iTextWidth;
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
	return 0;
}
// ***************************************************************

int Graphics::cTextBoxControl::GetStringHeight()
{
	if (m_pFont)
	{
		RECT rectStringInfo = m_pFont->GetRect();
		return rectStringInfo.bottom;
	}
	return 0;
}

// ***************************************************************
void Graphics::cTextBoxControl::SetText( const Base::cString & strText )
{
	int iWidth = GetStringWidth(strText);
	if(iWidth <= m_fWidth)
	{
		m_strText = strText;
		m_iTextWidth = iWidth;
		m_pFont->SetText(m_strText);
	}

}

// ***************************************************************
bool Graphics::cTextBoxControl::SetCaratPosition( const long iPos )
{
	if (iPos >= 0 && iPos <= m_strText.GetLength())
	{
		cString subStr = m_strText.GetSubString(0, iPos);
		m_avCaretVector[0].x = GetStringWidth(subStr);
		m_avCaretVector[1].x = m_avCaretVector[0].x ;
		m_iCaretPos = iPos;
		SetCaratAbsolutePosition();
		return true;
	}
	Log_Write_L2(ILogger::LT_ERROR, "Pos is < 0 or pos > strlen");
	return false;
}

// ***************************************************************
void Graphics::cTextBoxControl::SetCaratAbsolutePosition()
{
	if (m_pCaretLine)
	{
		m_vAbsoluteCaratPosition[0].x = m_vControlAbsolutePosition.x + m_avCaretVector[0].x;
		m_vAbsoluteCaratPosition[0].y = m_vControlAbsolutePosition.y + m_avCaretVector[0].y;
		m_vAbsoluteCaratPosition[1].x = m_vControlAbsolutePosition.x + m_avCaretVector[0].x;
		m_vAbsoluteCaratPosition[1].y = m_vControlAbsolutePosition.y + m_avCaretVector[0].y + VGetHeight();
	}
}
// ***************************************************************
IBaseControl * IBaseControl::CreateTextBoxControl(const Base::cString & strDefaultImage,  const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color )
{
	cTextBoxControl * pControl = DEBUG_NEW cTextBoxControl();
	pControl->Init(strDefaultImage, iHeight, iWidth, iWeight, bItalic, charset, strFaceName, dwFormat, color);
	return pControl;
}
