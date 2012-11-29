// ***************************************************************
//  Score   version:  1.0   Ankur Sheel  date: 05/15/2008
//  -------------------------------------------------------------

//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "Score.h"
#include "FontManager.hxx"
#include "ControlStructures.h"
#include "BaseControl.hxx"

using namespace Graphics;
using namespace Base;

// ***************************************************************
// Constructor
// ***************************************************************
cScore::cScore()
: m_iValue(0)
{
}
// ***************************************************************

// ***************************************************************
// Destructor
// ***************************************************************
cScore::~cScore()
{
	Cleanup();
}
// ***************************************************************

// ***************************************************************
// Initializes the font
// ***************************************************************
void cScore::Init(const cVector2 & vInitialPos)
{
	stLabelControlDef def;
	def.pFont = IFontManager::GetInstance()->VGetFont("arial.fnt"); // forte
	def.textColor = cColor::TURQUOISE;
	def.strText = cString(20, "%02d", m_iValue);
	def.fTextHeight = 40;
	m_pLabel = shared_ptr<IBaseControl>(IBaseControl::CreateLabelControl(def));
	m_pLabel->VSetPosition(vInitialPos);
/*	if (vInitialPos.x > 0 )
	{
		m_pFont->SetFormat(DT_RIGHT | DT_TOP);
	}
	else
	{
		m_pFont->SetFormat(DT_LEFT | DT_TOP);
	}*/
}
// ***************************************************************

// ***************************************************************
// Deletes the resources
// *************************************************************** 	
void cScore::Cleanup()
{
}
// ***************************************************************

// ***************************************************************
// Increment the score
// *************************************************************** 	
void cScore::IncrementScore()
{
	m_iValue++;
	m_pLabel->VSetText(cString(20, "%02d", m_iValue));
}
// ***************************************************************

shared_ptr<IBaseControl> cScore::GetLabel()
{
	return m_pLabel;
}
// ***************************************************************