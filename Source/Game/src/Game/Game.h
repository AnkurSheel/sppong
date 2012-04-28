// ***************************************************************
//  Game   version:  1.0   ·  date: 04/30/2008
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

namespace Utilities
{
	class ITimer;
}
namespace MySound
{
	class ISound;
}

class cScore;
class cPongGameElement;
class cGameFlowStateMachine;
class cMPongView;

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
	cGame();
	~cGame();
	void VOnInitialization(const HINSTANCE hInstance, const int nCmdShow,const bool bFullScreen, const int iFullScreenWidth, const int iFullScreenHeight, HWND & outHwnd);
	void OnUpdate();
	void VOnLostDevice();
	HRESULT VOnResetDevice();
	bool VOnMsgProc(const Graphics::AppMsg & msg);
	void VRun();
	Base::cString VGetGameTitle() const;
	void Render(TICK tickCurrent, float fElapsedTime);
	void Restart();
	void CheckForWin();
	void CheckForCollisions();
	void Cleanup();
	TICK GetRunningTicks();
	float GetRunningTime();
	float GetFPS();
	void MoveLeftPaddle(bool bMoveDown);
	void MoveRightPaddle(bool bMoveDown);
	void HandlePaddleAI(const float fElapsedTime);
	bool IsSinglePlayer();

private:
	void SinglePlayerButtonPressed(bool bPressed);
	void MultiPlayerButtonPressed(bool bPressed);
	void QuitButtonPressed(bool bPressed);

private:
	LPDIRECT3DDEVICE9			m_pD3dDevice;
	int							m_iDisplayHeight ;		// the display height of the window
	int							m_iDisplayWidth ;		// the display width of the window
	cPongGameElement *			m_pGameElements[PGE_TOTAL]; // ptr to the gameelements
	MySound::ISound *			m_pSound;
	bool						m_bSinglePlayer;
	bool						m_bMultiPlayer;
	cGameFlowStateMachine *		m_pStateMachine;
	cMPongView *				m_pPongView;
	Utilities::ITimer *			m_pGameTimer;
	cScore*						m_pScore;				// ptr to Scoreboard

private:
	friend class cStateTitleScreen;
	friend class cStateMenuScreen;
	friend class cStatePlayGame;
};
#endif // Game_h__