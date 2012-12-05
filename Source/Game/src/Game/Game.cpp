// ***************************************************************
//  Game   version:  1.0   Ankur Sheel  date: 04/30/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "Game.h"
#include "Sprite.hxx"
#include "Elements/Paddle.h"
#include "Elements/Ball.h"
//#include "CollisionChecker.hxx"
#include "Elements/Wall.h"
#include "Elements/Score.h"
#include "GameFlowStateMachine.h"
#include "GameFlowStates.h"
#include "Sound.hxx"
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

// ***************************************************************
// Constructor
// ***************************************************************
cGame::cGame(const cString strName)
: cBaseApp(strName)
, m_pScore(NULL)
, m_pStateMachine(NULL)
, m_bSinglePlayer(false)
, m_bMultiPlayer(false)
, m_pSound(NULL)
, m_ppGameElements(NULL)
{
}

// ***************************************************************
// Destructor
// ***************************************************************
cGame::~cGame()
{
	VCleanup();
}

// ***************************************************************
// Function called when the window is created
// ***************************************************************
void cGame::VOnInitialization(const HINSTANCE & hInstance, const int nCmdShow,
							  const cString & strOptionsFileName)
{
	cBaseApp::VOnInitialization(hInstance, nCmdShow, strOptionsFileName);

	m_iDisplayHeight = m_pHumanView->m_pAppWindowControl->VGetHeight();
	m_iDisplayWidth = m_pHumanView->m_pAppWindowControl->VGetWidth();

	m_pSound = ISound::CreateSound();
	m_pSound->Init();
	m_pStateMachine = DEBUG_NEW cGameFlowStateMachine(this);

	IEntityManager::GetInstance()->VRegisterEntity(this);
	m_pStateMachine->SetCurrentState(cStateTitleScreen::Instance());
}

void cGame::VCreateHumanView()
{
	m_pHumanView = DEBUG_NEW cMPongView();
}

// ***************************************************************
cString cGame::VGetGameTitle() const
{
	return VGetName();
}

// ***************************************************************
void cGame::VOnUpdate()
{
	cBaseApp::VOnUpdate();
	m_pStateMachine->Update();
	m_pSound->Update();
	IMessageDispatchManager::GetInstance()->VOnUpdate();
}

// ***************************************************************
// Restarts the game
// ***************************************************************
void cGame::Restart()
{
	Sleep(100);
	//m_pGameElements[PGE_PADDLE_LEFT]->OnRestart(cVector3(10.0f, (float)m_iDisplayHeight/2, 0.0f));
	//m_pGameElements[PGE_PADDLE_RIGHT]->OnRestart(cVector3((float)(m_iDisplayWidth), (float)m_iDisplayHeight/2, 0.0f));
	//m_pGameElements[PGE_BALL]->OnRestart(cVector3((float)m_iDisplayWidth/2, (float)m_iDisplayHeight/2, 0.0f));
}

// ***************************************************************
// Checks if either player has won
// ***************************************************************
void cGame::CheckForWin()
{
	//cVector3 vBallPosition = m_pGameElements[PGE_BALL]->GetPosition();

	//if(vBallPosition.m_dX <= 0)
	//{
	//	m_pSound->PlaySound(GS_WIN);
	//	m_pScore[1].IncrementScore();
	//	Restart();
	//}
	//if (vBallPosition.m_dX >= (m_iDisplayWidth - m_pGameElements[PGE_BALL]->GetSprite()->GetScaledWidth()))
	//{
	//	m_pSound->PlaySound(GS_WIN);
	//	m_pScore[0].IncrementScore();
	//	Restart();
	//}
}

