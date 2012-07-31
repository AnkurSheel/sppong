// ***************************************************************
//  Entity2State   version:  1.0   Ankur Sheel  date: 2012/07/26
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "Entity2States.h"
#include "MessageDispatchManager.hxx"
#include "Entity2.h"
#include "FSM/StateMachine.h"

using namespace Utilities;
using namespace Base;
using namespace AI;
using namespace GameBase;

// ***************************************************************
cEntity2State1::cEntity2State1()
{

}

// ***************************************************************
cEntity2State1::~cEntity2State1()
{

}

// ***************************************************************
void cEntity2State1::VOnEnter( cEntity2 * pEntity )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Entity2 State1 Enter"));
}

// ***************************************************************
void cEntity2State1::VOnUpdate( cEntity2 * pEntity )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Entity2 State1 VOnUpdate"));
	IMessageDispatchManager::GetInstance()->VDispatchMessage(0.0f, 1, 0, 0, NULL);
}

// ***************************************************************
void cEntity2State1::VOnExit( cEntity2 * pEntity )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Entity2 State1 VOnExit"));
}

// ***************************************************************
bool cEntity2State1::VOnMessage( cEntity2 * pEntity, const Telegram &msg )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Entity2 State1 VOnMessage"));
	if(msg.Msg == 0)
	{
		pEntity->GetStateMachine()->ChangeState(pEntity->m_pState2);
		return true;
	}
	return false;
}

// ***************************************************************
cEntity2State2::cEntity2State2()
{

}

// ***************************************************************
cEntity2State2::~cEntity2State2()
{

}

// ***************************************************************
void cEntity2State2::VOnEnter( cEntity2 * pEntity )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Entity2 State2 Enter"));
	IMessageDispatchManager::GetInstance()->VDispatchMessage(1.0f, 1, 0, 1, NULL);
}

// ***************************************************************
void cEntity2State2::VOnUpdate( cEntity2 * pEntity )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Entity2 State2 VOnUpdate"));
}

// ***************************************************************
void cEntity2State2::VOnExit( cEntity2 * pEntity )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Entity2 State2 VOnExit"));
}

// ***************************************************************
bool cEntity2State2::VOnMessage( cEntity2 * pEntity, const Telegram &msg )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Entity2 State2 VOnMessage"));
	if(msg.Msg == 1)
	{
		pEntity->GetStateMachine()->ChangeState(pEntity->m_pState1);
		return true;
	}
	return false;
}
