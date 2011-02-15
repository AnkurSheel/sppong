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
#include "2D/Sprite.hxx"
#include "Elements/Paddle.h"
#include "Elements/Ball.h"
#include "CollisionChecker.hxx"
#include "Elements/Wall.h"
#include "Elements/Score.h"
#include "Essentials/MainWindow.hxx"
#include "GameFlowStateMachine.h"
#include "GameFlowStates.h"
#include "Sound.hxx"
#include "Input/MouseZone.hxx"

using namespace MySound;
using namespace Graphics;
// ***************************************************************
// Constructor
// ***************************************************************
cGame::cGame()
: m_pTableSprite(NULL)
, m_pTitleScreenSprite(NULL)
, m_pCursorSprite(NULL)
, m_pScore(NULL)
, m_bDisplayFPS(false)
, m_pStateMachine(NULL)
, m_pD3dDevice(NULL)
, m_pMouseZones(NULL)
, m_pSinglePlayerSprite(NULL)
, m_pTwoPlayerSprite(NULL)
, m_pQuitSprite(NULL)
, m_bSinglePlayer(false)
, m_pSound(NULL)
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

// ***************************************************************
// Display the Graphics
// ***************************************************************
void cGame::Render()
{
	m_pStateMachine->Update();
	m_pSound->Update();
	if (m_bDisplayFPS)
	{
		IMainWindow::TheWindow()->DisplayFPS();
	}
}
// ***************************************************************

// ***************************************************************
// Initialize the resources that are volatile
// ***************************************************************
void cGame::OnResetDevice()
{
	m_pStateMachine->OnResetDevice(this);
}
// ***************************************************************

// ***************************************************************
// Free the resources that are volatile
// ***************************************************************
void cGame::OnLostDevice()
{
	m_pStateMachine->OnLostDevice(this);
}
// ***************************************************************

// ***************************************************************
// Function called when the window is created
// ***************************************************************
void cGame::OnInit( LPDIRECT3DDEVICE9 const pDevice, 
				   const UINT iDisplayHeight, 
				   const UINT iDisplayWidth )
{
	m_pD3dDevice = pDevice;
	m_iDisplayHeight = iDisplayHeight;
	m_iDisplayWidth = iDisplayWidth;


	m_pMouseZones = IMouseZone::CreateMouseZone();

	m_pSound = ISound::CreateSound();
	m_pSound->Init();
	m_pStateMachine = DEBUG_NEW cGameFlowStateMachine(this);
	m_pStateMachine->SetCurrentState(cStateTitleScreen::Instance());
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

	if (pbPressedKeys[DIK_F2])
	{
		// lock the F2 key
		IMainWindow::TheWindow()->LockKey(DIK_F2) ;

		m_bDisplayFPS = !m_bDisplayFPS;
	}

	if (pbPressedKeys[DIK_ESCAPE])
	{
		// lock the ESC key
		IMainWindow::TheWindow()->LockKey(DIK_ESCAPE) ;

		// if the current state is the title screen and the user presses ESC
		// go the game screen
		if (m_pStateMachine->GetCurrentState() == cStateTitleScreen::Instance())
		{
			m_pStateMachine->ChangeState(cStateMenuScreen::Instance());
		}
		else
		{
			// if the current state is the game screen and the user presses ESC, QUIT
			PostQuitMessage(0);
		}
	}
	if (pbPressedKeys[DIK_S])
	{
		if (!(ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pGameElements[PGE_PADDLE_LEFT]->GetBoundingRectangle(), m_pGameElements[PGE_WALL_DOWN]->GetBoundingRectangle())))
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
		if (!(ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pGameElements[PGE_PADDLE_LEFT]->GetBoundingRectangle(), m_pGameElements[PGE_WALL_UP]->GetBoundingRectangle())))
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
		IMainWindow::TheWindow()->LockKey(DIK_P) ;
		m_pSound->ChangeMusicVolume(true, GS_MAIN_MENU_MUSIC);
	}
	if (pbPressedKeys[DIK_L])
	{
		IMainWindow::TheWindow()->LockKey(DIK_L) ;
		m_pSound->ChangeMusicVolume(false, GS_MAIN_MENU_MUSIC);
	}

	// if Two Player mode handle the keys
	if (!m_bSinglePlayer)
	{
		if (pbPressedKeys[DIK_DOWN])
		{
			if (!(ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pGameElements[PGE_PADDLE_RIGHT]->GetBoundingRectangle(), m_pGameElements[PGE_WALL_DOWN]->GetBoundingRectangle())))
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
			if (!(ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pGameElements[PGE_PADDLE_RIGHT]->GetBoundingRectangle(), m_pGameElements[PGE_WALL_UP]->GetBoundingRectangle())))
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

	char szZoneName[64];
	if (m_pMouseZones->CheckZones(IMainWindow::TheWindow()->GetAbsXMousePos(), IMainWindow::TheWindow()->GetAbsYMousePos(), pbMouseButtons, szZoneName))
	{
		if(m_pStateMachine->GetCurrentState() == cStateTitleScreen::Instance())
		{
			if (strcmp(szZoneName, "Title Screen") == 0)
			{
				m_pStateMachine->ChangeState(cStateMenuScreen::Instance());
			}
		}

		if (m_pStateMachine->GetCurrentState() == cStateMenuScreen::Instance())
		{
			if (strcmp(szZoneName, "Single Player") == 0)
			{
				m_bSinglePlayer = true;
				m_pStateMachine->ChangeState(cStatePlayGame::Instance());
			}

			if (strcmp(szZoneName, "Two Player") == 0)
			{
				m_bSinglePlayer = false;
				m_pStateMachine->ChangeState(cStatePlayGame::Instance());
			}
			if (strcmp(szZoneName, "Quit") == 0)
			{
				PostQuitMessage(0);
			}
		}
	}
}
// ***************************************************************

