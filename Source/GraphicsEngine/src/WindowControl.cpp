// ***************************************************************
//  WindowControl   version:  1.0   Ankur Sheel  date: 2011/11/21
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "WindowControl.h"
#include "Sprite.hxx"
#include "DxBase.hxx"

using namespace Graphics;
using namespace Utilities;
using namespace Base;
using namespace std;

// ***************************************************************
cWindowControl::cWindowControl()
	: m_eWindowType(cWindowControlDef::WT_DESKTOP)
{
	
}

// ***************************************************************
cWindowControl::~cWindowControl()
{
}

// ***************************************************************
void cWindowControl::Initialize(const cWindowControlDef & def)
{
	m_bAllowMovingControls = def.bAllowMovingControls;
	m_eWindowType = def.wType;
	if(m_eWindowType != cWindowControlDef::WT_DESKTOP && !def.strBGImageFile.IsEmpty())
	{
		m_pBGSprite = ISprite::CreateSprite();
		m_pBGSprite->VInitialize(def.strBGImageFile);
	}
	cBaseControl::Initialize(def);
}

// ***************************************************************
bool cWindowControl::VOnLeftMouseButtonUp( const int X, const int Y )
{
	if (m_eWindowType != cWindowControlDef::WT_DESKTOP)
	{
		return	cBaseControl::VOnLeftMouseButtonUp(X, Y);
	}
	return false;
}

// ***************************************************************
bool cWindowControl::VOnLeftMouseButtonDown( const int X, const int Y )
{
	if (m_eWindowType != cWindowControlDef::WT_DESKTOP)
	{
		return cBaseControl::VOnLeftMouseButtonDown(X, Y);
	}
	return false;
}

// ***************************************************************
bool cWindowControl::VOnMouseMove( const int X, const int Y )
{
	if (m_eWindowType != cWindowControlDef::WT_DESKTOP)
	{
		return cBaseControl::VOnMouseMove(X, Y);
	}
	return false;
}

// ***************************************************************
void cWindowControl::VSetAbsolutePosition()
{
	cBaseControl::VSetAbsolutePosition();
	if (m_pBGSprite)
	{
		m_pBGSprite->VSetPosition(m_vControlAbsolutePosition);
	}
}

// ***************************************************************
IBaseControl * IBaseControl::CreateWindowControl(const cWindowControlDef & def)
{
	cWindowControl * pControl = DEBUG_NEW cWindowControl();
	pControl->Initialize(def);
	
	return pControl;
}
