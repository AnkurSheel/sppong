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
#include "CollisionChecker.hxx"
#include "Elements/Wall.h"
#include "Elements/Score.h"
#include "GameFlowStateMachine.h"
#include "GameFlowStates.h"
#include "Sound.hxx"
#include "MPongView.h"
#include "DXBase.hxx"
#include "Timer.hxx"
#include "ProcessManager.hxx"
#include "MainWindow.hxx"
#include "ResourceManager.hxx"
#include "EntityManager.hxx"
#include "MessageDispatchManager.hxx"

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
, m_pD3dDevice(NULL)
, m_bSinglePlayer(false)
, m_bMultiPlayer(false)
, m_pSound(NULL)
, m_pPongView(NULL)
, m_pGameTimer(NULL)
{
	for(int i=0;i<PGE_TOTAL;i++)
	{
		m_pGameElements[i] = NULL;
	}
}

// ***************************************************************
// Destructor
// ***************************************************************
cGame::~cGame()
{
	Cleanup();
}

// ***************************************************************
// Function called when the window is created
// ***************************************************************
void cGame::VOnInitialization( const HINSTANCE hInstance, const int nCmdShow,
				   const bool bFullScreen, const int iFullScreenWidth,
				   const int iFullScreenHeight, HWND & outHwnd )
{
	cBaseApp::VOnInitialization(hInstance, nCmdShow, bFullScreen, iFullScreenWidth, iFullScreenHeight, outHwnd);

	m_pD3dDevice = IDXBase::GetInstance()->VGetDevice();
	m_iDisplayHeight = iFullScreenHeight;
	m_iDisplayWidth = iFullScreenWidth;

	m_pSound = ISound::CreateSound();
	m_pSound->Init();
	m_pStateMachine = DEBUG_NEW cGameFlowStateMachine(this);
	m_pPongView = DEBUG_NEW cMPongView();

	m_pPongView->VOnCreateDevice(hInstance, outHwnd, m_iDisplayWidth, m_iDisplayHeight);
	IEntityManager::GetInstance()->VRegisterEntity(this);
	m_pStateMachine->SetCurrentState(cStateTitleScreen::Instance());
}

// ***************************************************************
// the message loop
// ***************************************************************
void cGame::VRun()
{
	MSG Msg ;

	m_pGameTimer = ITimer::CreateTimer();
	m_pGameTimer->VStartTimer();

	PeekMessage(&Msg, NULL, 0, 0, PM_NOREMOVE) ;
	// run till completed
	while (Msg.message!=WM_QUIT)
	{
		// is there a message to process?
		if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
		{
			// dispatch the message
			TranslateMessage(&Msg) ;
			DispatchMessage(&Msg) ;
		}
		else
		{
			//No message to process?
			// Then do your game stuff here
			VOnUpdate();
			Render(m_pGameTimer->VGetRunningTicks(), m_pGameTimer->VGetDeltaTime());
		}
	}
}

// ***************************************************************
void cGame::VOnLostDevice()
{
	m_pPongView->VOnLostDevice();
}

// ***************************************************************
HRESULT cGame::VOnResetDevice()
{
	return(m_pPongView->VOnResetDevice());
}

// ***************************************************************
bool cGame::VOnMsgProc( const Graphics::AppMsg & msg )
{
	return m_pPongView->VOnMsgProc(msg);
}

// ***************************************************************
cString cGame::VGetGameTitle() const
{
	return VGetName();
}

// ***************************************************************
void cGame::VOnUpdate()
{
	m_pGameTimer->VOnUpdate();
	m_pStateMachine->Update();
	m_pSound->Update();
	IMessageDispatchManager::GetInstance()->VOnUpdate();
	m_pPongView->VOnUpdate(this, m_pGameTimer->VGetDeltaTime());

}

// ***************************************************************
// Display the Graphics
// ***************************************************************
void cGame::Render(TICK tickCurrent, float fElapsedTime)
{
	m_pPongView->VOnRender(this, tickCurrent, fElapsedTime);
}

