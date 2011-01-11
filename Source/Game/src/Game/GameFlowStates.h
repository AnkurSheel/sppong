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
	: public IState<cGame>
{
public:
	virtual void OnLostDevice(cGame *pGame) = 0;
	virtual void OnResetDevice(cGame *pGame) = 0;
};

class cStateTitleScreen 
	: public IGameFlowStates
{
private:
	cStateTitleScreen();
	float m_fCurrentTime;
public:
	~cStateTitleScreen();
	static cStateTitleScreen *Instance();
	void Enter(cGame *pGame);
	void Execute(cGame *pGame);
	void Exit(cGame *pGame);
	bool OnMessage(cGame *pGame, const Telegram &msg);
	void OnLostDevice(cGame *pGame);
	void OnResetDevice(cGame *pGame);
};

class cStateMenuScreen 
	: public IGameFlowStates
{
private:
	cStateMenuScreen();
	int		m_iSinglePlayerSpritePosY;
	int		m_iTwoPlayerSpritePosY;
	int		m_iQuitSpritePosY;
public:
	~cStateMenuScreen();
	static cStateMenuScreen *Instance();
	void Enter(cGame *pGame);
	void Execute(cGame *pGame);
	void Exit(cGame *pGame);
	bool OnMessage(cGame *pGame, const Telegram &msg);
	void OnLostDevice(cGame *pGame);
	void OnResetDevice(cGame *pGame);
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
	void OnLostDevice(cGame *pGame);
	void OnResetDevice(cGame *pGame);

};
#endif // GameFlowStates_h__