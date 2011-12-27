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
#include "Structures.h"

using namespace MySound;
using namespace Graphics;
using namespace Base;
using namespace GameBase;
using namespace Utilities;
// ***************************************************************
// Constructor
// ***************************************************************
cGame::cGame()
: m_pScore(NULL)
, m_pStateMachine(NULL)
, m_pD3dDevice(NULL)
, m_bSinglePlayer(false)
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

// ***************************************************************
// Destructor
// ***************************************************************
cGame::~cGame()
{
	Cleanup();
}
// ***************************************************************

void cGame::OnUpdate()
{
	m_pGameTimer->Update();
	m_pStateMachine->Update();
	m_pSound->Update();
	m_pPongView->OnUpdate(this, m_pGameTimer->GetElapsedTime());

}
// ***************************************************************
// Display the Graphics
// ***************************************************************
void cGame::Render(TICK tickCurrent, float fElapsedTime)
{
	m_pPongView->OnRender(this, tickCurrent, fElapsedTime);
}
// ***************************************************************

// ***************************************************************
// Function called when the window is created
// ***************************************************************
HWND cGame::OnInit( const HINSTANCE hInstance, const int nCmdShow,const bool bFullScreen, const int iFullScreenWidth, const int iFullScreenHeight )
{
	HWND hwnd;
	cBaseApp::OnInit(hInstance, nCmdShow, bFullScreen, iFullScreenWidth, iFullScreenHeight, hwnd);

	m_pD3dDevice = IDXBase::GetInstance()->GetDevice();
	m_iDisplayHeight = iFullScreenHeight;
	m_iDisplayWidth = iFullScreenWidth;

	m_pSound = ISound::CreateSound();
	m_pSound->Init();
	m_pStateMachine = DEBUG_NEW cGameFlowStateMachine(this);
	m_pPongView = DEBUG_NEW cMPongView();

	m_pPongView->OnCreateDevice(hInstance, hwnd, m_iDisplayWidth, m_iDisplayHeight);

	m_pStateMachine->SetCurrentState(cStateTitleScreen::Instance());

	return hwnd;
}
// ***************************************************************

// ***************************************************************
// Process user input
// ***************************************************************
void cGame::ProcessInput( const long xDelta,
						 const long yDelta, 
						 const long zDelta, 
						 const bool* const pbPressedKeys, 
						 const bool* const pbMouseButtons, 
						 const float fElapsedTime )
{

	if (pbPressedKeys[DIK_S])
	{
		if (!(ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(&(m_pGameElements[PGE_PADDLE_LEFT]->GetBoundingRectangle()), 
																			 &(m_pGameElements[PGE_WALL_DOWN]->GetBoundingRectangle()))))
		{
			cPaddle * pPaddle = m_pGameElements[PGE_PADDLE_LEFT]->CastToPaddle();
			if(pPaddle)
			{
				pPaddle->MoveDown(fElapsedTime);
			}
		}
	}

	if (pbPressedKeys[DIK_W])
	{
		if (!(ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(&(m_pGameElements[PGE_PADDLE_LEFT]->GetBoundingRectangle()), 
																				&(m_pGameElements[PGE_WALL_UP]->GetBoundingRectangle()))))
		{
			cPaddle * pPaddle = m_pGameElements[PGE_PADDLE_LEFT]->CastToPaddle();
			if(pPaddle)
			{
				pPaddle->MoveUp(fElapsedTime);
			}
		}
	}

	if (pbPressedKeys[DIK_A])
	{
		if(m_pGameElements[PGE_PADDLE_LEFT]->GetPosition().x >= 0)
		{
			cPaddle * pPaddle = m_pGameElements[PGE_PADDLE_LEFT]->CastToPaddle();
			if(pPaddle)
			{
				pPaddle->MoveLeft(fElapsedTime);
			}
		}
	}

	if (pbPressedKeys[DIK_D])
	{
		if(m_pGameElements[PGE_PADDLE_LEFT]->GetPosition().x <= m_iDisplayWidth/2 - m_pGameElements[PGE_PADDLE_LEFT]->GetSprite()->GetScaledWidth())
		{
			cPaddle * pPaddle = m_pGameElements[PGE_PADDLE_LEFT]->CastToPaddle();
			if(pPaddle)
			{
				pPaddle->MoveRight(fElapsedTime);
			}
		}
	}

	if (pbPressedKeys[DIK_P])
	{
		//IMainWindow::GetInstance()->LockKey(DIK_P) ;
		m_pSound->ChangeMusicVolume(true, GS_MAIN_MENU_MUSIC);
	}
	if (pbPressedKeys[DIK_L])
	{
		//IMainWindow::GetInstance()->LockKey(DIK_L) ;
		m_pSound->ChangeMusicVolume(false, GS_MAIN_MENU_MUSIC);
	}

	// if Two Player mode handle the keys
	if (!m_bSinglePlayer)
	{
		if (pbPressedKeys[DIK_DOWN])
		{
			if (!(ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(&(m_pGameElements[PGE_PADDLE_RIGHT]->GetBoundingRectangle()), &(m_pGameElements[PGE_WALL_DOWN]->GetBoundingRectangle()))))
			{
				cPaddle * pPaddle = m_pGameElements[PGE_PADDLE_RIGHT]->CastToPaddle();
				if(pPaddle)
				{
					pPaddle->MoveDown(fElapsedTime);
				}
			}
		}

		if (pbPressedKeys[DIK_UP])
		{
			if (!(ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(&(m_pGameElements[PGE_PADDLE_RIGHT]->GetBoundingRectangle()), &(m_pGameElements[PGE_WALL_UP]->GetBoundingRectangle()))))
			{
				cPaddle * pPaddle = m_pGameElements[PGE_PADDLE_RIGHT]->CastToPaddle();
				if(pPaddle)
				{
					pPaddle->MoveUp(fElapsedTime);
				}
			}
		}

		if (pbPressedKeys[DIK_LEFT])
		{
			if(m_pGameElements[PGE_PADDLE_RIGHT]->GetPosition().x >= m_iDisplayWidth/2)
			{
				cPaddle * pPaddle = m_pGameElements[PGE_PADDLE_RIGHT]->CastToPaddle();
				if(pPaddle)
				{
					pPaddle->MoveLeft(fElapsedTime);
				}
			}
		}

		if (pbPressedKeys[DIK_RIGHT])
		{
			if (m_pGameElements[PGE_PADDLE_RIGHT]->GetPosition().x <= (m_iDisplayWidth - m_pGameElements[PGE_PADDLE_RIGHT]->GetSprite()->GetScaledWidth()))
			{
				cPaddle * pPaddle = m_pGameElements[PGE_PADDLE_RIGHT]->CastToPaddle();
				if(pPaddle)
				{
					pPaddle->MoveRight(fElapsedTime);
				}
			}
		}
	}
	else // single player mode
	{
		HandlePaddleAI(fElapsedTime);
	}
}
// ***************************************************************

