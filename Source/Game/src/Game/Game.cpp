// *****************************************************************************
//  Game   version:  1.0   Ankur Sheel  date: 04/30/2008
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "Game.h"
#include "Sprite.hxx"
#include "Elements/Paddle.h"
#include "Elements/Ball.h"
#include "Elements/Wall.h"
#include "Elements/Score.h"
#include "GameFlowStateMachine.h"
#include "GameFlowStates.h"
#include "MPongView.h"
#include "Timer.hxx"
#include "ProcessManager.hxx"
#include "MainWindow.hxx"
#include "ResourceManager.hxx"
#include "EntityManager.hxx"
#include "MessageDispatchManager.hxx"
#include "BaseControl.hxx"

using namespace MySound;
using namespace Graphics;
using namespace Base;
using namespace GameBase;
using namespace Utilities;

// *****************************************************************************
cGame::cGame(const cString strName)
: cBaseApp(strName)
, m_pScore(NULL)
, m_pStateMachine(NULL)
, m_bSinglePlayer(false)
, m_bMultiPlayer(false)
//, m_pSound(NULL)
, m_ppGameElements(NULL)
{
	// making sure our memory leak checker is working
#if _DEBUG
	int * p = DEBUG_NEW int();
#endif
}

// *****************************************************************************
cGame::~cGame()
{
	VCleanup();
}

// *****************************************************************************
void cGame::VOnInitialization(const HINSTANCE & hInstance, const int nCmdShow,
							  const cString & strOptionsFile)
{
	cBaseApp::VOnInitialization(hInstance, nCmdShow, strOptionsFile);

	m_iDisplayHeight = static_cast<int>(m_pHumanView->m_pAppWindowControl->VGetHeight());
	m_iDisplayWidth = static_cast<int>(m_pHumanView->m_pAppWindowControl->VGetWidth());

	m_pStateMachine = DEBUG_NEW cGameFlowStateMachine(this);

	IEntityManager::GetInstance()->VRegisterEntity(this);
	m_pStateMachine->SetCurrentState(cStateTitleScreen::Instance());
}

void cGame::VCreateHumanView()
{
	m_pHumanView = DEBUG_NEW cMPongView();
}

// *****************************************************************************
cString cGame::VGetGameTitle() const
{
	return VGetName();
}

// *****************************************************************************
void cGame::VOnUpdate()
{
	cBaseApp::VOnUpdate();
	m_pStateMachine->Update();
	//m_pSound->Update();
	IMessageDispatchManager::GetInstance()->VOnUpdate();
}

// *****************************************************************************
void cGame::Restart()
{
	Sleep(100);
	m_ppGameElements[PGE_PADDLE_LEFT]->OnRestart();
	m_ppGameElements[PGE_PADDLE_RIGHT]->OnRestart();
	m_ppGameElements[PGE_BALL]->OnRestart();
}

// *****************************************************************************
void cGame::VRoundOver(const bool bPlayer1Won)
{
	m_pHumanView->PlaySFX("SFX\\win.wav");
	if (bPlayer1Won)
	{
		m_pScore[1].IncrementScore();
		Restart();
	}
	else
	{
		m_pScore[0].IncrementScore();
		Restart();
	}
}

// *****************************************************************************
void cGame::VCleanup()
{
	if(m_ppGameElements)
	{
		for (int i=0; i<PGE_TOTAL; i++)
		{
			SAFE_DELETE(m_ppGameElements[i]);
		}
		SAFE_DELETE_ARRAY(m_ppGameElements);
	}

	SAFE_DELETE_ARRAY(m_pScore);
	SAFE_DELETE(m_pStateMachine);

	//SAFE_DELETE(m_pSound);

	cBaseApp::VCleanup();
}

// *****************************************************************************
void cGame::HandlePaddleAI( const float fElapsedTime )
{
	cVector3 vBallPos = m_ppGameElements[PGE_BALL]->GetPosition();
	// if the ball is in the players half, there is no need to do anything
	if (vBallPos.x < 0)
	{
		return;
	}
	cVector3 vPaddlePos = m_ppGameElements[PGE_PADDLE_RIGHT]->GetPosition();

	if (vPaddlePos.y - vBallPos.y < 1)
	{
		cPaddle * pPaddle = m_ppGameElements[PGE_PADDLE_RIGHT]->CastToPaddle();
		if(pPaddle)
		{
			pPaddle->MoveUp(fElapsedTime);
		}
		return;
	}
	else if (vBallPos.y - vPaddlePos.y < 1)
	{
		cPaddle * pPaddle = m_ppGameElements[PGE_PADDLE_RIGHT]->CastToPaddle();
		if(pPaddle)
		{
			pPaddle->MoveDown(fElapsedTime);
		}
		return;
	}
}

void cGame::MoveLeftPaddle(bool bMoveDown)
{
	cPaddle * pPaddle = m_ppGameElements[PGE_PADDLE_LEFT]->CastToPaddle();
	if(pPaddle)
	{
		if (bMoveDown)
		{
			pPaddle->MoveDown(m_pGameTimer->VGetDeltaTime());
		}
		else
		{
			pPaddle->MoveUp(m_pGameTimer->VGetDeltaTime());
		}
	}
}

// *****************************************************************************
void cGame::MoveRightPaddle( bool bMoveDown )
{
	cPaddle * pPaddle = m_ppGameElements[PGE_PADDLE_RIGHT]->CastToPaddle();
	if(pPaddle)
	{
		if (bMoveDown)
		{
			pPaddle->MoveDown(m_pGameTimer->VGetDeltaTime());
		}
		else
		{
			pPaddle->MoveUp(m_pGameTimer->VGetDeltaTime());
		}
	}
}

// *****************************************************************************
bool cGame::IsSinglePlayer()
{
	return m_bSinglePlayer;
}

// *****************************************************************************
bool cGame::VOnHandleMessage(const AI::Telegram & telegram)
{
	return m_pStateMachine->HandleMessage(telegram);
}

// *****************************************************************************
cPongGameElement ** const cGame::VGetGameElements() const
{
	return m_ppGameElements; 
}

// *****************************************************************************
cVector3 cGame::VGetScreenTopLeftPos() const
{
	return m_vScreenTopLeftPos;
}

// *****************************************************************************
cVector3 cGame::VGetScreenBottomRightPos() const
{
	return m_vScreenBottomRightPos;
}

// *****************************************************************************
IBaseApp * IGame::CreateGame(const cString strName)
{
	return DEBUG_NEW cGame(strName);
}