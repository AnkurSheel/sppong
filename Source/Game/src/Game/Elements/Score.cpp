// *****************************************************************************
//  Score   version:  1.0   Ankur Sheel  date: 05/15/2008
//  ----------------------------------------------------------------------------

//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "Score.h"
#include "FontManager.hxx"
#include "ControlStructures.h"
#include "BaseControl.hxx"
#include "GameDirectories.h"

using namespace Graphics;
using namespace Base;
using namespace Utilities;

// *****************************************************************************
cScore::cScore()
: m_iValue(0)
{
}

// *****************************************************************************
cScore::~cScore()
{
	Cleanup();
}

// *****************************************************************************
void cScore::Init(const cVector2 & vInitialPos)
{
	cLabelControlDef def;
	def.pFont = IFontManager::GetInstance()->VGetFont("arial.fnt"); // forte
	def.textColor = cColor::TURQUOISE;
	def.strText = cString(20, "%02d", m_iValue);
	def.fTextHeight = 40;
	def.vPosition = vInitialPos;
	m_pLabel = shared_ptr<IBaseControl>(IBaseControl::CreateLabelControl(def));
}

// ***************************************************************************** 	
void cScore::Cleanup()
{
}

// ***************************************************************************** 	
void cScore::IncrementScore()
{
	m_iValue++;
	m_pLabel->VSetText(cString(20, "%02d", m_iValue));
}

// *****************************************************************************
shared_ptr<IBaseControl> cScore::GetLabel()
{
	return m_pLabel;
}