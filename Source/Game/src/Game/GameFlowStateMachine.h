#pragma once
#include "fsm\statemachine.h"
#include "Game.h"

class IGameFlowStates;

class cGameFlowStateMachine :
	public cStateMachine<cGame>
{
public:
	cGameFlowStateMachine::cGameFlowStateMachine(cGame *pGame);
	cGameFlowStateMachine::~cGameFlowStateMachine(void);
	void OnLostDevice(cGame *pGame);
	void OnResetDevice(cGame *pGame);
private:
	//cGame * m_pGame;
	//IGameFlowStates * m_pCurrentState;
	//IGameFlowStates * m_pPreviousState;
	//IGameFlowStates * m_pGlobalState;
};
