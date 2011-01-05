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
#include "fsm/StateMachine.h"
#include "GameFlowStates.h"

#include "Input/MouseZone.h"

// ***************************************************************
// Constructor
// ***************************************************************
cGame::cGame()
: m_pPaddleSprite(NULL)
, m_pBallSprite(NULL)
, m_pWallSprite(NULL)
, m_pTitleScreenSprite(NULL)
, m_pCursorSprite(NULL)
, m_pPaddle(NULL)
, m_pBall(NULL)
, m_pWall(NULL)
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
	m_pPaddleSprite->Init(m_pD3dDevice, "resources\\Sprites\\paddle.jpg");
	m_pBallSprite->Init(m_pD3dDevice, "resources\\Sprites\\ball.png");
	m_pWallSprite->Init(m_pD3dDevice, "resources\\Sprites\\wall.png");

	m_pPaddle[0].OnResetDevice(m_pPaddleSprite);
	m_pPaddle[1].OnResetDevice(m_pPaddleSprite);
	m_pBall->OnResetDevice(m_pBallSprite);
	m_pWall[0].OnResetDevice(m_pWallSprite);
	m_pWall[1].OnResetDevice(m_pWallSprite);

	m_pScore[0].OnResetDevice(m_pD3dDevice);
	m_pScore[1].OnResetDevice(m_pD3dDevice);
}
// ***************************************************************