// ***************************************************************
// Checks for collisions
// ***************************************************************
void cGame::CheckForCollisions()
{
	// check for collisions between paddle and ball
	//if (ICollisionChecker::GetInstance()->CheckFor2DCollisions(&(m_pGameElements[PGE_BALL]->GetBoundingRectangle()), &(m_pGameElements[PGE_PADDLE_LEFT]->GetBoundingRectangle()))
	//	|| ICollisionChecker::GetInstance()->CheckFor2DCollisions(&(m_pGameElements[PGE_BALL]->GetBoundingRectangle()), &(m_pGameElements[PGE_PADDLE_RIGHT]->GetBoundingRectangle())))
	//{
	//	cBall * pBall = m_pGameElements[PGE_BALL]->CastToBall();
	//	if(pBall)
	//	{
	//		pBall->ChangeSpeedX();
	//	}
	//	m_pSound->PlaySound(GS_BALL_PADDLE_COLLISION);
	//}

	//// check for collision between ball and walls
	//if (ICollisionChecker::GetInstance()->CheckFor2DCollisions(&(m_pGameElements[PGE_BALL]->GetBoundingRectangle()), &(m_pGameElements[PGE_WALL_UP]->GetBoundingRectangle()))
	//	|| ICollisionChecker::GetInstance()->CheckFor2DCollisions(&(m_pGameElements[PGE_BALL]->GetBoundingRectangle()), &(m_pGameElements[PGE_WALL_DOWN]->GetBoundingRectangle())))
	//{
	//	cBall * pBall = m_pGameElements[PGE_BALL]->CastToBall();
	//	if(pBall)
	//	{
	//		pBall->ChangeSpeedY();
	//	}
	//	m_pSound->PlaySound(GS_BALL_WALL_COLLISION);
	//}
}

// ***************************************************************
// Deletes the memory
// ***************************************************************
void cGame::VCleanup()
{
	if(m_ppGameElements)
	{
		SAFE_DELETE_ARRAY(*m_ppGameElements);
		SAFE_DELETE(m_ppGameElements);
	}

	SAFE_DELETE_ARRAY(m_pScore);
	SAFE_DELETE(m_pStateMachine);

	SAFE_DELETE(m_pSound);

	//ICollisionChecker::Destroy();
	cBaseApp::VCleanup();
}

// ***************************************************************
// the AI for the paddle
// ***************************************************************
void cGame::HandlePaddleAI( const float fElapsedTime )
{
	//// if the ball is in the players half, there is no need to do anything
	//if (m_pGameElements[PGE_BALL]->GetPosition().m_dX < m_iDisplayWidth/2)
	//{
	//	return;
	//}
	//float	fCentreOfPaddle = m_pGameElements[PGE_PADDLE_RIGHT]->GetPosition().m_dY + m_pGameElements[PGE_PADDLE_RIGHT]->GetSprite()->GetScaledHeight()/2;
	//float	fCentreOfBall = m_pGameElements[PGE_BALL]->GetPosition().m_dY + m_pGameElements[PGE_BALL]->GetSprite()->GetScaledHeight()/2;

	//if (fCentreOfPaddle - fCentreOfBall > 10)
	//{
	//	if (!(ICollisionChecker::GetInstance()->CheckFor2DCollisions(&(m_pGameElements[PGE_PADDLE_RIGHT]->GetBoundingRectangle()), &(m_pGameElements[PGE_WALL_UP]->GetBoundingRectangle()))))
	//	{
	//		cPaddle * pPaddle = m_pGameElements[PGE_PADDLE_RIGHT]->CastToPaddle();
	//		if(pPaddle)
	//		{
	//			pPaddle->MoveUp(fElapsedTime);
	//		}
	//		return;
	//	}
	//}

	//if (fCentreOfBall - fCentreOfPaddle > 10)
	//{
	//	if (!(ICollisionChecker::GetInstance()->CheckFor2DCollisions(&(m_pGameElements[PGE_PADDLE_RIGHT]->GetBoundingRectangle()), &(m_pGameElements[PGE_WALL_DOWN]->GetBoundingRectangle()))))
	//	{
	//		cPaddle * pPaddle = m_pGameElements[PGE_PADDLE_RIGHT]->CastToPaddle();
	//		if(pPaddle)
	//		{
	//			pPaddle->MoveDown(fElapsedTime);
	//		}
	//		return;
	//	}
	//}
}

