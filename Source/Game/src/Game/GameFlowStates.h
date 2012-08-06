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

class IGameFlowStates
	: public AI::cState<cGame>
{
};

class cStateTitleScreen 
	: public IGameFlowStates
{
public:
	~cStateTitleScreen();
	static cStateTitleScreen *Instance();
	void VOnEnter(cGame *pGame);
	void VOnUpdate(cGame *pGame);
	void VOnExit(cGame *pGame);
	bool VOnMessage(cGame *pGame, const AI::Telegram &msg);
private:
	cStateTitleScreen();
};

class cStateMenuScreen 
	: public IGameFlowStates
{
public:
	~cStateMenuScreen();
	static cStateMenuScreen *Instance();
	void VOnEnter(cGame *pGame);
	void VOnUpdate(cGame *pGame);
	void VOnExit(cGame *pGame);
	bool VOnMessage(cGame *pGame, const AI::Telegram &msg);
private:
	cStateMenuScreen();
};

class cStatePlayGame 
	: public IGameFlowStates
{
public:
	virtual ~cStatePlayGame();
	static cStatePlayGame *Instance();
	virtual void VOnEnter(cGame *pGame);
	virtual void VOnUpdate(cGame *pGame);
	virtual void VOnExit(cGame *pGame);
	virtual bool VOnMessage(cGame *pGame, const AI::Telegram &msg);
private:
	cStatePlayGame();
};
#endif // GameFlowStates_h__