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

// ***************************************************************
cCheckBoxControl::cCheckBoxControl()
: m_pTickBox(NULL)
, m_pLabel(NULL)
, m_iLabelPosition(D3DXVECTOR3(0.f, 0.f, 0.f))
, m_pfnCallBack(NULL)
{

}

// ***************************************************************
cCheckBoxControl::~cCheckBoxControl()
{
	Cleanup();
}		

// ***************************************************************
void cCheckBoxControl::Init( const Base::cString & strCheckedImage, 
							const Base::cString & strUnCheckedImage, 
							const Base::cString & strCaption, 
							const int iCheckBoxWidth, const int iCheckBoxHeight, 
							const int iSpaceCaption, const int iHeight, 
							const UINT iWidth, const UINT iWeight, 
							const BOOL bItalic, const BYTE charset, 
							const Base::cString & strFaceName, DWORD dwFormat, 
							const D3DXCOLOR & color )
{
	SAFE_DELETE(m_pTickBox);
	m_pTickBox = IBaseControl::CreateButtonControl(strUnCheckedImage, strCheckedImage);
	m_pTickBox ->VSetSize(iCheckBoxWidth, iCheckBoxHeight);
	m_pTickBox ->VSetPosition(D3DXVECTOR3(0.f, 0.f, 0.f));

	SAFE_DELETE(m_pLabel);
	m_pLabel = IBaseControl::CreateLabelControl(iHeight, iWidth, iWeight, bItalic, charset, strFaceName, dwFormat, color, strCaption);
	m_iLabelPosition = D3DXVECTOR3(iCheckBoxWidth + iSpaceCaption, 0.0f, 0.0f);
	m_pLabel->VSetPosition(m_iLabelPosition);

	VSetSize(m_pTickBox->VGetWidth() + iSpaceCaption + m_pLabel->VGetWidth(), max(m_pTickBox->VGetHeight(), m_pLabel->VGetHeight()));
}

// ***************************************************************
bool cCheckBoxControl::VOnLeftMouseButtonDown( const int X, const int Y )
{
	if (m_bChecked)
	{
		m_pTickBox->VOnLeftMouseButtonUp(X, Y);
		m_bChecked = false;
	}
	else
	{
		m_pTickBox->VOnLeftMouseButtonDown(X, Y);
		m_bChecked = true;
	}
	if (m_pfnCallBack)
	{
		m_pfnCallBack();
	}
	return cBaseControl::VOnLeftMouseButtonDown(X, Y);
}

// ***************************************************************
void cCheckBoxControl::VOnRender( const AppMsg & msg )
{
	D3DXVECTOR3 vControlAbsolutePosition;
	bool bIsPositionChanged;
	RenderPrivate(vControlAbsolutePosition, bIsPositionChanged);

	if (bIsPositionChanged)
	{
		m_pTickBox->VSetPosition(vControlAbsolutePosition);
		m_pLabel->VSetPosition(vControlAbsolutePosition + m_iLabelPosition);
	}
	m_pTickBox->VOnRender(msg);
	m_pLabel->VOnRender(msg);
}

// ***************************************************************
void cCheckBoxControl::VOnLostDevice()
{
	if (m_pTickBox)
	{
		m_pTickBox->VOnLostDevice();
	}
	if (m_pLabel)
	{
		m_pLabel->VOnLostDevice();
	}
	cBaseControl::VOnLostDevice();
}

// ***************************************************************
HRESULT cCheckBoxControl::VOnResetDevice()
{
	if (m_pTickBox)
	{
		m_pTickBox->VOnResetDevice();
	}
	if (m_pLabel)
	{
		m_pLabel->VOnResetDevice();
	}
	return cBaseControl::VOnResetDevice();
	
}

// ***************************************************************
void cCheckBoxControl::VRegisterCallBack(function <void ()> callback)
{
	m_pfnCallBack = callback;
}

// ***************************************************************
void cCheckBoxControl::VUnregisterCallBack()
{
	m_pfnCallBack = NULL;
}

// ***************************************************************
void cCheckBoxControl::Cleanup()
{
	SAFE_DELETE(m_pTickBox);
	SAFE_DELETE(m_pLabel);
	VUnregisterCallBack();
}

// ***************************************************************
GRAPHIC_API  IBaseControl * IBaseControl::CreateCheckBoxControl( const Base::cString & strCheckedImage, const Base::cString & strUncheckedImage, const Base::cString & strCaption, const int iCheckBoxWidth, const int iCheckBoxHeight, const int iSpaceCaption, const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName, DWORD dwFormat, const D3DXCOLOR & color )
{
	cCheckBoxControl * pControl = DEBUG_NEW cCheckBoxControl();
	pControl->Init(strCheckedImage, strUncheckedImage, strCaption, iCheckBoxWidth, iCheckBoxHeight, iSpaceCaption, iHeight, iWidth, iWeight, bItalic, charset, strFaceName, dwFormat, color);
	return pControl;

}
