// ***************************************************************
//  Entity2   version:  1.0   Ankur Sheel  date: 2012/07/27
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "Entity2.h"
#include "Entity2States.h"
#include "FSM/StateMachine.h"

using namespace AI;
using namespace Utilities;
using namespace Base;

// ***************************************************************
cEntity2::cEntity2(const int iID)
: cBaseEntity(iID)
{
	m_pState1 = new cEntity2State1();
	m_pState2 = new cEntity2State2();
	m_pStateMachine = new cStateMachine<cEntity2>(this);
	m_pStateMachine->SetCurrentState(m_pState1);
}

// ***************************************************************
cEntity2::~cEntity2()
{
	SAFE_DELETE(m_pState1);
	SAFE_DELETE(m_pState2);
	SAFE_DELETE(m_pStateMachine);
}

// ***************************************************************
void cEntity2::VOnUpdate()
{	
	m_pStateMachine->Update();
}

// ***************************************************************
bool cEntity2::VOnHandleMessage( const AI::Telegram & telegram )
{
	return m_pStateMachine->HandleMessage(telegram);
}

// ***************************************************************
AI::cStateMachine<cEntity2> * const cEntity2::GetStateMachine()
{
	return	m_pStateMachine;
}
