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
#include "Sentence.hxx"

using namespace Base;
using namespace Utilities;
using namespace Graphics;

// ***************************************************************
cLabelControl::cLabelControl()
: m_pSentence(NULL)
{
}

// ***************************************************************
cLabelControl::~cLabelControl()
{
	VCleanup();
}

// ***************************************************************
void cLabelControl::Init(const shared_ptr<IMyFont> m_pFont, const cColor & textColor,
								   const cString & strText)
{
	m_pSentence = ISentence::CreateSentence();
	m_pSentence->VInitialize(m_pFont, strText, textColor);
}

// ***************************************************************
void cLabelControl::VRender(const ICamera * const pCamera)
{
	cBaseControl::VRender(pCamera);
	if (m_pSentence)
	{
		m_pSentence->VRender(pCamera);
	}
}

// *************************************************************************
void cLabelControl::VSetAbsolutePosition()
{
	cBaseControl::VSetAbsolutePosition();
	m_pSentence->VSetPosition(m_vControlAbsolutePosition);
}

// *************************************************************************
void cLabelControl::VCleanup()
{
	SAFE_DELETE(m_pSentence);
	cBaseControl::VCleanup();
}

// *************************************************************************
IBaseControl * IBaseControl::CreateLabelControl(const shared_ptr<IMyFont> m_pFont,
														  const cColor & textColor,
														  const cString & strText)
{
	cLabelControl * pControl = DEBUG_NEW cLabelControl();
	pControl->Init(m_pFont, textColor, strText);
	return pControl;
}