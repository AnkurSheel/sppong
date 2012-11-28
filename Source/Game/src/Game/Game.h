// ***************************************************************
//  Game   version:  1.0   �  date: 04/30/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Game_h__
#define Game_h__

#include "Game.hxx"
#include "BaseApp.h"

namespace Base
{
	class cString;
}

namespace GameBase
{
	class cHumanView;
}

namespace MySound
{
	class ISound;
}

class cScore;
class cPongGameElement;
class cGameFlowStateMachine;

class cGame 
	: public IGame
	, public GameBase::cBaseApp
{
private:
	enum PONGGAMEELEMENTS
	{
		PGE_UNKNOWN = -1,
		PGE_BALL,
		PGE_PADDLE_LEFT,
		PGE_PADDLE_RIGHT,
		PGE_WALL_UP,
		PGE_WALL_DOWN,
		PGE_TOTAL
	};

	enum GAMESOUNDS
	{
		GS_UNKNOWN = -1,
		GS_BALL_WALL_COLLISION,
		GS_BALL_PADDLE_COLLISION,
		GS_WIN,
		GS_MAIN_MENU_MUSIC,
		GS_TOTAL
	};

public:
	cGame(const Base::cString strName);
	~cGame();
	void VOnInitialization(const HINSTANCE & hInstance, const int nCmdShow,
		const Base::cString & strOptionsFileName);
	Base::cString VGetGameTitle() const;
	void VCleanup();
	void Restart();
	void CheckForWin();
	void CheckForCollisions();
	void MoveLeftPaddle(bool bMoveDown);
	void MoveRightPaddle(bool bMoveDown);
	void HandlePaddleAI(const float fElapsedTime);
	bool IsSinglePlayer();
	bool VOnHandleMessage(const AI::Telegram & telegram);
private:
	void VOnUpdate();
	void SinglePlayerButtonPressed(bool bPressed);
	void MultiPlayerButtonPressed(bool bPressed);
	void QuitButtonPressed(bool bPressed);
	void VCreateHumanView();

private:
	int							m_iDisplayHeight ;		// the display height of the window
	int							m_iDisplayWidth ;		// the display width of the window
	cPongGameElement *			m_pGameElements[PGE_TOTAL]; // ptr to the gameelements
	MySound::ISound *			m_pSound;
	bool						m_bSinglePlayer;
	bool						m_bMultiPlayer;
	cGameFlowStateMachine *		m_pStateMachine;
	cScore*						m_pScore;				// ptr to Scoreboard

private:
	friend class cStateTitleScreen;
	friend class cStateMenuScreen;
	friend class cStatePlayGame;
};
#endif // Game_h__