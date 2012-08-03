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
: m_iUpdateCycles(0)
{

}

// ***************************************************************
cEntity1State1::~cEntity1State1()
{

}

// ***************************************************************
void cEntity1State1::VOnEnter( cEntity1 * pEntity )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "%s State1Enter", pEntity->VGetName().GetData()));
}

// ***************************************************************
void cEntity1State1::VOnUpdate( cEntity1 * pEntity )
{
	m_iUpdateCycles++;
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "%s State1 VOnUpdate %d", pEntity->VGetName().GetData(), m_iUpdateCycles));
	if(m_iUpdateCycles == 5)
	{
		IMessageDispatchManager::GetInstance()->VDispatchMessage(0.0f, 0, 1, 0, NULL);
	}
	else if(m_iUpdateCycles == 10)
	{
		IMessageDispatchManager::GetInstance()->VDispatchMessage(1.0f, 0, 1, 1, NULL);
	}
	else if(m_iUpdateCycles == 15)
	{
		pEntity->GetStateMachine()->RequestPushState(pEntity->m_pState2);
	}
}

// ***************************************************************
void cEntity1State1::VOnExit( cEntity1 * pEntity )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "%s State1 VOnExit", pEntity->VGetName().GetData()));
}

// ***************************************************************
bool cEntity1State1::VOnMessage( cEntity1 * pEntity, const Telegram &msg )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "%s State1 VOnMessage", pEntity->VGetName().GetData()));
	if(msg.Msg == 0)
	{
		pEntity->GetStateMachine()->RequestChangeState(pEntity->m_pState2);
		return true;
	}
	return false;
}

// ***************************************************************
void cEntity1State1::VOnPause( cEntity1 * pEntity )
{
	m_bIsPaused = true;
}

// ***************************************************************
void cEntity1State1::VOnResume( cEntity1 * pEntity )
{
	m_bIsPaused = false;
}

// ***************************************************************
cEntity1State2::cEntity1State2()
: m_iUpdateCycles(0)
{

}

// ***************************************************************
cEntity1State2::~cEntity1State2()
{

}

// ***************************************************************
void cEntity1State2::VOnEnter( cEntity1 * pEntity )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "%s State2 Enter", pEntity->VGetName().GetData()));
}

// ***************************************************************
void cEntity1State2::VOnUpdate( cEntity1 * pEntity )
{
	m_iUpdateCycles++;
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "%s State2 VOnUpdate %d", pEntity->VGetName().GetData(), m_iUpdateCycles));
	if(m_iUpdateCycles == 5)
	{
		IMessageDispatchManager::GetInstance()->VDispatchMessage(0.0f, 0, 1, 0, NULL);
	}
	else if(m_iUpdateCycles == 10)
	{
		IMessageDispatchManager::GetInstance()->VDispatchMessage(1.0f, 0, 1, 1, NULL);
	}
	else if(m_iUpdateCycles == 25)
	{
		pEntity->GetStateMachine()->RequestPopState();
	}

}

// ***************************************************************
void cEntity1State2::VOnExit( cEntity1 * pEntity )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "%s State2 VOnExit", pEntity->VGetName().GetData()));
}

// ***************************************************************
bool cEntity1State2::VOnMessage( cEntity1 * pEntity, const Telegram &msg )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "%s State2 VOnMessage", pEntity->VGetName().GetData()));
	if(msg.Msg == 0)
	{
		pEntity->GetStateMachine()->RequestChangeState(pEntity->m_pState1);
		return true;
	}
	return false;
}

// ***************************************************************
void cEntity1State2::VOnPause( cEntity1 * pEntity)
{
	m_bIsPaused = true;
}

// ***************************************************************
void cEntity1State2::VOnResume( cEntity1 * pEntity)
{
	m_bIsPaused = false;
}
