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

namespace Graphics
{
	class ISprite;
	class IMouseZone;
}

class cScore;

class cPongGameElement;

class cGameFlowStateMachine;

namespace MySound
{
	class ISound;
}

class cGame 
	: public Graphics::IBaseApp
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
	void ProcessInput(const long xDelta,const long yDelta, const long zDelta, const bool* const pbPressedKeys, const bool* const pbMouseButtons, const float fElapsedTime );
	void Cleanup();
	void Restart();
	void CheckForWin();
	void CheckForCollisions();

private:
	LPDIRECT3DDEVICE9			m_pD3dDevice;
	UINT						m_iDisplayHeight ;		// the display height of the window
	UINT						m_iDisplayWidth ;		// the display width of the window
	cPongGameElement *			m_pGameElements[PGE_TOTAL]; // ptr to the gameelements
	cScore*						m_pScore;				// ptr to Scoreboard
	Graphics::ISprite *			m_pTitleScreenSprite;	// the sprite for the title screen
	Graphics::ISprite *			m_pCursorSprite;		// the sprite for the title screen
	Graphics::ISprite *			m_pSinglePlayerSprite;	// the sprite for the Single Player Menu
	Graphics::ISprite *			m_pTwoPlayerSprite;		// the sprite for the Single Player Menu
	Graphics::ISprite *			m_pQuitSprite;		// the sprite for the Single Player Menu
	Graphics::ISprite *			m_pTableSprite;		// the sprite for the Single Player Menu
	MySound::ISound *			m_pSound;
	bool						m_bDisplayFPS;
	bool						m_bSinglePlayer;
	cGameFlowStateMachine *		m_pStateMachine;
	Graphics::IMouseZone *		m_pMouseZones;

private:
	friend class cStateTitleScreen;
	friend class cStateMenuScreen;
	friend class cStatePlayGame;
};
#endif // Game_h__