// ***************************************************************
//  GraphicsTestView   version:  1.0   Ankur Sheel  date: 2012/08/31
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef GraphicsTestView_h__
#define GraphicsTestView_h__

#include "HumanView.h"

class cGame;

namespace GameBase
{
	class IBaseApp;
}

class cGraphicsTestView 
	: public GameBase::cHumanView
{
public:
	cGraphicsTestView();
	~cGraphicsTestView();
	void VOnCreateDevice(GameBase::IBaseApp * pGame, const HINSTANCE hInst, const HWND hWnd, int iClientWidth, int iClientHeight );
	void VOnUpdate(TICK tickCurrent, const float fElapsedTime);
	void VOnRender(TICK tickCurrent, float fElapsedTime);
	bool VOnMsgProc( const Graphics::AppMsg & msg );	
	void TestUIControls();
	void TestPoints();
	void Finished();

private:
	cGame	*					m_pGame;
	Graphics::IBaseControl *	m_pInfoLabelControl;
	bool						m_bFinished;
};
#endif // GraphicsTestView_h__
