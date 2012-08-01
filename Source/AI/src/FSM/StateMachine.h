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

namespace AI
{
	struct Telegram;
}

#include "State.h"

namespace AI
{
	template <class entity_type>
	class cStateMachine
		: public Base::cNonCopyable
	{
	public:
		cStateMachine(entity_type *owner);
		virtual ~cStateMachine();
		void SetCurrentState(cState<entity_type>* state);
		void SetPreviousState(cState<entity_type>* state);
		void SetGlobalState(cState<entity_type>* state);
		void Update();
		void ChangeState(cState<entity_type>* pNewState);
		void RevertToPreviousState();
		cState<entity_type>* GetCurrentState();
		cState<entity_type>* GetPreviousState();
		cState<entity_type>* GetGlobalState();
		bool IsInState(const cState<entity_type>& state);
		bool HandleMessage(const Telegram& msg);
		void DoStateReplacement();

	protected:
		entity_type *			m_pOwner;
		cState<entity_type> *	m_pCurrentState;
		cState<entity_type> *	m_pNextState;
		cState<entity_type> *	m_pPreviousState;
		cState<entity_type> *	m_pGlobalState;
	
	private:
		bool					m_bRequestedStateChange;

	};

#include "Statemachine.inl"
}
#endif // StateMachine_h__