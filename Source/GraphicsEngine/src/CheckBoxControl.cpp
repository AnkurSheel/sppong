// ***************************************************************
//  CheckBoxControl   version:  1.0   Ankur Sheel  date: 2011/12/11
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "CheckBoxControl.h"

using namespace Graphics;

Graphics::cCheckBoxControl::cCheckBoxControl()
: m_pTickBox(NULL)
, m_pLabel(NULL)
, m_iLabelPosition(D3DXVECTOR3(0.f, 0.f, 0.f))
, m_pfnCallBack(NULL)
{

}
// ***************************************************************

Graphics::cCheckBoxControl::~cCheckBoxControl()
{
	Cleanup();
}		
// ***************************************************************

void Graphics::cCheckBoxControl::Init( const Base::cString & strCheckedImage, const Base::cString & strUnCheckedImage, const Base::cString & strCaption, const int iCheckBoxWidth, const int iCheckBoxHeight, const int iSpaceCaption, const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color )
{
	SAFE_DELETE(m_pTickBox);
	m_pTickBox = IBaseControl::CreateButtonControl(strUnCheckedImage, strCheckedImage);
	m_pTickBox ->SetSize(iCheckBoxWidth, iCheckBoxHeight);
	m_pTickBox ->SetPosition(D3DXVECTOR3(0.f, 0.f, 0.f));

	SAFE_DELETE(m_pLabel);
	m_pLabel = IBaseControl::CreateLabelControl(iHeight, iWidth, iWeight, bItalic, charset, strFaceName, dwFormat, color, strCaption);
	m_iLabelPosition = D3DXVECTOR3(iCheckBoxWidth + iSpaceCaption, 0.0f, 0.0f);
	m_pLabel->SetPosition(m_iLabelPosition);

	SetSize(m_pTickBox->GetWidth() + iSpaceCaption + m_pLabel->GetWidth(), max(m_pTickBox->GetHeight(), m_pLabel->GetHeight()));
}
// ***************************************************************

void Graphics::cCheckBoxControl::OnRender( const AppMsg & msg )
{

	D3DXVECTOR3 vControlAbsolutePosition;
	bool bIsPositionChanged;
	RenderPrivate(vControlAbsolutePosition, bIsPositionChanged);

	if (bIsPositionChanged)
	{
		m_pTickBox->SetPosition(vControlAbsolutePosition);
		m_pLabel->SetPosition(vControlAbsolutePosition + m_iLabelPosition);
	}
	m_pTickBox->OnRender(msg);
	m_pLabel->OnRender(msg);
}
// ***************************************************************

void Graphics::cCheckBoxControl::Cleanup()
{
	SAFE_DELETE(m_pTickBox);
	SAFE_DELETE(m_pLabel);
	UnregisterCallBack();
}
// ***************************************************************

bool Graphics::cCheckBoxControl::OnMouseDown( const int iButton, const int X, const int Y )
{
	if (m_bChecked)
	{
		m_pTickBox->OnMouseUp(iButton, X, Y);
		m_bChecked = false;
	}
	else
	{
		m_pTickBox->OnMouseDown(iButton, X, Y);
		m_bChecked = true;
	}
	if (m_pfnCallBack)
	{
		m_pfnCallBack();
	}
	return cBaseControl::OnMouseDown(iButton, X, Y);
}
// ***************************************************************

void Graphics::cCheckBoxControl::OnLostDevice()
{
	if (m_pTickBox)
	{
		m_pTickBox->OnLostDevice();
	}
	if (m_pLabel)
	{
		m_pLabel->OnLostDevice();
	}
	cBaseControl::OnLostDevice();
}
// ***************************************************************

HRESULT Graphics::cCheckBoxControl::OnResetDevice()
{
	if (m_pTickBox)
	{
		m_pTickBox->OnResetDevice();
	}
	if (m_pLabel)
	{
		m_pLabel->OnResetDevice();
	}
	return cBaseControl::OnResetDevice();
	
}
// ***************************************************************


void Graphics::cCheckBoxControl::RegisterCallBack(function <void ()> callback)
{
	m_pfnCallBack = callback;
}
// ***************************************************************

void Graphics::cCheckBoxControl::UnregisterCallBack()
{
	m_pfnCallBack = NULL;
}
// ***************************************************************

GRAPHIC_API  IBaseControl * Graphics::IBaseControl::CreateCheckBoxControl( const Base::cString & strCheckedImage, const Base::cString & strUncheckedImage, const Base::cString & strCaption, const int iCheckBoxWidth, const int iCheckBoxHeight, const int iSpaceCaption, const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color )
{
	cCheckBoxControl * pControl = DEBUG_NEW cCheckBoxControl();
	pControl->Init(strCheckedImage, strUncheckedImage, strCaption, iCheckBoxWidth, iCheckBoxHeight, iSpaceCaption, iHeight, iWidth, iWeight, bItalic, charset, strFaceName, dwFormat, color);
	return pControl;

}