// ***************************************************************
//  Entity   version:  1.0   Ankur Sheel  date: 2012/07/26
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Entity_h__
#define Entity_h__

#include "fsm/StateMachine.h"

class cTestState1;
class cTestState2;
namespace AI
{
	struct Telegram;
}
class cEntity
	: public Base::cNonCopyable
{
public:
	cEntity(const int iID);
	virtual ~cEntity();
	void Update();
	void SetID(const int iID);
	int GetID();
	bool HandleMessage(const AI::Telegram & telegram);
	AI::cStateMachine<cEntity> * const GetStateMachine() { return	m_pStateMachine; }
private:
	AI::cStateMachine<cEntity> *	m_pStateMachine;
	cTestState1 *					m_pTestState1;
	cTestState2 *					m_pTestState2;
	int								m_iID;

	static int						m_siNextValidID;
private:
	friend class cTestState1;
	friend class cTestState2;
};
#endif // Entity_h__