// ***************************************************************
// Deletes the memory
// ***************************************************************
void cGame::Cleanup()
{
	m_pPongView->OnDestroyDevice();
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

	if(ICollisionChecker::TheCollisionChecker())
		ICollisionChecker::TheCollisionChecker()->Destroy();

	if (IMainWindow::GetInstance())
		IMainWindow::GetInstance()->Destroy();

	if(IResourceManager::TheResourceManager())
		IResourceManager::TheResourceManager()->Destroy();
}
// ***************************************************************

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

// ***************************************************************
// Checks for collisions
// ***************************************************************
void cGame::CheckForCollisions()
{
	// check for collisions between paddle and ball
	if (ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(&(m_pGameElements[PGE_BALL]->GetBoundingRectangle()), &(m_pGameElements[PGE_PADDLE_LEFT]->GetBoundingRectangle()))
		|| ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(&(m_pGameElements[PGE_BALL]->GetBoundingRectangle()), &(m_pGameElements[PGE_PADDLE_RIGHT]->GetBoundingRectangle())))
	{
		cBall * pBall = m_pGameElements[PGE_BALL]->CastToBall();
		if(pBall)
		{
			pBall->ChangeSpeedX();
		}
		m_pSound->PlaySound(GS_BALL_PADDLE_COLLISION);
	}

	// check for collision between ball and walls
	if (ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(&(m_pGameElements[PGE_BALL]->GetBoundingRectangle()), &(m_pGameElements[PGE_WALL_UP]->GetBoundingRectangle()))
		|| ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(&(m_pGameElements[PGE_BALL]->GetBoundingRectangle()), &(m_pGameElements[PGE_WALL_DOWN]->GetBoundingRectangle())))
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
		if (!(ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(&(m_pGameElements[PGE_PADDLE_RIGHT]->GetBoundingRectangle()), &(m_pGameElements[PGE_WALL_UP]->GetBoundingRectangle()))))
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
		if (!(ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(&(m_pGameElements[PGE_PADDLE_RIGHT]->GetBoundingRectangle()), &(m_pGameElements[PGE_WALL_DOWN]->GetBoundingRectangle()))))
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

cString cGame::GetGameTitle() const
{
	return "MPong";
}

float cGame::GetRunningTime()
{
	if(m_pGameTimer)
		return m_pGameTimer->GetRunningTime();

	return 0.f;
}
// ***************************************************************

TICK cGame::GetRunningTicks()
{
	if(m_pGameTimer)
		return m_pGameTimer->GetRunningTicks();

	return 0;
}
// ***************************************************************

// ***************************************************************
// the message loop
// ***************************************************************
void cGame::Run()
{
	MSG Msg ;

	m_pGameTimer = ITimer::CreateTimer();
	m_pGameTimer->Start();

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
			OnUpdate();
			Render(m_pGameTimer->GetRunningTicks(), m_pGameTimer->GetElapsedTime());
		}
	}
}
// ***************************************************************


// ***************************************************************
// Display the FPS
// ***************************************************************
float cGame::GetFPS()
{
	return m_pGameTimer->GetFPS();
}
// ***************************************************************

void cGame::OnMsgProc( const Graphics::AppMsg & msg )
{
	switch(msg.m_uMsg)
	{
	case WM_CHAR:
		switch (msg.m_wParam)
		{ 
		case VK_SPACE:
			IMainWindow::GetInstance()->ToggleFullScreen();
			Log_Write_L3(ILogger::LT_DEBUG, "Toggled FullScreen");
			break;
		}
	}
}
// ***************************************************************

HRESULT cGame::OnResetDevice()
{
	return(m_pPongView->OnResetDevice());
}
// ***************************************************************

void cGame::OnLostDevice()
{
	m_pPongView->OnLostDevice();
}
// ***************************************************************

IBaseApp * IGame::CreateGame()
{
	return DEBUG_NEW cGame();
}
// ***************************************************************