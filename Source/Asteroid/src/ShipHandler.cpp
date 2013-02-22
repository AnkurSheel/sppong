// *****************************************************************************
//  ShipHandler   version:  1.0   Ankur Sheel  date: 2013/02/21
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "ShipHandler.h"
#include "Structures.h"

using namespace Graphics;

// ***************************************************************
ShipPaddleHandler::ShipPaddleHandler()
: m_pfnCallBack(NULL)
{
	memset(m_bKey, 0, sizeof(m_bKey));
}

// ***************************************************************
ShipPaddleHandler::~ShipPaddleHandler()
{
	UnregisterCallBack();
}

// ***************************************************************
bool ShipPaddleHandler::VOnKeyDown(const unsigned int iCharID)
{
	BYTE c = static_cast<const BYTE>(iCharID);
	m_bKey[c] = true;
	return true;
}

// ***************************************************************
bool ShipPaddleHandler::VOnKeyUp(const unsigned int iCharID)
{
	BYTE c = static_cast<const BYTE>(iCharID);
	m_bKey[c] = false;
	return true;
}

// ***************************************************************
bool ShipPaddleHandler::VOnCharPress(const unsigned int iCharID)
{
	return false;
}

// ***************************************************************
void ShipPaddleHandler::OnUpdate()
{
	if (m_bKey['S'])
	{
		if (m_pfnCallBack)
		{
			m_pfnCallBack(SM_MOVE_BK);
		}
	}

	if (m_bKey['W'])
	{
		if (m_pfnCallBack)
		{
			m_pfnCallBack(SM_MOVE_FWD);
		}
	}

	if (m_bKey['A'])
	{
		if (m_pfnCallBack)
		{
			m_pfnCallBack(SM_ROTATE_LEFT);
		}
	}

	if (m_bKey['D'])
	{
		if (m_pfnCallBack)
		{
			m_pfnCallBack(SM_ROTATE_RIGHT);
		}
	}
}

// ***************************************************************
void ShipPaddleHandler::RegisterCallBack(ShipInputCallBackFn callback )
{
	m_pfnCallBack = callback;
}

// ***************************************************************
void ShipPaddleHandler::UnregisterCallBack()
{
	m_pfnCallBack = NULL;
}

// ***************************************************************
void ShipPaddleHandler::VLockKey( const BYTE c, const bool bLock )
{

}