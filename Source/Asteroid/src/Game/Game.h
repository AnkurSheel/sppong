// *****************************************************************************
//  Game   version:  1.0   ·  date: 04/30/2008
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

namespace Utilities
{
	class IRandomGenerator;
}

namespace MySound
{
	class ISound;
}

class cScore;
class cAsteroidGameElement;
class cGameFlowStateMachine;

class cGame 
	: public IGame
	, public GameBase::cBaseApp
{
public:
	cGame(const Base::cString strName);
	void VGetGameElements(GameElementList & gameElements) const;
	Base::cVector3 VGetScreenTopLeftPos() const;
	Base::cVector3 VGetScreenBottomRightPos() const;
	void VRoundOver(const bool bPlayer1Won);
	void MoveShip(const ShipMovement eShipMovement);
	Utilities::IRandomGenerator * const GetRandomGenerator() const;

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
	int									m_iDisplayHeight ;		// the display height of the window
	int									m_iDisplayWidth ;		// the display width of the window
	GameElementList						m_pGameElements;		// ptr to the gameelements
	cGameFlowStateMachine *				m_pStateMachine;
	cScore*								m_pScore;				// ptr to Scoreboard
	Base::cVector3						m_vScreenTopLeftPos;
	Base::cVector3						m_vScreenBottomRightPos;
	shared_ptr<cAsteroidGameElement> 	m_pShip;	
	Utilities::IRandomGenerator *		m_pRandomGenerator;

private:
	friend class cStateTitleScreen;
	friend class cStateMenuScreen;
	friend class cStatePlayGame;
	friend class cStateHelpScreen;
	friend class cStateOptionsScreen;
	friend class cStatePauseScreen;
	friend class cAsteroidView;
};
#endif // Game_h__