// ***************************************************************
//  Entity1   version:  1.0   Ankur Sheel  date: 2012/07/27
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "Entity1.h"
#include "Entity1States.h"
#include "FSM/StateMachine.h"

using namespace AI;
using namespace Utilities;
using namespace Base;

// ***************************************************************
cEntity1::cEntity1(const int iID)
: cBaseEntity(iID)
{
	m_pState1 = new cEntity1State1();
	m_pState2 = new cEntity1State2();
	m_pStateMachine = new cStateMachine<cEntity1>(this);
	m_pStateMachine->SetCurrentState(m_pState1);
}

// ***************************************************************
cEntity1::~cEntity1()
{
	SAFE_DELETE(m_pState1);
	SAFE_DELETE(m_pState2);
	SAFE_DELETE(m_pStateMachine);
}

// ***************************************************************
void cEntity1::VOnUpdate()
{	
	m_pStateMachine->Update();
}

// ***************************************************************
bool cEntity1::VOnHandleMessage( const AI::Telegram & telegram )
{
	return m_pStateMachine->HandleMessage(telegram);
}

// ***************************************************************
AI::cStateMachine<cEntity1> * const cEntity1::GetStateMachine()
{
	return	m_pStateMachine;
}
