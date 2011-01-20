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
#include "2D/Sprite.h"
#include "Essentials/DxBase.h"
#include "Elements/Paddle.h"
#include "Elements/Ball.h"
#include "CollisionChecker.h"
#include "Elements/Wall.h"
#include "Elements/Score.h"
#include "Essentials/MainWindow.h"
#include "GameFlowStateMachine.h"
#include "GameFlowStates.h"

#include "Input/MouseZone.h"

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
		if (!(ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pGameElements[PGE_PADDLE_UP]->GetBoundingRectangle(), m_pGameElements[PGE_WALL_DOWN]->GetBoundingRectangle())))
		{
			cPaddle * pPaddle = static_cast<cPaddle*>(m_pGameElements[PGE_PADDLE_UP]);
			if(pPaddle)
			{
				pPaddle->MoveDown(fElapsedTime);
			}
		}
	}

	if (pbPressedKeys[DIK_W])
	{
		if (!(ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pGameElements[PGE_PADDLE_UP]->GetBoundingRectangle(), m_pGameElements[PGE_WALL_UP]->GetBoundingRectangle())))
		{
			cPaddle * pPaddle = static_cast<cPaddle*>(m_pGameElements[PGE_PADDLE_UP]);
			if(pPaddle)
			{
				pPaddle->MoveUp(fElapsedTime);
			}
		}
	}

	if (pbPressedKeys[DIK_A])
	{
		if(m_pGameElements[PGE_PADDLE_UP]->GetPosition().x >= 0)
		{
			cPaddle * pPaddle = static_cast<cPaddle*>(m_pGameElements[PGE_PADDLE_UP]);
			if(pPaddle)
			{
				pPaddle->MoveLeft(fElapsedTime);
			}
		}
	}

	if (pbPressedKeys[DIK_D])
	{
		if(m_pGameElements[PGE_PADDLE_UP]->GetPosition().x <= m_iDisplayWidth/2 - m_pGameElements[PGE_PADDLE_UP]->GetSprite()->GetScaledWidth())
		{
			cPaddle * pPaddle = static_cast<cPaddle*>(m_pGameElements[PGE_PADDLE_UP]);
			if(pPaddle)
			{
				pPaddle->MoveRight(fElapsedTime);
			}
		}
	}

	// if Two Player mode handle the keys
	if (!m_bSinglePlayer)
	{
		if (pbPressedKeys[DIK_DOWN])
		{
			if (!(ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pGameElements[PGE_PADDLE_DOWN]->GetBoundingRectangle(), m_pGameElements[PGE_WALL_DOWN]->GetBoundingRectangle())))
			{
				cPaddle * pPaddle = static_cast<cPaddle*>(m_pGameElements[PGE_PADDLE_DOWN]);
				if(pPaddle)
				{
					pPaddle->MoveDown(fElapsedTime);
				}
			}
		}

		if (pbPressedKeys[DIK_UP])
		{
			if (!(ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pGameElements[PGE_PADDLE_DOWN]->GetBoundingRectangle(), m_pGameElements[PGE_WALL_UP]->GetBoundingRectangle())))
			{
				cPaddle * pPaddle = static_cast<cPaddle*>(m_pGameElements[PGE_PADDLE_DOWN]);
				if(pPaddle)
				{
					pPaddle->MoveUp(fElapsedTime);
				}
			}
		}

		if (pbPressedKeys[DIK_LEFT])
		{
			if(m_pGameElements[PGE_PADDLE_DOWN]->GetPosition().x >= m_iDisplayWidth/2)
			{
				cPaddle * pPaddle = static_cast<cPaddle*>(m_pGameElements[PGE_PADDLE_DOWN]);
				if(pPaddle)
				{
					pPaddle->MoveLeft(fElapsedTime);
				}
			}
		}

		if (pbPressedKeys[DIK_RIGHT])
		{
			if (m_pGameElements[PGE_PADDLE_DOWN]->GetPosition().x <= (m_iDisplayWidth - m_pGameElements[PGE_PADDLE_DOWN]->GetSprite()->GetScaledWidth()))
			{
				cPaddle * pPaddle = static_cast<cPaddle*>(m_pGameElements[PGE_PADDLE_DOWN]);
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
}
// ***************************************************************

// ***************************************************************
// Restarts the game
// ***************************************************************
void cGame::Restart()
{
	m_pGameElements[PGE_PADDLE_UP]->OnRestart(D3DXVECTOR3(10.0f, (float)m_iDisplayHeight/2, 0.0f));
	m_pGameElements[PGE_PADDLE_DOWN]->OnRestart(D3DXVECTOR3((float)(m_iDisplayWidth), (float)m_iDisplayHeight/2, 0.0f));
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
		cBall * pBall = static_cast<cBall *>(m_pGameElements[PGE_BALL]);
		if(pBall)
		{
			pBall->ChangeSpeedY();
		}
	}

	// check if ball hits vertical wall
	if(vBallPosition.x <= 0)
	{
		m_pScore[1].IncrementScore();
		Restart();
	}
	if (vBallPosition.x >= (m_iDisplayWidth - m_pGameElements[PGE_BALL]->GetSprite()->GetScaledWidth()))
	{
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
	if (ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pGameElements[PGE_BALL]->GetBoundingRectangle(), m_pGameElements[PGE_PADDLE_UP]->GetBoundingRectangle())
		|| ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pGameElements[PGE_BALL]->GetBoundingRectangle(), m_pGameElements[PGE_PADDLE_DOWN]->GetBoundingRectangle()))
	{
		cBall * pBall = static_cast<cBall *>(m_pGameElements[PGE_BALL]);
		if(pBall)
		{
			pBall->ChangeSpeedX();
		}
	}

	// check for collision between ball and walls
	if (ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pGameElements[PGE_BALL]->GetBoundingRectangle(), m_pGameElements[PGE_WALL_UP]->GetBoundingRectangle())
		|| ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pGameElements[PGE_BALL]->GetBoundingRectangle(), m_pGameElements[PGE_WALL_DOWN]->GetBoundingRectangle()))
	{
		cBall * pBall = static_cast<cBall *>(m_pGameElements[PGE_BALL]);
		if(pBall)
		{
			pBall->ChangeSpeedY();
		}
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
	float	fCentreOfPaddle = m_pGameElements[PGE_PADDLE_DOWN]->GetPosition().y + m_pGameElements[PGE_PADDLE_DOWN]->GetSprite()->GetScaledHeight()/2;
	float	fCentreOfBall = m_pGameElements[PGE_BALL]->GetPosition().y + m_pGameElements[PGE_BALL]->GetSprite()->GetScaledHeight()/2;

	if (fCentreOfPaddle - fCentreOfBall > 10)
	{
		if (!(ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pGameElements[PGE_PADDLE_DOWN]->GetBoundingRectangle(), m_pGameElements[PGE_WALL_UP]->GetBoundingRectangle())))
		{
			cPaddle * pPaddle = static_cast<cPaddle*>(m_pGameElements[PGE_PADDLE_DOWN]);
			if(pPaddle)
			{
				pPaddle->MoveUp(fElapsedTime);
			}
			return;
		}
	}

	if (fCentreOfBall - fCentreOfPaddle > 10)
	{
		if (!(ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pGameElements[PGE_PADDLE_DOWN]->GetBoundingRectangle(), m_pGameElements[PGE_WALL_DOWN]->GetBoundingRectangle())))
		{
			cPaddle * pPaddle = static_cast<cPaddle*>(m_pGameElements[PGE_PADDLE_DOWN]);
			if(pPaddle)
			{
				pPaddle->MoveDown(fElapsedTime);
			}
			return;
		}
	}
}