// ***************************************************************
// Free the resources that are volatile
// ***************************************************************
void cGame::OnLostDevice()
{
	m_pPaddleSprite->Cleanup();
	m_pBallSprite->Cleanup();
	m_pWallSprite->Cleanup();
	m_pScore[0].OnLostDevice();
	m_pScore[1].OnLostDevice();
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

	m_pPaddle = DEBUG_NEW cPaddle[2]();
	m_pBall = DEBUG_NEW cBall();
	m_pWall = DEBUG_NEW cWall[2]();
	m_pScore = DEBUG_NEW cScore[2]();

	m_pPaddleSprite = ISprite::CreateSprite();
	m_pBallSprite = ISprite::CreateSprite();
	m_pWallSprite = ISprite::CreateSprite();
	
	m_pMouseZones = IMouseZone::CreateMouseZone();

	ICollisionChecker::CreateCollisionChecker();
	m_pStateMachine = DEBUG_NEW cStateMachine<cGame>(this);
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
		if (!(ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pPaddle[0].GetBoundingRectangle(), m_pWall[1].GetBoundingRectangle())))
		{
			m_pPaddle[0].MoveDown(fElapsedTime);
		}
	}

	if (pbPressedKeys[DIK_W])
	{
		if (!(ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pPaddle[0].GetBoundingRectangle(), m_pWall[0].GetBoundingRectangle())))
		{
			m_pPaddle[0].MoveUp(fElapsedTime);
		}
	}

	if (pbPressedKeys[DIK_A])
	{
		if(m_pPaddle[0].GetPosition().x >= 0)
		{
				m_pPaddle[0].MoveLeft(fElapsedTime);
		}
	}

	if (pbPressedKeys[DIK_D])
	{
		if(m_pPaddle[0].GetPosition().x <= m_iDisplayWidth/2 - m_pPaddleSprite->GetScaledWidth())
		{
			m_pPaddle[0].MoveRight(fElapsedTime);
		}
	}

	// if Two Player mode handle the keys
	if (!m_bSinglePlayer)
	{
		if (pbPressedKeys[DIK_DOWN])
		{
			if (!(ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pPaddle[1].GetBoundingRectangle(), m_pWall[1].GetBoundingRectangle())))
			{
				m_pPaddle[1].MoveDown(fElapsedTime);
			}
		}

		if (pbPressedKeys[DIK_UP])
		{
			if (!(ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pPaddle[1].GetBoundingRectangle(), m_pWall[0].GetBoundingRectangle())))
			{
				m_pPaddle[1].MoveUp(fElapsedTime);
			}
		}

		if (pbPressedKeys[DIK_LEFT])
		{
			if(m_pPaddle[1].GetPosition().x >= m_iDisplayWidth/2)
			{
				m_pPaddle[1].MoveLeft(fElapsedTime);
			}
		}

		if (pbPressedKeys[DIK_RIGHT])
		{
			if (m_pPaddle[1].GetPosition().x <= (m_iDisplayWidth - m_pPaddleSprite->GetScaledWidth()))
			{
				m_pPaddle[1].MoveRight(fElapsedTime);
			}
		}
	}
	else // single player mode
	{
		HandlePaddleAI(fElapsedTime);
	}

	//TCHAR szZoneName[64]; ;
	char szZoneName[64];
	if (m_pMouseZones->CheckZones(IMainWindow::TheWindow()->GetAbsXMousePos(), IMainWindow::TheWindow()->GetAbsYMousePos(), pbMouseButtons, szZoneName))
	{
		if(m_pStateMachine->GetCurrentState() == cStateTitleScreen::Instance())
		{
			//if (_tcscmp(szZoneName, _T("Title Screen")) == 0)
			if (strcmp(szZoneName, "Title Screen") == 0)
			{
				m_pStateMachine->ChangeState(cStateMenuScreen::Instance());
			}
		}

		if (m_pStateMachine->GetCurrentState() == cStateMenuScreen::Instance())
		{
			//if (_tcscmp(szZoneName, _T("Single Player")) == 0)
			if (strcmp(szZoneName, "Single Player") == 0)
			{
				m_bSinglePlayer = true;
				m_pStateMachine->ChangeState(cStatePlayGame::Instance());
			}

			//if (_tcscmp(szZoneName, _T("Two Player")) == 0)
			if (strcmp(szZoneName, "Two Player") == 0)
			{
				m_bSinglePlayer = false;
				m_pStateMachine->ChangeState(cStatePlayGame::Instance());
			}
			//if (_tcscmp(szZoneName, _T("Quit")) == 0)
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
	SAFE_DELETE(m_pPaddleSprite) ;
	SAFE_DELETE(m_pBallSprite);
	SAFE_DELETE(m_pWallSprite);
	SAFE_DELETE_ARRAY(m_pPaddle);
	SAFE_DELETE(m_pBall);
	SAFE_DELETE_ARRAY(m_pWall);
	SAFE_DELETE_ARRAY(m_pScore);
	SAFE_DELETE(m_pStateMachine);
	SAFE_DELETE(m_pMouseZones);

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
	m_pPaddle[0].OnRestart(D3DXVECTOR3(10.0f, (float)m_iDisplayHeight/2, 0.0f));
	m_pPaddle[1].OnRestart(D3DXVECTOR3((float)(m_iDisplayWidth), (float)m_iDisplayHeight/2, 0.0f));

	m_pBall->OnRestart(D3DXVECTOR3((float)m_iDisplayWidth/2, (float)m_iDisplayHeight/2, 0.0f));
}
// ***************************************************************

// ***************************************************************
// Checks if either player has won
// ***************************************************************
void cGame::CheckForWin()
{
	D3DXVECTOR3 vBallPosition = m_pBall->GetPosition();

	// check if ball hits horizontal wall
	if (vBallPosition.y >= (m_iDisplayHeight - m_pBallSprite->GetScaledHeight())
		|| vBallPosition.y <= 0)
	{

		m_pBall->ChangeSpeedY();
	}

	// check if ball hits vertical wall
	if(vBallPosition.x <= 0)
	{
		m_pScore[1].IncrementScore();
		Restart();
	}
	if (vBallPosition.x >= (m_iDisplayWidth - m_pBallSprite->GetScaledWidth()))
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
	if (ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pBall->GetBoundingRectangle(), m_pPaddle[0].GetBoundingRectangle())
		|| ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pBall->GetBoundingRectangle(), m_pPaddle[1].GetBoundingRectangle()))
	{
		m_pBall->ChangeSpeedX();
	}

	// check for collision between ball and walls
	if (ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pBall->GetBoundingRectangle(), m_pWall[0].GetBoundingRectangle())
		|| ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pBall->GetBoundingRectangle(), m_pWall[1].GetBoundingRectangle()))
	{
		m_pBall->ChangeSpeedY();
	}
}
// ***************************************************************

// ***************************************************************
// the AI for the paddle
// ***************************************************************
void cGame::HandlePaddleAI( const float fElapsedTime )
{
	// if the ball is in the players half, there is no need to do anything
	if (m_pBall->GetPosition().x < m_iDisplayWidth/2)
	{
		return;
	}
	float	fCentreOfPaddle = m_pPaddle[1].GetPosition().y + m_pPaddleSprite->GetScaledHeight()/2;
	float	fCentreOfBall = m_pBall->GetPosition().y + m_pBallSprite->GetScaledHeight()/2;

	if (fCentreOfPaddle - fCentreOfBall > 10)
	{
		if (!(ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pPaddle[1].GetBoundingRectangle(), m_pWall[0].GetBoundingRectangle())))
		{
			m_pPaddle[1].MoveUp(fElapsedTime);
			return;
		}
	}

	if (fCentreOfBall - fCentreOfPaddle > 10)
	{
		if (!(ICollisionChecker::TheCollisionChecker()->CheckFor2DCollisions(m_pPaddle[1].GetBoundingRectangle(), m_pWall[1].GetBoundingRectangle())))
		{
			m_pPaddle[1].MoveDown(fElapsedTime);
			return;
		}
	}
}