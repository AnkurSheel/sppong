// ***************************************************************
//  Entity2State   version:  1.0   Ankur Sheel  date: 2012/07/26
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Entity2State_h__
#define Entity2State_h__

#include "fsm/State.h"
#include "FSM/Telegram.h"

class cEntity2;

class cEntity2State1 
	: public AI::IState<cEntity2>
{
public:
	cEntity2State1();;
	~cEntity2State1();;
	virtual void VOnEnter(cEntity2 * pEntity);
	virtual void VOnUpdate(cEntity2 * pEntity);
	virtual void VOnExit(cEntity2 * pEntity);
	virtual bool VOnMessage(cEntity2 * pEntity, const AI::Telegram &msg);
};

class cEntity2State2 
	: public AI::IState<cEntity2>
{
public:
	cEntity2State2();
	~cEntity2State2();
	virtual void VOnEnter(cEntity2 * pEntity);
	virtual void VOnUpdate(cEntity2 * pEntity);
	virtual void VOnExit(cEntity2 * pEntity);
	virtual bool VOnMessage(cEntity2 * pEntity, const AI::Telegram &msg);
};
#endif // Entity2State_h__