// ***************************************************************
// Restarts the game
// ***************************************************************
void cGame::Restart()
{
	Sleep(100);
	m_pGameElements[PGE_PADDLE_LEFT]->OnRestart(D3DXVECTOR3(10.0f, (float)m_iDisplayHeight/2, 0.0f));
	m_pGameElements[PGE_PADDLE_RIGHT]->OnRestart(D3DXVECTOR3((float)(m_iDisplayWidth), (float)m_iDisplayHeight/2, 0.0f));
	m_pGameElements[PGE_BALL]->OnRestart(D3DXVECTOR3((float)m_iDisplayWidth/2, (float)m_iDisplayHeight/2, 0.0f));
}

// ***************************************************************
// Checks if either player has won
// ***************************************************************
void cGame::CheckForWin()
{
	D3DXVECTOR3 vBallPosition = m_pGameElements[PGE_BALL]->GetPosition();

	if(vBallPosition.x <= 0)
	{
		m_pSound->PlaySound(GS_WIN);
		m_pScore[1].IncrementScore();
		Restart();
	}
	if (vBallPosition.x >= (m_iDisplayWidth - m_pGameElements[PGE_BALL]->GetSprite()->GetScaledWidth()))
	{
		m_pSound->PlaySound(GS_WIN);
		m_pScore[0].IncrementScore();
		Restart();
	}
}

// ***************************************************************
// Checks for collisions
// ***************************************************************
void cGame::CheckForCollisions()
{
	// check for collisions between paddle and ball
	if (ICollisionChecker::GetInstance()->CheckFor2DCollisions(&(m_pGameElements[PGE_BALL]->GetBoundingRectangle()), &(m_pGameElements[PGE_PADDLE_LEFT]->GetBoundingRectangle()))
		|| ICollisionChecker::GetInstance()->CheckFor2DCollisions(&(m_pGameElements[PGE_BALL]->GetBoundingRectangle()), &(m_pGameElements[PGE_PADDLE_RIGHT]->GetBoundingRectangle())))
	{
		cBall * pBall = m_pGameElements[PGE_BALL]->CastToBall();
		if(pBall)
		{
			pBall->ChangeSpeedX();
		}
		m_pSound->PlaySound(GS_BALL_PADDLE_COLLISION);
	}

	// check for collision between ball and walls
	if (ICollisionChecker::GetInstance()->CheckFor2DCollisions(&(m_pGameElements[PGE_BALL]->GetBoundingRectangle()), &(m_pGameElements[PGE_WALL_UP]->GetBoundingRectangle()))
		|| ICollisionChecker::GetInstance()->CheckFor2DCollisions(&(m_pGameElements[PGE_BALL]->GetBoundingRectangle()), &(m_pGameElements[PGE_WALL_DOWN]->GetBoundingRectangle())))
	{
		cBall * pBall = m_pGameElements[PGE_BALL]->CastToBall();
		if(pBall)
		{
			pBall->ChangeSpeedY();
		}
		m_pSound->PlaySound(GS_BALL_WALL_COLLISION);
	}
}

// ***************************************************************
// Deletes the memory
// ***************************************************************
void cGame::Cleanup()
{
	m_pPongView->VOnDestroyDevice();
	SAFE_DELETE(m_pPongView);

	for(int i=0;i<PGE_TOTAL;i++)
	{
		if (m_pGameElements[i])
		{
			m_pGameElements[i]->Cleanup();
			SAFE_DELETE(m_pGameElements[i]);
		}
	}

	SAFE_DELETE_ARRAY(m_pScore);
	SAFE_DELETE(m_pStateMachine);

	SAFE_DELETE(m_pSound);

	SAFE_DELETE(m_pGameTimer);

	ICollisionChecker::Destroy();
	IMainWindow::Destroy();

	if(IResourceManager::GetInstance())
		IResourceManager::Destroy();
}

// ***************************************************************
float cGame::GetRunningTime()
{
	if(m_pGameTimer)
		return m_pGameTimer->VGetRunningTime();

	return 0.f;
}

// ***************************************************************
TICK cGame::GetRunningTicks()
{
	if(m_pGameTimer)
		return m_pGameTimer->VGetRunningTicks();

	return 0;
}

// ***************************************************************
// Display the FPS
// ***************************************************************
float cGame::GetFPS()
{
	return m_pGameTimer->VGetFPS();
}

