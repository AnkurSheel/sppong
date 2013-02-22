// *****************************************************************************
//  MpongView   version:  1.0   Ankur Sheel  date: 2011/05/02
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "MpongView.h"
#include "Game/Game.h"
#include "Game/Elements/Score.h"
#include "Game/Elements/PongGameElement.h"
#include "P1PaddleHandler.h"
#include "P2PaddleHandler.h"
#include "Camera.hxx"
#include "MessageDispatchManager.hxx"

using namespace Utilities;
using namespace Graphics;
using namespace GameBase;
using namespace Base;

// *****************************************************************************
cMPongView::cMPongView()
: m_pGame(NULL)
{
}

// *****************************************************************************
cMPongView::~cMPongView()
{
}

void cMPongView::VOnCreateDevice(IBaseApp * pGame,
								 const HINSTANCE & hInst,
								 const HWND & hWnd)
{
	cHumanView::VOnCreateDevice(pGame, hInst, hWnd);
	m_pCamera->VSetPosition(cVector3(0.0f, 0.0f, -20.0f));
	m_pGame = dynamic_cast<cGame *>(pGame);
}

// *****************************************************************************
void cMPongView::VOnUpdate(const TICK tickCurrent, const float fElapsedTime)
{
	cHumanView::VOnUpdate(tickCurrent, fElapsedTime);
	if (m_P1PaddleHandler)
	{
		m_P1PaddleHandler->OnUpdate();
	}
	if (m_P2PaddleHandler)
	{
		m_P2PaddleHandler->OnUpdate();
	}
}

// *****************************************************************************
bool cMPongView::VOnMsgProc( const Base::AppMsg & msg )
{
	if(!cHumanView::VOnMsgProc(msg))
	{
		if(msg.m_uMsg == WM_KEYDOWN)
		{
			if (msg.m_wParam == VK_ESCAPE  && !IsKeyLocked(VK_ESCAPE))
			{
				// lock the ESC key
				LockKey(VK_ESCAPE);
				IMessageDispatchManager::GetInstance()->VDispatchMessage(0.0f, m_pGame->VGetID(),
					m_pGame->VGetID(), MSG_ESCAPE_PRESSED, NULL);
			}
			if (m_P1PaddleHandler)
			{
				m_P1PaddleHandler->VOnKeyDown(msg.m_wParam);
			}
			if (m_P2PaddleHandler)
			{
				m_P2PaddleHandler->VOnKeyDown(msg.m_wParam);
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
				m_P1PaddleHandler->VOnKeyUp(msg.m_wParam);
			}
			if (m_P2PaddleHandler)
			{
				m_P2PaddleHandler->VOnKeyUp(msg.m_wParam);
			}
		}
	}
	return true;
}

// *****************************************************************************
void cMPongView::OnSinglePlayerSelected( cGame * pGame)
{
	m_P1PaddleHandler = shared_ptr<P1PaddleHandler>(DEBUG_NEW P1PaddleHandler());
	function<void (bool)> callbackP1Paddle;
	callbackP1Paddle = bind(&cGame::MoveLeftPaddle, pGame, _1);
	m_P1PaddleHandler->RegisterCallBack(callbackP1Paddle);
}

// *****************************************************************************
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

// *******************************************************************************************
void cMPongView::VRenderPrivate()
{
	for (int i=0; i<m_pGame->PGE_TOTAL; i++)
	{
		if(m_pGame->VGetGameElements() && m_pGame->VGetGameElements()[i])
		{
			m_pGame->VGetGameElements()[i]->Render(m_pCamera);
		}
	}
	cHumanView::VRenderPrivate();
}
