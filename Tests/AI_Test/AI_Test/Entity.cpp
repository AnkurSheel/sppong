// ***************************************************************
//  Entity   version:  1.0   Ankur Sheel  date: 2012/07/27
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "Entity.h"
#include "TestStates.h"

using namespace AI;
using namespace Utilities;
using namespace Base;

int cEntity::m_siNextValidID = 0;

// ***************************************************************
cEntity::cEntity(const int iID)
{
	m_pTestState1 = new cTestState1;
	m_pTestState2 = new cTestState2();
	m_pStateMachine = new cStateMachine<cEntity>(this);
	m_pStateMachine->SetCurrentState(m_pTestState1);
	SetID(iID);
}

// ***************************************************************
cEntity::~cEntity()
{
	SAFE_DELETE(m_pTestState1);
	SAFE_DELETE(m_pTestState2);
	SAFE_DELETE(m_pStateMachine);
}

// ***************************************************************
void cEntity::Update()
{	
	m_pStateMachine->Update();
}

// ***************************************************************
void cEntity::SetID(const int iID)
{
	//make sure the val is equal to or greater than the next available ID
	if(iID >= m_siNextValidID)
	{
		m_iID = iID;
		m_siNextValidID = m_iID + 1;
	}
}

// ***************************************************************
int cEntity::GetID()
{
	return m_iID;
}

// ***************************************************************
bool cEntity::HandleMessage( const AI::Telegram & telegram )
{
	return m_pStateMachine->HandleMessage(telegram);
}
