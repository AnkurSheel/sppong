// ***************************************************************
//  LabelControl   version:  1.0   Ankur Sheel  date: 2011/11/22
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "LabelControl.h"
#include "Font.hxx"
#include "DxBase.hxx"

using namespace Base;
using namespace Utilities;
using namespace Graphics;

Graphics::cLabelControl::cLabelControl()
//: m_pFont(NULL)
{

}

// ***************************************************************

Graphics::cLabelControl::~cLabelControl()
{
	//SAFE_DELETE(m_pFont);
}
// ***************************************************************

void Graphics::cLabelControl::OnKeyDown( const AppMsg & msg )
{

}
// ***************************************************************

void Graphics::cLabelControl::OnKeyUp( const AppMsg & msg )
{

}
// ***************************************************************

void Graphics::cLabelControl::OnRender( const AppMsg & msg )
{
	if (m_pFont)
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
		}

		m_pFont->Render(IDXBase::GetInstance()->GetDevice());
	}
}
// ***************************************************************

void Graphics::cLabelControl::Init(const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color, const Base::cString & strCaption )
{
	m_pFont = IFont::CreateMyFont();
	if (m_pFont != NULL)
	{
		m_pFont->InitFont(IDXBase::GetInstance()->GetDevice(), iHeight, iWidth, iWeight, bItalic, charset, strFaceName);
		m_pFont->SetFormat(dwFormat);
		m_pFont->SetTextColor(color);
		m_pFont->SetText(strCaption);
		m_pFont->CalculateAndSetRect();

		RECT rect = m_pFont->GetRect();
		m_dwHeight = rect.bottom - rect.top;
		m_dwWidth = rect.right - rect.left;

		Log_Write_L3(ILogger::LT_DEBUG, cString(100, "Label Height : %d, Label Width : %d", m_dwHeight, m_dwWidth));
	}
}
// ***************************************************************

IBaseControl * Graphics::IBaseControl::CreateLabelControl( const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color, const Base::cString & strCaption )
{
	cLabelControl * pControl = DEBUG_NEW cLabelControl();
	pControl->Init(iHeight, iWidth, iWeight, bItalic, charset, strFaceName, dwFormat, color, strCaption);
	return pControl;
}
// ***************************************************************
