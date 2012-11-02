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
#include "Structures.h"

using namespace Graphics;
using namespace Base;

// ***************************************************************
cCheckBoxControl::cCheckBoxControl()
: m_bChecked(false)
{

}

// ***************************************************************
cCheckBoxControl::~cCheckBoxControl()
{
	VCleanup();
}		

// ***************************************************************
void cCheckBoxControl::Initialize(const stCheckBoxControlDef & def)
{
	m_pTickBox = shared_ptr<IBaseControl>(IBaseControl::CreateButtonControl(def.buttonControlDef));
	
	IBaseControl * pLabel = IBaseControl::CreateLabelControl(def.labelControlDef);
	VAddChildControl(shared_ptr<IBaseControl>(pLabel));

	VSetSize(cVector2(m_pTickBox->VGetWidth() + def.iSpaceCaption + pLabel->VGetWidth(),
		max(m_pTickBox->VGetHeight(), pLabel->VGetHeight())));
	float fX = m_pTickBox->VGetWidth() + def.iSpaceCaption;
	float fY = VGetHeight()/2.0f - pLabel->VGetHeight()/2.0f;
	pLabel->VSetPosition(cVector2(fX, fY));
}

// *************************************************************************
void cCheckBoxControl::VRender(const ICamera * const pCamera)
{
	cBaseControl::VRender(pCamera);
	if (m_pTickBox)
	{
		m_pTickBox->VRender(pCamera);
	}
}

// ***************************************************************
bool cCheckBoxControl::VOnLeftMouseButtonDown( const int X, const int Y )
{
	AppMsg msg;
	msg.m_uMsg = WM_LBUTTONDOWN;
	msg.m_lParam = MAKELONG(X, Y);

	if(m_pTickBox && m_pTickBox->VPostMsg(msg))
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
			m_pfnCallBack(m_bChecked);
		}
	}
	return cBaseControl::VOnLeftMouseButtonDown(X, Y);
}

// ***************************************************************
void cCheckBoxControl::VSetAbsolutePosition()
{
	cBaseControl::VSetAbsolutePosition();
	if (m_pTickBox)
	{
		m_pTickBox->VSetPosition(m_vControlAbsolutePosition);
	}
}

// ***************************************************************
GRAPHIC_API  IBaseControl * IBaseControl::CreateCheckBoxControl(const stCheckBoxControlDef & def)
{
	cCheckBoxControl * pControl = DEBUG_NEW cCheckBoxControl();
	pControl->Initialize(def);
	return pControl;
}