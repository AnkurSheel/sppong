// ***************************************************************
//  Entity1States   version:  1.0   Ankur Sheel  date: 2012/07/26
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Entity1States_h__
#define Entity1States_h__

#include "fsm/State.h"
#include "FSM/Telegram.h"

class cEntity1;

class cEntity1State1 
	: public AI::cState<cEntity1>
{
public:
	cEntity1State1();;
	~cEntity1State1();;
	virtual void VOnEnter(cEntity1 * pEntity);
	virtual void VOnUpdate(cEntity1 * pEntity);
	virtual void VOnExit(cEntity1 * pEntity);
	virtual void VOnPause(cEntity1 * pEntity);
	virtual void VOnResume(cEntity1 * pEntity);
	virtual bool VOnMessage(cEntity1 * pEntity, const AI::Telegram &msg);
	
private:
	int		m_iUpdateCycles;
};

class cEntity1State2 
	: public AI::cState<cEntity1>
{
public:
	cEntity1State2();
	~cEntity1State2();
	virtual void VOnEnter(cEntity1 * pEntity);
	virtual void VOnUpdate(cEntity1 * pEntity);
	virtual void VOnExit(cEntity1 * pEntity);
	virtual void VOnPause(cEntity1 * pEntity);
	virtual void VOnResume(cEntity1 * pEntity);
	virtual bool VOnMessage(cEntity1 * pEntity, const AI::Telegram &msg);

private:
	int		m_iUpdateCycles;
};
#endif // Entity1States_h__