// ***************************************************************
// Deletes the memory
// ***************************************************************
void cGame::Cleanup()
{
	for(int i=0;i<PGE_TOTAL;i++)
	{
		SAFE_DELETE(m_pGameElements[i]);
	}

	SAFE_DELETE_ARRAY(m_pScore);
	SAFE_DELETE(m_pStateMachine);
	SAFE_DELETE(m_pMouseZones);
	SAFE_DELETE(m_pTableSprite);

	SAFE_DELETE(m_pTitleScreenSprite);
	SAFE_DELETE(m_pCursorSprite);
	SAFE_DELETE(m_pSinglePlayerSprite);
	SAFE_DELETE(m_pTwoPlayerSprite);
	SAFE_DELETE(m_pQuitSprite);
	SAFE_DELETE(m_pSound);

	if(ICollisionChecker::TheCollisionChecker())
		ICollisionChecker::TheCollisionChecker()->Destroy();

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

	// check if ball hits horizontal wall
	if (vBallPosition.y >= (m_iDisplayHeight - m_pGameElements[PGE_BALL]->GetSprite()->GetScaledHeight())
		|| vBallPosition.y <= 0)
	{
		cBall * pBall = m_pGameElements[PGE_BALL]->CastToBall();
		if(pBall)
		{
			pBall->ChangeSpeedY();
		}
	}

	// check if ball hits vertical wall
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
	if (ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pGameElements[PGE_BALL]->GetBoundingRectangle(), m_pGameElements[PGE_PADDLE_LEFT]->GetBoundingRectangle())
		|| ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pGameElements[PGE_BALL]->GetBoundingRectangle(), m_pGameElements[PGE_PADDLE_RIGHT]->GetBoundingRectangle()))
	{
		cBall * pBall = m_pGameElements[PGE_BALL]->CastToBall();
		if(pBall)
		{
			pBall->ChangeSpeedX();
		}
		m_pSound->PlaySound(GS_BALL_PADDLE_COLLISION);
	}

	// check for collision between ball and walls
	if (ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pGameElements[PGE_BALL]->GetBoundingRectangle(), m_pGameElements[PGE_WALL_UP]->GetBoundingRectangle())
		|| ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pGameElements[PGE_BALL]->GetBoundingRectangle(), m_pGameElements[PGE_WALL_DOWN]->GetBoundingRectangle()))
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
		if (!(ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pGameElements[PGE_PADDLE_RIGHT]->GetBoundingRectangle(), m_pGameElements[PGE_WALL_UP]->GetBoundingRectangle())))
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
		if (!(ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pGameElements[PGE_PADDLE_RIGHT]->GetBoundingRectangle(), m_pGameElements[PGE_WALL_DOWN]->GetBoundingRectangle())))
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

const char * const cGame::GetGameTitle()
{
	return "MPong";
}

IGame * IGame::CreateGame()
{
	cGame * pGame = DEBUG_NEW cGame();
	return pGame;
}
