// *****************************************************************************
//  AsteroidView   version:  1.0   Ankur Sheel  date: 2013/02/21
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef AsteroidView_h__
#define AsteroidView_h__

#include "HumanView.h"

class cGame;
class ShipPaddleHandler;
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

private:
	shared_ptr<ShipPaddleHandler>		m_P1PaddleHandler;
	cGame	*						m_pGame;
};
#endif // AsteroidView_h__