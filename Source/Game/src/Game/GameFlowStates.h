// ***************************************************************
//  GameFlowStates   version:  1.0   Ankur Sheel  date: 05/24/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef GameFlowStates_h__
#define GameFlowStates_h__

#include "fsm/State.h"

class cGame;
struct Telegram;

class IGameFlowStates
	: public AI::IState<cGame>
{
};

class cStateTitleScreen 
	: public IGameFlowStates
{
private:
	cStateTitleScreen();
	TICK m_tickCurrentTime;
public:
	~cStateTitleScreen();
	static cStateTitleScreen *Instance();
	void Enter(cGame *pGame);
	void Execute(cGame *pGame);
	void Exit(cGame *pGame);
	bool OnMessage(cGame *pGame, const Telegram &msg);
};

class cStateMenuScreen 
	: public IGameFlowStates
{
private:
	cStateMenuScreen();
public:
	~cStateMenuScreen();
	static cStateMenuScreen *Instance();
	void Enter(cGame *pGame);
	void Execute(cGame *pGame);
	void Exit(cGame *pGame);
	bool OnMessage(cGame *pGame, const Telegram &msg);
};

class cStatePlayGame 
	: public IGameFlowStates
{
private:
	cStatePlayGame();
public:
	virtual ~cStatePlayGame();
	static cStatePlayGame *Instance();
	virtual void Enter(cGame *pGame);
	virtual void Execute(cGame *pGame);
	virtual void Exit(cGame *pGame);
	virtual bool OnMessage(cGame *pGame, const Telegram &msg);
};
#endif // GameFlowStates_h__