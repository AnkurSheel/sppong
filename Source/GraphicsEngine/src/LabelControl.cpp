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
#include "Sprite.hxx"

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
void cLabelControl::Initialize(const stLabelControlDef & def)
{
	if(def.pFont)
	{
		m_pSentence = ISentence::CreateSentence();
		m_pSentence->VInitialize(def.pFont, def.strText, def.textColor);
		m_pSentence->VSetHeight(def.fTextHeight);
		VSetSize(cVector2(m_pSentence->VGetWidth(), m_pSentence->VGetHeight()));
	}
	if(!def.strBGImageFile.IsEmpty())
	{
		m_pBGSprite = ISprite::CreateSprite();
		m_pBGSprite->VInitialize(def.strBGImageFile);
		m_pBGSprite->VSetSize(m_vSize);
	}
}

// ***************************************************************
void cLabelControl::VRender(const ICamera * const pCamera)
{
	if(m_bVisible)
	{
		cBaseControl::VRender(pCamera);
		if (m_pSentence)
		{
			m_pSentence->VRender(pCamera);
		}
	}
}

// *************************************************************************
void cLabelControl::VSetAbsolutePosition()
{
	cBaseControl::VSetAbsolutePosition();
	if(m_pSentence)
	{
		m_pSentence->VSetPosition(m_vControlAbsolutePosition);	
	}
}

// *************************************************************************
void cLabelControl::VSetText(const Base::cString & strText)
{
	if(m_pSentence != NULL)
	{
		m_pSentence->VSetText(strText);
	}
}

// *************************************************************************
void cLabelControl::VCleanup()
{
	SAFE_DELETE(m_pSentence);
	cBaseControl::VCleanup();
}

// *************************************************************************
IBaseControl * IBaseControl::CreateLabelControl(const stLabelControlDef & def)
{
	cLabelControl * pControl = DEBUG_NEW cLabelControl();
	pControl->Initialize(def);
	return pControl;
}