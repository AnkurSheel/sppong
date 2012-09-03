// ***************************************************************
//  MpongView   version:  1.0   Ankur Sheel  date: 2011/05/02
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "MpongView.h"
#include "Sprite.hxx"
#include "DxBase.hxx"
#include "Game/Game.h"
#include "Input.hxx"
#include "Font.hxx"
#include "Game/Elements/Score.h"
#include "P1PaddleHandler.h"
#include "P2PaddleHandler.h"

using namespace Utilities;
using namespace Graphics;
using namespace GameBase;
using namespace Base;

// ***************************************************************
cMPongView::cMPongView()
: m_bDisplayFPS(false)
, m_pGame(NULL)
{
}

// ***************************************************************
cMPongView::~cMPongView()
{
}

void cMPongView::VOnCreateDevice(IBaseApp * pGame, const HINSTANCE hInst, const HWND hWnd, 
								 int iClientWidth, int iClientHeight)
{
	cHumanView::VOnCreateDevice(pGame, hInst, hWnd, iClientWidth, iClientHeight);
	m_pGame = dynamic_cast<cGame *>(pGame);
}

// ***************************************************************
void cMPongView::VOnUpdate(const TICK tickCurrent, const float fElapsedTime)
{
	cHumanView::VOnUpdate(tickCurrent, fElapsedTime);
	if (m_P1PaddleHandler)
	{
		m_P1PaddleHandler->OnUpdate();
	}
	if (m_pGame)
	{
		if(m_pGame->IsSinglePlayer())
		{
			m_pGame->HandlePaddleAI(fElapsedTime);
		}
		else if (m_P2PaddleHandler)
		{
			m_P2PaddleHandler->OnUpdate();
		}
	}
}

// ***************************************************************
void cMPongView::VRenderPrivate()
{
	cHumanView::VRenderPrivate();
		
	if (m_bDisplayFPS && m_pGame)
	{
		AppMsg msg;
		m_pFont->SetText(cString(20, "%0.2f", m_pGame->GetFPS()));
		m_pFont->VOnRender(msg);
	}
}

// ***************************************************************
bool cMPongView::VOnMsgProc( const Graphics::AppMsg & msg )
{
	if(!cHumanView::VOnMsgProc(msg))
	{
		if(msg.m_uMsg == WM_KEYDOWN)
		{
			if (msg.m_wParam == VK_F2 && !IsKeyLocked(VK_F2) )
			{
				// lock the F2 key
				LockKey(VK_F2);
				m_bDisplayFPS = !m_bDisplayFPS;
			}
			if (msg.m_wParam == VK_ESCAPE  && !IsKeyLocked(VK_ESCAPE))
			{
				// lock the ESC key
				LockKey(VK_ESCAPE);
				PostQuitMessage(0);
			}
			if (m_P1PaddleHandler)
			{
				m_P1PaddleHandler->VOnKeyDown(msg);
			}
			if (m_P2PaddleHandler)
			{
				m_P2PaddleHandler->VOnKeyDown(msg);
			}
		}
		else if (msg.m_uMsg == WM_KEYUP)
		{
			if (msg.m_wParam == VK_F2)
			{
				UnlockKey(VK_F2);
			}
			if (msg.m_wParam == VK_ESCAPE)
			{
				UnlockKey(VK_ESCAPE);
			}
			if (m_P1PaddleHandler)
			{
				m_P1PaddleHandler->VOnKeyUp(msg);
			}
			if (m_P2PaddleHandler)
			{
				m_P2PaddleHandler->VOnKeyUp(msg);
			}
		}
	}
	return true;
}

// ***************************************************************
void cMPongView::OnSinglePlayerSelected( cGame * pGame)
{
	m_P1PaddleHandler = shared_ptr<P1PaddleHandler>(DEBUG_NEW P1PaddleHandler());
	function<void (bool)> callbackP1Paddle;
	callbackP1Paddle = bind(&cGame::MoveLeftPaddle, pGame, _1);
	m_P1PaddleHandler->RegisterCallBack(callbackP1Paddle);
}

// ***************************************************************
void cMPongView::OnMultiPlayerSelected( cGame * pGame )
{
	m_P1PaddleHandler = shared_ptr<P1PaddleHandler>(DEBUG_NEW P1PaddleHandler());
	function<void (bool)> callbackP1Paddle;
	callbackP1Paddle = bind(&cGame::MoveLeftPaddle, pGame, _1);
	m_P1PaddleHandler->RegisterCallBack(callbackP1Paddle);

	m_P2PaddleHandler = shared_ptr<P2PaddleHandler>(DEBUG_NEW P2PaddleHandler());
	function<void (bool)> callbackP2Paddle;
	callbackP2Paddle = bind(&cGame::MoveRightPaddle, pGame, _1);
	m_P2PaddleHandler->RegisterCallBack(callbackP2Paddle);
}
