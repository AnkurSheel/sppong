// *****************************************************************************
//  MPongView   version:  1.0   Ankur Sheel  date: 2011/05/02
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef MPongView_h__
#define MPongView_h__

#include "HumanView.h"

class cGame;
class P1PaddleHandler;
class P2PaddleHandler;

namespace GameBase
{
	class IBaseApp;
}

class cMPongView 
	: public GameBase::cHumanView
{
public:
	cMPongView();
	~cMPongView();
	void VOnCreateDevice(GameBase::IBaseApp * pGame,
		const HINSTANCE & hInst, const HWND & hWnd);
	void VOnUpdate(const TICK tickCurrent, const float fElapsedTime);
	void VRenderPrivate();
	bool VOnMsgProc( const Base::AppMsg & msg );	
	void OnSinglePlayerSelected(cGame * pGame);
	void OnMultiPlayerSelected(cGame * pGame);

private:
	shared_ptr<P1PaddleHandler>		m_P1PaddleHandler;
	shared_ptr<P2PaddleHandler>		m_P2PaddleHandler;
	cGame	*						m_pGame;
};
#endif // MPongView_h__
