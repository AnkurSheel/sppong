// ***************************************************************
//  TestStates   version:  1.0   Ankur Sheel  date: 2012/07/26
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "TestStates.h"
#include "MessageDispatchManager.h"
#include "Entity.h"

using namespace Utilities;
using namespace Base;
using namespace AI;

// ***************************************************************
cTestState1::cTestState1()
{

}

// ***************************************************************
cTestState1::~cTestState1()
{

}

// ***************************************************************
void cTestState1::Enter( cEntity * pEntity )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Test State1 Enter"));
}

// ***************************************************************
void cTestState1::Execute( cEntity * pEntity )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Test State1 Execute"));
	cMessageDispatchManager::GetInstance()->DispatchMessage(0.0f, 0, 0, 0, NULL);
}

// ***************************************************************
void cTestState1::Exit( cEntity * pEntity )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Test State1 Exit"));
}

// ***************************************************************
bool cTestState1::OnMessage( cEntity * pEntity, const Telegram &msg )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Test State1 OnMessage"));
	if(msg.Msg == 0)
	{
		pEntity->GetStateMachine()->ChangeState(pEntity->m_pTestState2);
		return true;
	}
	return false;
}

// ***************************************************************
cTestState2::cTestState2()
{

}

// ***************************************************************
cTestState2::~cTestState2()
{

}

// ***************************************************************
void cTestState2::Enter( cEntity * pEntity )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Test State2 Enter"));
	cMessageDispatchManager::GetInstance()->DispatchMessage(1.0f, 0, 0, 1, NULL);
}

// ***************************************************************
void cTestState2::Execute( cEntity * pEntity )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Test State2 Execute"));
}

// ***************************************************************
void cTestState2::Exit( cEntity * pEntity )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Test State2 Exit"));
}

// ***************************************************************
bool cTestState2::OnMessage( cEntity * pEntity, const Telegram &msg )
{
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Test State2 OnMessage"));
	if(msg.Msg == 1)
	{
		pEntity->GetStateMachine()->ChangeState(pEntity->m_pTestState1);
		return true;
	}
	return false;
}
