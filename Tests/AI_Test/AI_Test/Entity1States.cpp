// ***************************************************************
//  Entity1States   version:  1.0   Ankur Sheel  date: 2012/07/26
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "Entity1States.h"
#include "MessageDispatchManager.hxx"
#include "Entity1.h"
#include "FSM/StateMachine.h"

using namespace Utilities;
using namespace Base;
using namespace AI;
using namespace GameBase;

// ***************************************************************
cEntity1State1::cEntity1State1()
{

}

// ***************************************************************
cEntity1State1::~cEntity1State1()
{

}

// ***************************************************************
void cEntity1State1::VOnEnter( cEntity1 * pEntity )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Entity1 State1Enter"));
}

// ***************************************************************
void cEntity1State1::VOnUpdate( cEntity1 * pEntity )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Entity1 State1VOnUpdate"));
	IMessageDispatchManager::GetInstance()->DispatchMessage(0.0f, 0, 1, 0, NULL);
}

// ***************************************************************
void cEntity1State1::VOnExit( cEntity1 * pEntity )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Entity1 State1VOnExit"));
}

// ***************************************************************
bool cEntity1State1::VOnMessage( cEntity1 * pEntity, const Telegram &msg )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Entity1 State1VOnMessage"));
	if(msg.Msg == 0)
	{
		pEntity->GetStateMachine()->ChangeState(pEntity->m_pState2);
		return true;
	}
	return false;
}

// ***************************************************************
cEntity1State2::cEntity1State2()
{

}

// ***************************************************************
cEntity1State2::~cEntity1State2()
{

}

// ***************************************************************
void cEntity1State2::VOnEnter( cEntity1 * pEntity )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Entity1 State2 Enter"));
	IMessageDispatchManager::GetInstance()->DispatchMessage(1.0f, 0, 1, 1, NULL);
}

// ***************************************************************
void cEntity1State2::VOnUpdate( cEntity1 * pEntity )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Entity1 State2 VOnUpdate"));
}

// ***************************************************************
void cEntity1State2::VOnExit( cEntity1 * pEntity )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Entity1 State2 VOnExit"));
}

// ***************************************************************
bool cEntity1State2::VOnMessage( cEntity1 * pEntity, const Telegram &msg )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Entity1 State2 VOnMessage"));
	if(msg.Msg == 1)
	{
		pEntity->GetStateMachine()->ChangeState(pEntity->m_pState1);
		return true;
	}
	return false;
}
