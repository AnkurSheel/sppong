// ***************************************************************
//  States   version:  1.0   Ankur Sheel  date: 2012/07/26
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef TestStates_h__
#define TestStates_h__

#include "fsm/State.h"
class cEntity;

class cTestState1 
	: public AI::IState<cEntity>
{
public:
	cTestState1();;
	~cTestState1();;
	virtual void Enter(cEntity * pEntity);
	virtual void Execute(cEntity * pEntity);
	virtual void Exit(cEntity * pEntity);
	virtual bool OnMessage(cEntity * pEntity, const Telegram &msg);
};

class cTestState2 
	: public AI::IState<cEntity>
{
public:
	cTestState2();
	~cTestState2();
	virtual void Enter(cEntity * pEntity);
	virtual void Execute(cEntity * pEntity);
	virtual void Exit(cEntity * pEntity);
	virtual bool OnMessage(cEntity * pEntity, const Telegram &msg);
};
#endif // TestStates_h__