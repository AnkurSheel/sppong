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
	void HandleMessage(const AI::Telegram & telegram);
private:
	AI::cStateMachine<cEntity> *	m_pStateMachine;
	cTestState1 *					m_pTestState1;
	cTestState2 *					m_pTestState2;
	int								m_iUpdateCycles;
	int								m_iID;

	static int						m_siNextValidID;
};
#endif // Entity_h__