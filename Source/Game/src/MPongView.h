// ***************************************************************
//  MPongView   version:  1.0   Ankur Sheel  date: 2011/05/02
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef MPongView_h__
#define MPongView_h__

#include "HumanView.h"

class cGame;
class P1PaddleHandler;
class P2PaddleHandler;

class cMPongView : public GameBase::cHumanView
{
public:
	cMPongView();
	~cMPongView();
	void VOnUpdate(cGame * pGame, float fElapsedTime);
	void VOnRender(cGame * pGame, TICK tickCurrent, float fElapsedTime);
	bool VOnMsgProc( const Graphics::AppMsg & msg );	
	void OnSinglePlayerSelected(cGame * pGame);
	void OnMultiPlayerSelected(cGame * pGame);

private:
	bool							m_bDisplayFPS;
	shared_ptr<P1PaddleHandler>		m_P1PaddleHandler;
	shared_ptr<P2PaddleHandler>		m_P2PaddleHandler;
};
#endif // MPongView_h__
