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

class cStateTitleScreen 
: public IState<cGame>
{
private:
	cStateTitleScreen();
	float m_fCurrentTime;
public:
	virtual ~cStateTitleScreen();
	static cStateTitleScreen *Instance();
	virtual void Enter(cGame *pGame);
	virtual void Execute(cGame *pGame);
	virtual void Exit(cGame *pGame);
	virtual bool OnMessage(cGame *pGame, const Telegram &msg);
};

class cStateMenuScreen 
	: public IState<cGame>
{
private:
	cStateMenuScreen();
	int		m_iSinglePlayerSpritePosY;
	int		m_iTwoPlayerSpritePosY;
	int		m_iQuitSpritePosY;
public:
	virtual ~cStateMenuScreen();
	static cStateMenuScreen *Instance();
	virtual void Enter(cGame *pGame);
	virtual void Execute(cGame *pGame);
	virtual void Exit(cGame *pGame);
	virtual bool OnMessage(cGame *pGame, const Telegram &msg);
};

class cStatePlayGame 
	: public IState<cGame>
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