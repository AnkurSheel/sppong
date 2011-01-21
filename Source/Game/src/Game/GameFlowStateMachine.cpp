// ***************************************************************
//  GameFlowStateMachine   version:  1.0   Ankur Sheel  date: 2011/01/21
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "GameFlowStateMachine.h"
#include "GameFlowStates.h"

cGameFlowStateMachine::cGameFlowStateMachine(cGame *pGame)
: cStateMachine<cGame>(pGame)
{
}
// ***************************************************************

cGameFlowStateMachine::~cGameFlowStateMachine(void)
{
}
// ***************************************************************

void cGameFlowStateMachine::OnLostDevice(cGame *pGame)
{
	IGameFlowStates * pGameFlowStates = NULL;
	if(m_pGlobalState)
	{
		pGameFlowStates = dynamic_cast<IGameFlowStates*>(m_pGlobalState);
		pGameFlowStates->OnLostDevice(pGame);
	}
	if(m_pCurrentState)
	{
		pGameFlowStates = dynamic_cast<IGameFlowStates*>(m_pCurrentState);
		pGameFlowStates->OnLostDevice(pGame);
	}
}
// ***************************************************************

void cGameFlowStateMachine::OnResetDevice(cGame *pGame)
{
	IGameFlowStates * pGameFlowStates = NULL;
	if(m_pGlobalState)
	{
		pGameFlowStates = dynamic_cast<IGameFlowStates*>(m_pGlobalState);
		pGameFlowStates->OnResetDevice(pGame);
	}
	if(m_pCurrentState)
	{
		pGameFlowStates = dynamic_cast<IGameFlowStates*>(m_pCurrentState);
		pGameFlowStates->OnResetDevice(pGame);
	}
}
// ***************************************************************
