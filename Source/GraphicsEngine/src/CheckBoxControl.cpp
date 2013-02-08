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
void cCheckBoxControl::Initialize(const cCheckBoxControlDef & def)
{
	m_pTickBox = shared_ptr<IBaseControl>(IBaseControl::CreateButtonControl(def.buttonControlDef));
	cBaseControl::Initialize(def);
	
	IBaseControl * pLabel = IBaseControl::CreateLabelControl(def.labelControlDef);
	VAddChildControl(shared_ptr<IBaseControl>(pLabel));
	VSetSize(cVector2(m_pTickBox->VGetWidth() + def.iSpaceCaption + pLabel->VGetWidth(),
		max(m_pTickBox->VGetHeight(), pLabel->VGetHeight())));
	float fX = m_pTickBox->VGetWidth() + def.iSpaceCaption;
	float fY = VGetHeight()/2.0f - pLabel->VGetHeight()/2.0f;
	pLabel->VSetPosition(cVector2(fX, fY));

	m_bChecked = def.bChecked;
	if (m_bChecked)
	{
		m_pTickBox->VOnLeftMouseButtonDown(0, 0);
	}
	else
	{
		m_pTickBox->VOnLeftMouseButtonUp(0, 0);
	}
}

// *************************************************************************
void cCheckBoxControl::VRender(const ICamera * const pCamera)
{
	if(m_bVisible)
	{
		cBaseControl::VRender(pCamera);
		if (m_pTickBox)
		{
			m_pTickBox->VRender(pCamera);
		}
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
		if (UIEventCallBackFn * pFn = GetCallbackFromMap(UIET_BTNPRESSED))
		{
			stUIEventCallbackParam param;
			param.bChecked = m_bChecked;
			(*pFn)(param);
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
GRAPHIC_API  IBaseControl * IBaseControl::CreateCheckBoxControl(const cCheckBoxControlDef & def)
{
	cCheckBoxControl * pControl = DEBUG_NEW cCheckBoxControl();
	pControl->Initialize(def);
	return pControl;
}