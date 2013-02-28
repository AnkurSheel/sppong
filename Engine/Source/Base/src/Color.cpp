// *****************************************************************************
//  Color   version:  1.0   Ankur Sheel  date: 2012/09/03
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "Color.h"

using namespace Base;

const cColor cColor::BLACK = cColor(0, 0, 0, 255);
const cColor cColor::WHITE = cColor(255, 255, 255, 255);
const cColor cColor::RED = cColor(255, 0, 0, 255);
const cColor cColor::BLUE = cColor(0, 0, 255, 255);
const cColor cColor::GREEN = cColor(0, 255, 0, 255);
const cColor cColor::GRAY = cColor(190, 190, 190, 255);
const cColor cColor::TURQUOISE = cColor(64, 224, 208, 255);
const cColor cColor::YELLOW = cColor(255, 255, 0, 255);
const cColor cColor::TAN = cColor(210, 180, 140, 255);
const cColor cColor::ORANGE = cColor(255, 165, 0, 255);
const cColor cColor::VIOLET = cColor(238, 130, 238, 255);

 // *****************************************************************************
cColor::cColor()
: m_iRed(0)
, m_iGreen(0)
, m_iBlue(0)
, m_iAlpha(0)
{
}

// *****************************************************************************
cColor::cColor(int iRed, int iGreen, int iBlue, int iAlpha)
: m_iRed(iRed)
, m_iGreen(iGreen)
, m_iBlue(iBlue)
, m_iAlpha(iAlpha)
{
	Clamp<int>(m_iRed, 0, 255);
	Clamp<int>(m_iBlue, 0, 255);
	Clamp<int>(m_iGreen, 0, 255);
	Clamp<int>(m_iAlpha, 0, 255);
}

// *****************************************************************************
cColor::cColor(float fRed, float fGreen, float fBlue, float fAlpha)
: m_iRed(static_cast<int>(fRed * 255))
, m_iGreen(static_cast<int>(fGreen * 255))
, m_iBlue(static_cast<int>(fBlue * 255))
, m_iAlpha(static_cast<int>(fAlpha * 255))
{
	Clamp<int>(m_iRed, 0, 255);
	Clamp<int>(m_iBlue, 0, 255);
	Clamp<int>(m_iGreen, 0, 255);
	Clamp<int>(m_iAlpha, 0, 255);
}

// *****************************************************************************
cColor::~cColor()
{
}

// *****************************************************************************
void cColor::GetColorComponentsInFloat(float & fRed, float & fBlue, 
									   float & fGreen, float & fAlpha) const
{
	fRed = static_cast<float>(m_iRed)/255.0f;
	fBlue = static_cast<float>(m_iGreen)/255.0f;;
	fGreen = static_cast<float>(m_iBlue)/255.0f;;
	fAlpha = static_cast<float>(m_iAlpha)/255.0f;;
}
