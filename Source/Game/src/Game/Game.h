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

	void HandlePaddleAI(const float fElapsedTime);
public:
	cGame();
	~cGame();
	void OnInit(const HINSTANCE hInstance, const int nCmdShow,const bool bFullScreen, const int iFullScreenWidth, const int iFullScreenHeight, HWND & outHwnd);
	void OnLostDevice();
	HRESULT OnResetDevice();
	void OnUpdate();
	bool OnMsgProc(const Graphics::AppMsg & msg);
	void Render(TICK tickCurrent, float fElapsedTime);
	void ProcessInput(const long xDelta,const long yDelta, const long zDelta, const bool* const pbPressedKeys, const bool* const pbMouseButtons, const float fElapsedTime );
	void Run();
	void Restart();
	void CheckForWin();
	void CheckForCollisions();
	void Cleanup();
	Base::cString GetGameTitle() const;
	TICK GetRunningTicks();
	float GetRunningTime();
	float GetFPS();

private:
	LPDIRECT3DDEVICE9			m_pD3dDevice;
	int							m_iDisplayHeight ;		// the display height of the window
	int							m_iDisplayWidth ;		// the display width of the window
	cPongGameElement *			m_pGameElements[PGE_TOTAL]; // ptr to the gameelements
	MySound::ISound *			m_pSound;
	bool						m_bSinglePlayer;
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