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

#include "Essentials/BaseApp.h"

class cPaddle;
class cBall;
class cSprite;
class cWall;
class cScore;

class cStateTitleScreen;

template <class entity_type>
class cStateMachine;

class cMouseZone;

class cGame : public cBaseApp
{
private:
	LPDIRECT3DDEVICE9		m_pD3dDevice;
	UINT					m_iDisplayHeight ;		// the display height of the window
	UINT					m_iDisplayWidth ;		// the display width of the window
	cPaddle*				m_pPaddle;				// ptr to the paddle
	cBall*					m_pBall;				// ptr to the ball
	cWall*					m_pWall;				// ptr to wall
	cScore*					m_pScore;				// ptr to Scoreboard
	cSprite*				m_pPaddleSprite;		// the sprite for the paddle
	cSprite*				m_pBallSprite;			// the sprite for the ball
	cSprite*				m_pWallSprite;			// the sprite for the wall
	cSprite*				m_pTitleScreenSprite;	// the sprite for the title screen
	cSprite*				m_pCursorSprite;		// the sprite for the title screen
	cSprite*				m_pSinglePlayerSprite;	// the sprite for the Single Player Menu
	cSprite*				m_pTwoPlayerSprite;		// the sprite for the Single Player Menu
	cSprite*				m_pQuitSprite;		// the sprite for the Single Player Menu
	
	bool					m_bDisplayFPS;
	bool					m_bSinglePlayer;
	cStateMachine<cGame>*	m_pStateMachine;

	cMouseZone*				m_pMouseZones;
	cGame(const cGame&){}
	cGame operator =(const cGame&){}
	void HandlePaddleAI(const float fElapsedTime);
public:
	cGame();
	~cGame();
	void Render();
	void OnResetDevice();
	void OnLostDevice();
	void OnInit(LPDIRECT3DDEVICE9 const pDevice, const UINT iDisplayHeight, const UINT iDisplayWidth);
	//void ProcessInput(const long xDelta,const long yDelta, const long zDelta, const bool* const pbPressedKeys, const bool* const pbMouseButtons, const float fElapsedTime );
	void ProcessInput(const long xDelta,const long yDelta, const long zDelta, const bool* const pbPressedKeys, const bool* const pbMouseButtons, const float fElapsedTime );
	void Cleanup();
	void Restart();
	void CheckForWin();
	void CheckForCollisions();
	void DisplayTitle();
private:
	friend class cStateTitleScreen;
	friend class cStateMenuScreen;
	friend class cStatePlayGame;
};
#endif // Game_h__