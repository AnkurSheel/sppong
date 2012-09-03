// ***************************************************************
//  P2PaddleHandler   version:  1.0   Ankur Sheel  date: 2012/04/21
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "P2PaddleHandler.h"
#include "Structures.h"

using namespace Graphics;

// ***************************************************************
P2PaddleHandler::P2PaddleHandler()
: m_pfnCallBack(NULL)
{
	memset(m_bKey, 0, sizeof(m_bKey));
}

// ***************************************************************
P2PaddleHandler::~P2PaddleHandler()
{
	UnregisterCallBack();
}

// ***************************************************************
bool P2PaddleHandler::VOnKeyDown( const AppMsg & msg )
{
	BYTE c = static_cast<const BYTE>(msg.m_wParam);
	m_bKey[c] = true;
	return true;
}

// ***************************************************************
bool P2PaddleHandler::VOnKeyUp( const AppMsg & msg )
{
	BYTE c = static_cast<const BYTE>(msg.m_wParam);
	m_bKey[c] = false;
	return true;
}

// ***************************************************************
void P2PaddleHandler::VLockKey( const BYTE c, const bool bLock )
{

}
// ***************************************************************
void P2PaddleHandler::OnUpdate()
{
	if (m_bKey[VK_UP])
	{
		if (m_pfnCallBack)
		{
			m_pfnCallBack(false);
		}
	}

	if (m_bKey[VK_DOWN])
	{
		if (m_pfnCallBack)
		{
			m_pfnCallBack(true);
		}
	}
}

// ***************************************************************
void P2PaddleHandler::RegisterCallBack( function <void (bool)> callback )
{
	m_pfnCallBack = callback;
}

// ***************************************************************
void P2PaddleHandler::UnregisterCallBack()
{
	m_pfnCallBack = NULL;
}
