// ***************************************************************
//  P1PaddleHandler   version:  1.0   Ankur Sheel  date: 2012/04/20
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "P1PaddleHandler.h"
#include "Structures.h"

using namespace Graphics;

// ***************************************************************
P1PaddleHandler::P1PaddleHandler()
: m_pfnCallBack(NULL)
{
	memset(m_bKey, 0, sizeof(m_bKey));
}

// ***************************************************************
P1PaddleHandler::~P1PaddleHandler()
{
	UnregisterCallBack();
}

// ***************************************************************
bool P1PaddleHandler::VOnKeyDown( const AppMsg & msg )
{
	BYTE c = static_cast<const BYTE>(msg.m_wParam);
	m_bKey[c] = true;
	return true;
}

// ***************************************************************
bool P1PaddleHandler::VOnKeyUp( const AppMsg & msg )
{
	BYTE c = static_cast<const BYTE>(msg.m_wParam);
	m_bKey[c] = false;
	return true;
}

// ***************************************************************
void P1PaddleHandler::OnUpdate()
{
	if (m_bKey['S'])
	{
		if (m_pfnCallBack)
		{
			m_pfnCallBack(true);
		}
	}

	if (m_bKey['W'])
	{
		if (m_pfnCallBack)
		{
			m_pfnCallBack(false);
		}
	}
}

// ***************************************************************
void P1PaddleHandler::RegisterCallBack( function <void (bool)> callback )
{
	m_pfnCallBack = callback;
}

// ***************************************************************
void P1PaddleHandler::UnregisterCallBack()
{
	m_pfnCallBack = NULL;
}

// ***************************************************************
void P1PaddleHandler::VLockKey( const BYTE c, const bool bLock )
{

}