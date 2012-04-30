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

// ***************************************************************
Graphics::cLabelControl::cLabelControl()
{
}

// ***************************************************************
Graphics::cLabelControl::~cLabelControl()
{
}

// ***************************************************************
void Graphics::cLabelControl::Init(const int iHeight, const UINT iWidth, const UINT iWeight, 
						 const BOOL bItalic, const BYTE charset, 
						 const cString & strFaceName, DWORD dwFormat, 
						 const D3DXCOLOR & color, const Base::cString & strCaption )
{
	m_pFont = IFont::CreateMyFont();
	if (m_pFont != NULL)
	{
		m_pFont->InitFont(IDXBase::GetInstance()->VGetDevice(), iHeight, iWidth, iWeight, bItalic, charset, strFaceName);
		m_pFont->SetFormat(dwFormat);
		m_pFont->SetTextColor(color);
		m_pFont->SetText(strCaption);
		m_pFont->CalculateAndSetRect();

		RECT rect = m_pFont->GetRect();
		m_fHeight = (float)(rect.bottom - rect.top);
		m_fWidth = (float)(rect.right - rect.left);

		Log_Write_L3(ILogger::LT_DEBUG, cString(100, "Label Height : %d, Label Width : %d", m_fHeight, m_fWidth));
	}
}

// ***************************************************************
void Graphics::cLabelControl::VOnRender( const AppMsg & msg )
{
	if (m_pFont)
	{
		m_pFont->OnRender(IDXBase::GetInstance()->VGetDevice());
	}
}

// ***************************************************************
void Graphics::cLabelControl::VOnLostDevice()
{
	cBaseControl::VOnLostDevice();
	
	if (m_pFont)
	{
		m_pFont->OnLostDevice();
	}
}

// ***************************************************************
HRESULT Graphics::cLabelControl::VOnResetDevice()
{
	cBaseControl::VOnResetDevice();
	if (m_pFont)
	{
		m_pFont->OnResetDevice();
	}
	return S_OK;
}

// ***************************************************************
void Graphics::cLabelControl::VSetAbsolutePosition()
{
	cBaseControl::VSetAbsolutePosition();
	UpdateRect();
}

// ***************************************************************
void Graphics::cLabelControl::VSetSize( const float fNewWidth, const float fNewHeight )
{
	cBaseControl::VSetSize(fNewWidth, fNewHeight);
	UpdateRect();	
}

// ***************************************************************
void Graphics::cLabelControl::UpdateRect()
{
	m_rectBoundary.left = (LONG)m_vControlAbsolutePosition.x;
	m_rectBoundary.top = (LONG)m_vControlAbsolutePosition.y;
	m_rectBoundary.right = m_rectBoundary.left + (LONG)m_fWidth;
	m_rectBoundary.bottom = m_rectBoundary.top + (LONG)m_fHeight;
	m_pFont->SetRect(m_rectBoundary);
}

// ***************************************************************
IBaseControl * IBaseControl::CreateLabelControl( const int iHeight, const UINT iWidth,
												const UINT iWeight, const BOOL bItalic,
												const BYTE charset, 
												const Base::cString & strFaceName, 
												DWORD dwFormat, const D3DXCOLOR & color, 
												const Base::cString & strCaption )
{
	cLabelControl * pControl = DEBUG_NEW cLabelControl();
	pControl->Init(iHeight, iWidth, iWeight, bItalic, charset, strFaceName, dwFormat, color, strCaption);
	return pControl;
}
