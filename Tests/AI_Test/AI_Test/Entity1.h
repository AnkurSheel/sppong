// ***************************************************************
//  Entity1   version:  1.0   Ankur Sheel  date: 2012/07/26
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Entity1_h__
#define Entity1_h__

#include "BaseEntity.h"

class cEntity1State1;
class cEntity1State2;

class cEntity1
	: public cBaseEntity
{
public:
	cEntity1(const int iID);
	virtual ~cEntity1();
	void VOnUpdate();
	bool VOnHandleMessage(const AI::Telegram & telegram);
	AI::cStateMachine<cEntity1> * const GetStateMachine();

private:
	AI::cStateMachine<cEntity1> *	m_pStateMachine;
	cEntity1State1 *				m_pState1;
	cEntity1State2 *				m_pState2;

private:
	friend class cEntity1State1;
	friend class cEntity1State2;
};
#endif // Entity_h__