void cGame::SinglePlayerButtonPressed(bool bPressed)
{
	if(!bPressed)
	{
		m_bSinglePlayer = true;
		cMPongView * pView = dynamic_cast<cMPongView *>(m_pHumanView);
		if(pView)
			pView->OnSinglePlayerSelected(this);
	}
}

void cGame::MultiPlayerButtonPressed(bool bPressed)
{
	if(!bPressed)
	{
		m_bMultiPlayer = true;
		cMPongView * pView = dynamic_cast<cMPongView *>(m_pHumanView);
		if(pView)
			pView->OnMultiPlayerSelected(this);
	}
}

void cGame::QuitButtonPressed( bool bPressed )
{
	if(!bPressed)
	{
		PostQuitMessage(0);
	}
}

void cGame::MoveLeftPaddle(bool bMoveDown)
{
	if (bMoveDown)
	{
		//if (!(ICollisionChecker::GetInstance()->CheckFor2DCollisions(&(m_pGameElements[PGE_PADDLE_LEFT]->GetBoundingRectangle()), 
		//	&(m_pGameElements[PGE_WALL_DOWN]->GetBoundingRectangle()))))
		{
			cPaddle * pPaddle = m_ppGameElements[PGE_PADDLE_LEFT]->CastToPaddle();
			if(pPaddle)
			{
				pPaddle->MoveDown(m_pGameTimer->VGetDeltaTime());
			}
		}
	}
	else
	{
		//if (!(ICollisionChecker::GetInstance()->CheckFor2DCollisions(&(m_pGameElements[PGE_PADDLE_LEFT]->GetBoundingRectangle()), 
		//	&(m_pGameElements[PGE_WALL_UP]->GetBoundingRectangle()))))
		{
			cPaddle * pPaddle = m_ppGameElements[PGE_PADDLE_LEFT]->CastToPaddle();
			if(pPaddle)
			{
				pPaddle->MoveUp(m_pGameTimer->VGetDeltaTime());
			}
		}

	}
}

// ***************************************************************
void cGame::MoveRightPaddle( bool bMoveDown )
{
	if (bMoveDown)
	{
		//if (!(ICollisionChecker::GetInstance()->CheckFor2DCollisions(&(m_pGameElements[PGE_PADDLE_RIGHT]->GetBoundingRectangle()), &(m_pGameElements[PGE_WALL_DOWN]->GetBoundingRectangle()))))
		{
			//cPaddle * pPaddle = m_pGameElements[PGE_PADDLE_RIGHT]->CastToPaddle();
			//if(pPaddle)
			//{
			//	pPaddle->MoveDown(m_pGameTimer->VGetDeltaTime());
			//}
		}
	}
	else
	{
		//if (!(ICollisionChecker::GetInstance()->CheckFor2DCollisions(&(m_pGameElements[PGE_PADDLE_RIGHT]->GetBoundingRectangle()), &(m_pGameElements[PGE_WALL_UP]->GetBoundingRectangle()))))
		{
			//cPaddle * pPaddle = m_pGameElements[PGE_PADDLE_RIGHT]->CastToPaddle();
			//if(pPaddle)
			//{
			//	pPaddle->MoveUp(m_pGameTimer->VGetDeltaTime());
			//}
		}
	}
}

// ***************************************************************
bool cGame::IsSinglePlayer()
{
	return m_bSinglePlayer;
}

// ***************************************************************
bool cGame::VOnHandleMessage(const AI::Telegram & telegram)
{
	return m_pStateMachine->HandleMessage(telegram);
}
// *****************************************************************************
cPongGameElement ** const cGame::GetGameElements() const
{
	return m_ppGameElements; 
}

// ***************************************************************
IBaseApp * IGame::CreateGame(const cString strName)
{
	return DEBUG_NEW cGame(strName);
}