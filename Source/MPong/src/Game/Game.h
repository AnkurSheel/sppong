// *****************************************************************************
//  Game   version:  1.0   �  date: 04/30/2008
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef Game_h__
#define Game_h__

#include "Game.hxx"
#include "BaseApp.h"

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
	cPongGameElement ** const VGetGameElements() const;
	Base::cVector3 VGetScreenTopLeftPos() const;
	Base::cVector3 VGetScreenBottomRightPos() const;
	void VRoundOver(const bool bPlayer1Won);
	void HandlePaddleAI(const float fElapsedTime);
	bool IsSinglePlayer();
	void MoveLeftPaddle(bool bMoveDown);
	void MoveRightPaddle(bool bMoveDown);

private:
	~cGame();
	void VOnInitialization(const HINSTANCE & hInstance, const int nCmdShow,
		const Base::cString & strOptionsFile);
	Base::cString VGetGameTitle() const;
	void VOnUpdate();
	void VCleanup();
	void Restart();
	bool VOnHandleMessage(const AI::Telegram & telegram);
	void VCreateHumanView();

private:
	int							m_iDisplayHeight ;		// the display height of the window
	int							m_iDisplayWidth ;		// the display width of the window
	cPongGameElement **			m_ppGameElements; // ptr to the gameelements
	//MySound::ISound *			m_pSound;
	bool						m_bSinglePlayer;
	bool						m_bMultiPlayer;
	cGameFlowStateMachine *		m_pStateMachine;
	cScore*						m_pScore;				// ptr to Scoreboard
	Base::cVector3				m_vScreenTopLeftPos;
	Base::cVector3				m_vScreenBottomRightPos;
	
private:
	friend class cStateTitleScreen;
	friend class cStateMenuScreen;
	friend class cStatePlayGame;
	friend class cStateHelpScreen;
	friend class cStateOptionsScreen;
	friend class cStatePauseScreen;
};
#endif // Game_h__