// ***************************************************************
// the AI for the paddle
// ***************************************************************
void cGame::HandlePaddleAI( const float fElapsedTime )
{
	// if the ball is in the players half, there is no need to do anything
	if (m_pGameElements[PGE_BALL]->GetPosition().x < m_iDisplayWidth/2)
	{
		return;
	}
	float	fCentreOfPaddle = m_pGameElements[PGE_PADDLE_RIGHT]->GetPosition().y + m_pGameElements[PGE_PADDLE_RIGHT]->GetSprite()->GetScaledHeight()/2;
	float	fCentreOfBall = m_pGameElements[PGE_BALL]->GetPosition().y + m_pGameElements[PGE_BALL]->GetSprite()->GetScaledHeight()/2;

	if (fCentreOfPaddle - fCentreOfBall > 10)
	{
		if (!(ICollisionChecker::GetInstance()->CheckFor2DCollisions(&(m_pGameElements[PGE_PADDLE_RIGHT]->GetBoundingRectangle()), &(m_pGameElements[PGE_WALL_UP]->GetBoundingRectangle()))))
		{
			cPaddle * pPaddle = m_pGameElements[PGE_PADDLE_RIGHT]->CastToPaddle();
			if(pPaddle)
			{
				pPaddle->MoveUp(fElapsedTime);
			}
			return;
		}
	}

	if (fCentreOfBall - fCentreOfPaddle > 10)
	{
		if (!(ICollisionChecker::GetInstance()->CheckFor2DCollisions(&(m_pGameElements[PGE_PADDLE_RIGHT]->GetBoundingRectangle()), &(m_pGameElements[PGE_WALL_DOWN]->GetBoundingRectangle()))))
		{
			cPaddle * pPaddle = m_pGameElements[PGE_PADDLE_RIGHT]->CastToPaddle();
			if(pPaddle)
			{
				pPaddle->MoveDown(fElapsedTime);
			}
			return;
		}
	}
}

void cGame::SinglePlayerButtonPressed(bool bPressed)
{
	if(!bPressed)
	{
		m_bSinglePlayer = true;
		m_pPongView->OnSinglePlayerSelected(this);
	}
}

void cGame::MultiPlayerButtonPressed(bool bPressed)
{
	if(!bPressed)
	{
		m_bMultiPlayer = true;
		m_pPongView->OnMultiPlayerSelected(this);
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
		if (!(ICollisionChecker::GetInstance()->CheckFor2DCollisions(&(m_pGameElements[PGE_PADDLE_LEFT]->GetBoundingRectangle()), 
			&(m_pGameElements[PGE_WALL_DOWN]->GetBoundingRectangle()))))
		{
			cPaddle * pPaddle = m_pGameElements[PGE_PADDLE_LEFT]->CastToPaddle();
			if(pPaddle)
			{
				pPaddle->MoveDown(m_pGameTimer->VGetDeltaTime());
			}
		}
	}
	else
	{
		if (!(ICollisionChecker::GetInstance()->CheckFor2DCollisions(&(m_pGameElements[PGE_PADDLE_LEFT]->GetBoundingRectangle()), 
			&(m_pGameElements[PGE_WALL_UP]->GetBoundingRectangle()))))
		{
			cPaddle * pPaddle = m_pGameElements[PGE_PADDLE_LEFT]->CastToPaddle();
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
		if (!(ICollisionChecker::GetInstance()->CheckFor2DCollisions(&(m_pGameElements[PGE_PADDLE_RIGHT]->GetBoundingRectangle()), &(m_pGameElements[PGE_WALL_DOWN]->GetBoundingRectangle()))))
		{
			cPaddle * pPaddle = m_pGameElements[PGE_PADDLE_RIGHT]->CastToPaddle();
			if(pPaddle)
			{
				pPaddle->MoveDown(m_pGameTimer->VGetDeltaTime());
			}
		}
	}
	else
	{
		if (!(ICollisionChecker::GetInstance()->CheckFor2DCollisions(&(m_pGameElements[PGE_PADDLE_RIGHT]->GetBoundingRectangle()), &(m_pGameElements[PGE_WALL_UP]->GetBoundingRectangle()))))
		{
			cPaddle * pPaddle = m_pGameElements[PGE_PADDLE_RIGHT]->CastToPaddle();
			if(pPaddle)
			{
				pPaddle->MoveUp(m_pGameTimer->VGetDeltaTime());
			}
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

// ***************************************************************
IBaseApp * IGame::CreateGame(const cString strName)
{
	return DEBUG_NEW cGame(strName);
}