// ***************************************************************
//  StateMachine   version:  1.0   Ankur Sheel  date: 05/23/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef StateMachine_h__
#define StateMachine_h__

struct Telegram;

#include "State.h"

template <class entity_type>
class cStateMachine
{
private:
	cStateMachine(const cStateMachine&){}
	cStateMachine operator =(const cStateMachine&){}

public:
	cStateMachine(entity_type *owner);
	virtual ~cStateMachine();
	void SetCurrentState(IState<entity_type>* state);
	void SetPreviousState(IState<entity_type>* state);
	void SetGlobalState(IState<entity_type>* state);
	void Update();
	void ChangeState(IState<entity_type>* pNewState);
	void RevertToPreviousState();
	IState<entity_type>* GetCurrentState();
	IState<entity_type>* GetPreviousState();
	IState<entity_type>* GetGlobalState();
	bool IsInState(const IState<entity_type>& state);
	bool HandleMessage(const Telegram& msg);

protected:
	entity_type * m_pOwner;
	IState<entity_type> * m_pCurrentState;
	IState<entity_type> * m_pPreviousState;
	IState<entity_type> * m_pGlobalState;
};

#include "Statemachine.inl"

#endif // StateMachine_h__