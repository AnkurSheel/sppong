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
#include "Sentence.hxx"
#include "DxBase.hxx"
#include "Structures.h"
#include "Sprite.hxx"
#include "Timer.hxx"

using namespace Graphics;
using namespace Base;
using namespace Utilities;

// ***************************************************************
cTextBoxControl::cTextBoxControl()
: m_fCaretPosInTextBox(0.0f)
, m_fLastCaretUpdateTime(0.0f)
, m_fCaretUpdateTime(0.0f)
, m_iCaretPosInText(0)
, m_bTextBoxFull(false)
, m_bIsCaretVisible(false)
{

}

// ***************************************************************
cTextBoxControl::~cTextBoxControl()
{
	VCleanup();
}

// ***************************************************************
void cTextBoxControl::Initialize(const stTextBoxControlDef & def)
{
	m_pSentence = ISentence::CreateSentence();
	m_pSentence->VInitialize(def.pFont, "", def.textColor);
	m_pSentence->VSetHeight(def.fTextHeight);
	if (!def.strBGImage.IsEmpty())
	{
		m_pBGSprite = ISprite::CreateSprite();
		m_pBGSprite->VInitialize(def.strBGImage);
	}

	if (!def.strCaretImage.IsEmpty())
	{
		m_pCaretSprite = ISprite::CreateSprite();
		m_pCaretSprite->VInitialize(def.strCaretImage);
		m_pCaretSprite->VSetSize(cVector2(def.iCaretWidth, def.fTextHeight));
	}
	m_fCaretUpdateTime = def.fCaretUpdateTime;

	m_pTimer = ITimer::CreateTimer();
}

// ***************************************************************
void cTextBoxControl::VRender(const ICamera * const pCamera )
{
	cBaseControl::VRender(pCamera);
	if (m_pSentence)
	{
		m_pSentence->VRender(pCamera);
	}
	m_pTimer->VOnUpdate();	
	m_fLastCaretUpdateTime += m_pTimer->VGetDeltaTime();
	
	if (m_fLastCaretUpdateTime >= m_fCaretUpdateTime)
	{
		m_fLastCaretUpdateTime = 0.0f;
		m_bIsCaretVisible = !m_bIsCaretVisible;
	}

	if(m_bFocus)
	{
		if(m_bIsCaretVisible)
		{
			if (m_pCaretSprite)
			{
				m_pCaretSprite->VRender(pCamera);
			}
		}
	}
}

// ***************************************************************
bool cTextBoxControl::VOnCharPress(const unsigned int iCharID)
{
	cBaseControl::VOnCharPress(iCharID);

	switch (iCharID)
	{
	case VK_BACK:
		RemoveText(1);
		return true;

	case VK_ESCAPE:
		SetFocusControl(NULL);
		return true;

	default:
		InsertText((char *)&iCharID);
		return true;
	}
	return false;
}


// ***************************************************************
bool cTextBoxControl::VOnKeyDown(const unsigned int iCharID)
{
	cBaseControl::VOnKeyDown(iCharID);
	
	switch (iCharID)
	{
	case VK_DELETE:
		if(SetCaratPosition(m_iCaretPosInText + 1))
		{
			RemoveText(1);
		}
		return true;

	case VK_LEFT:
		SetCaratPosition(m_iCaretPosInText - 1);
		return true;

	case VK_RIGHT:
		SetCaratPosition(m_iCaretPosInText + 1);
		return true;
	}
	return false;
}

// ***************************************************************
void cTextBoxControl::VSetAbsolutePosition()
{
	cBaseControl::VSetAbsolutePosition();
	if(m_pSentence)
	{
		m_pSentence->VSetPosition(m_vControlAbsolutePosition);	
	}
	SetCaratAbsolutePosition();
}

// *************************************************************************
void cTextBoxControl::VOnFocusChanged()
{
	if (m_bFocus)
	{
		m_pTimer->VStartTimer();
		m_bIsCaretVisible = true;
		m_fLastCaretUpdateTime = 0.0f;
	}
	else
	{
		m_pTimer->VStopTimer();	
		m_bIsCaretVisible = false;
	}
}

// *************************************************************************
void cTextBoxControl::VCleanup()
{
	cBaseControl::VCleanup();
	SAFE_DELETE(m_pSentence);
	SAFE_DELETE(m_pTimer);
}

// ***************************************************************
bool cTextBoxControl::InsertText( const Base::cString & strText )
{
	if(!m_bTextBoxFull 
		&& (GetStringWidth() + GetStringWidth(strText)) <= m_vSize.m_dX)
	{
		cString strExistingText;
		m_pSentence->VGetText(strExistingText);
		strExistingText.Insert(m_iCaretPosInText, strText);
		SetText(strExistingText);
		SetCaratPosition(m_iCaretPosInText + strText.GetLength());
		return true;
	}
	m_bTextBoxFull = true;
	return false;
}

// ***************************************************************
void cTextBoxControl::RemoveText(const unsigned int uiQuantity)
{
	if(SetCaratPosition(m_iCaretPosInText - uiQuantity))
	{
		cString strText;
		m_pSentence->VGetText(strText);
		strText.Remove(m_iCaretPosInText, uiQuantity);
		SetText(strText);
		m_bTextBoxFull = false;
	}
}

// ***************************************************************
int cTextBoxControl::GetStringWidth()
{
	if (m_pSentence)
	{
		return m_pSentence->VGetWidth();
	}
	return 0;
}

// ***************************************************************
int cTextBoxControl::GetStringWidth( const Base::cString & strText )
{
	if (m_pSentence)
	{
		return m_pSentence->VGetWidth(strText);
	}
	return 0;
}

// ***************************************************************
void cTextBoxControl::SetText( const Base::cString & strText )
{
	if (m_pSentence)
	{
		m_pSentence->VSetText(strText);
	}
}

// ***************************************************************
bool cTextBoxControl::SetCaratPosition(const unsigned int iPos )
{
	cString strText;
	m_pSentence->VGetText(strText);
	if (iPos >= 0 && iPos <= strText.GetLength())
	{
		cString subStr = strText.GetSubString(0, iPos);
		m_fCaretPosInTextBox = GetStringWidth(subStr);
		m_iCaretPosInText = iPos;
		SetCaratAbsolutePosition();
		return true;
	}
	Log_Write_L2(ILogger::LT_ERROR, "Pos is < 0 or pos > strlen");
	return false;
}

// ***************************************************************
void cTextBoxControl::SetCaratAbsolutePosition()
{
	if (m_pCaretSprite)
	{
		cVector2 vec = m_vControlAbsolutePosition;
		vec.m_dX += m_fCaretPosInTextBox;
		m_pCaretSprite->VSetPosition(vec);
	}
}

// ***************************************************************
IBaseControl * IBaseControl::CreateTextBoxControl(const stTextBoxControlDef & def)
{
	cTextBoxControl * pControl = DEBUG_NEW cTextBoxControl();
	pControl->Initialize(def);
	return pControl;
}