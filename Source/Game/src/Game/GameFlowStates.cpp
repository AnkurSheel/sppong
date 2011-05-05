// ***************************************************************
//  GameFlowStates   version:  1.0   Ankur Sheel  date: 05/24/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "GameFlowStates.h"
#include "Game.h"
#include "GameFlowStateMachine.h"
#include "Elements/Paddle.h"
#include "Elements/Wall.h"
#include "Elements/Score.h"
#include "Elements/Ball.h"
#include "Sprite.hxx"
#include "CollisionChecker.hxx"
#include "Sound.hxx"
#include "MPongView.h"
#include "myString.h"
#include "Timer.hxx"

using namespace MySound;
using namespace Graphics;
using namespace Base;

cStateTitleScreen::cStateTitleScreen()
{
}
// ***************************************************************

cStateTitleScreen::~cStateTitleScreen()
{
}
// ***************************************************************

cStateTitleScreen* cStateTitleScreen::Instance()
{
	static cStateTitleScreen instance;
	return &instance;
}
// ***************************************************************

void cStateTitleScreen::Enter(cGame *pGame)
{
	m_tickCurrentTime = pGame->GetRunningTime();

	ISprite * pTitleScreenSprite = ISprite::CreateSprite();

	pTitleScreenSprite->Init(pGame->m_pD3dDevice, "resources\\Sprites\\title.jpg");
	pTitleScreenSprite->SetSize((float)pGame->m_iDisplayWidth, (float)pGame->m_iDisplayHeight/5);

	pGame->m_pPongView->PushElement(pTitleScreenSprite, "");
}
// ***************************************************************

void cStateTitleScreen::Execute(cGame *pGame)
{
	//ankur - temp comment
	//// display the title screen for 2 secs before displaying the menu screen
	if(pGame->GetRunningTime() - m_tickCurrentTime > 2.0)
 	{
 		pGame->m_pStateMachine->ChangeState(cStateMenuScreen::Instance());
 	}
	//end ankur - temp comment
}
// ***************************************************************

void cStateTitleScreen::Exit(cGame *pGame)
{
	pGame->m_pPongView->RemoveElements();
 	pGame->m_pPongView->FreeZones();
}
// ***************************************************************

bool cStateTitleScreen::OnMessage(cGame *pGame, const Telegram &msg)
{
	return false;
}
// ***************************************************************

cStateMenuScreen::cStateMenuScreen()
{
}
// ***************************************************************

cStateMenuScreen::~cStateMenuScreen()
{
}
// ***************************************************************

cStateMenuScreen* cStateMenuScreen::Instance()
{
	static cStateMenuScreen instance;
	return &instance;
}
// ***************************************************************

void cStateMenuScreen::Enter(cGame *pGame)
{
	ISprite * pTitleScreenSprite = ISprite::CreateSprite();
	ISprite * pSinglePlayerSprite = ISprite::CreateSprite();
	ISprite * pTwoPlayerSprite = ISprite::CreateSprite();
	ISprite * pQuitSprite = ISprite::CreateSprite();

	pTitleScreenSprite->Init(pGame->m_pD3dDevice, "resources\\Sprites\\title.jpg");
	pTitleScreenSprite->SetSize((float)pGame->m_iDisplayWidth, (float)pGame->m_iDisplayHeight/5);
	pTitleScreenSprite->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pGame->m_pPongView->PushElement(pTitleScreenSprite, "");

	int iSinglePlayerSpritePosY = pTitleScreenSprite->GetScaledHeight() + pGame->m_iDisplayHeight/5;

	pSinglePlayerSprite->Init(pGame->m_pD3dDevice, "resources\\Sprites\\SinglePlayer.jpg");
	pSinglePlayerSprite->SetSize((float)pGame->m_iDisplayWidth/10, (float)pGame->m_iDisplayHeight/10);
	pSinglePlayerSprite->SetPosition(D3DXVECTOR3((float)pGame->m_iDisplayWidth/2 - pSinglePlayerSprite->GetScaledWidth()/2, 
												 (float)iSinglePlayerSpritePosY, 0.0f));
	pGame->m_pPongView->PushElement(pSinglePlayerSprite, "Single Player");

	int iTwoPlayerSpritePosY = iSinglePlayerSpritePosY + pSinglePlayerSprite->GetScaledHeight() + pGame->m_iDisplayHeight/15;
	
	pTwoPlayerSprite->Init(pGame->m_pD3dDevice, "resources\\Sprites\\TwoPlayer.jpg");
	pTwoPlayerSprite->SetSize((float)pGame->m_iDisplayWidth/10, (float)pGame->m_iDisplayHeight/10);
	pTwoPlayerSprite->SetPosition(D3DXVECTOR3((float)pGame->m_iDisplayWidth/2 - pTwoPlayerSprite->GetScaledWidth()/2, 
											(float)iTwoPlayerSpritePosY, 0.0f));
	pGame->m_pPongView->PushElement(pTwoPlayerSprite, "Two Player");

	int iQuitSpritePosY = iTwoPlayerSpritePosY + pTwoPlayerSprite->GetScaledHeight() + pGame->m_iDisplayHeight/15;
	
	pQuitSprite->Init(pGame->m_pD3dDevice, "resources\\Sprites\\Quit.jpg");
	pQuitSprite->SetSize((float)pGame->m_iDisplayWidth/10, (float)pGame->m_iDisplayHeight/10);
	pQuitSprite->SetPosition(D3DXVECTOR3((float)pGame->m_iDisplayWidth/2 - pQuitSprite->GetScaledWidth()/2, 
										(float)iQuitSpritePosY, 0.0f));
	pGame->m_pPongView->PushElement(pQuitSprite, "Quit");
	
	pGame->m_pSound->CreateStream(pGame->GS_MAIN_MENU_MUSIC, "resources\\Sounds\\Music\\MainMenu.mid");
	pGame->m_pSound->PlaySound(pGame->GS_MAIN_MENU_MUSIC);

}
// ***************************************************************

void cStateMenuScreen::Execute(cGame *pGame)
{
	cString strZoneName;
	if (pGame->m_pPongView->CheckZones(strZoneName))
	{
		if (strZoneName == "Single Player")
		{
			pGame->m_bSinglePlayer = true;
			pGame->m_pStateMachine->ChangeState(cStatePlayGame::Instance());
		}
		else if (strZoneName == "Two Player")
		{
			pGame->m_bSinglePlayer = false;
			pGame->m_pStateMachine->ChangeState(cStatePlayGame::Instance());
		}
		else if (strZoneName == "Quit")
		{
			PostQuitMessage(0);
		}
	}
}
// ***************************************************************

void cStateMenuScreen::Exit(cGame *pGame)
{
	pGame->m_pSound->RemoveSound(pGame->GS_MAIN_MENU_MUSIC);

	pGame->m_pPongView->RemoveElements();
 	pGame->m_pPongView->FreeZones();
}
// ***************************************************************

bool cStateMenuScreen::OnMessage(cGame *pGame, const Telegram &msg)
{
	return false;
}
// ***************************************************************

cStatePlayGame::cStatePlayGame()
{
}
// ***************************************************************

cStatePlayGame::~cStatePlayGame()
{
}
// ***************************************************************

cStatePlayGame* cStatePlayGame::Instance()
{
	static cStatePlayGame instance;
	return &instance;
}
// ***************************************************************

void cStatePlayGame::Enter(cGame *pGame)
{
	ICollisionChecker::CreateCollisionChecker();

	ISprite * pTableSprite = ISprite::CreateSprite();

	pTableSprite->Init(pGame->m_pD3dDevice, "resources\\Sprites\\Table.jpg");
	pTableSprite->SetSize((float)pGame->m_iDisplayWidth, (float)pGame->m_iDisplayHeight);
	pTableSprite->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pGame->m_pPongView->PushElement(pTableSprite, "");

	cPongGameElement::SetTableHeight(pGame->m_iDisplayHeight);
	cPongGameElement::SetTableWidth(pGame->m_iDisplayWidth);

	pGame->m_pGameElements[pGame->PGE_PADDLE_LEFT] = DEBUG_NEW cPaddle();
	pGame->m_pGameElements[pGame->PGE_PADDLE_LEFT]->Init(D3DXVECTOR3(10.0f, (float)pGame->m_iDisplayHeight/2, 0.0f), "resources\\Sprites\\paddle.jpg");
	pGame->m_pPongView->PushElement(const_cast<ISprite *>(pGame->m_pGameElements[pGame->PGE_PADDLE_LEFT]->GetSprite()), "");

	pGame->m_pGameElements[pGame->PGE_PADDLE_RIGHT] = DEBUG_NEW cPaddle();
	pGame->m_pGameElements[pGame->PGE_PADDLE_RIGHT]->Init(D3DXVECTOR3((float)(pGame->m_iDisplayWidth), (float)pGame->m_iDisplayHeight/2, 0.0f), "resources\\Sprites\\paddle.jpg");
	pGame->m_pPongView->PushElement(const_cast<ISprite *>(pGame->m_pGameElements[pGame->PGE_PADDLE_RIGHT]->GetSprite()), "");

	pGame->m_pGameElements[pGame->PGE_WALL_UP] = DEBUG_NEW cWall();
	pGame->m_pGameElements[pGame->PGE_WALL_UP]->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "resources\\Sprites\\wall.png");
	pGame->m_pPongView->PushElement(const_cast<ISprite *>(pGame->m_pGameElements[pGame->PGE_WALL_UP]->GetSprite()), "");

	pGame->m_pGameElements[pGame->PGE_WALL_DOWN] = DEBUG_NEW cWall();
	pGame->m_pGameElements[pGame->PGE_WALL_DOWN]->Init(D3DXVECTOR3(0.0f, (float)pGame->m_iDisplayHeight, 0.0f), "resources\\Sprites\\wall.png");
	pGame->m_pPongView->PushElement(const_cast<ISprite *>(pGame->m_pGameElements[pGame->PGE_WALL_DOWN]->GetSprite()), "");

	pGame->m_pGameElements[pGame->PGE_BALL] = DEBUG_NEW cBall();
	pGame->m_pGameElements[pGame->PGE_BALL]->Init(D3DXVECTOR3((float)pGame->m_iDisplayWidth/2, (float)pGame->m_iDisplayHeight/2, 0.0f), "resources\\Sprites\\ball.png");
	pGame->m_pPongView->PushElement(const_cast<ISprite *>(pGame->m_pGameElements[pGame->PGE_BALL]->GetSprite()), "");

	pGame->m_pScore = DEBUG_NEW cScore[2]();
	pGame->m_pScore[0].Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pGame->m_pScore[1].Init(D3DXVECTOR3((float)pGame->m_iDisplayWidth, 0.0f, 0.0f));

	pGame->m_pSound->CreateSound(pGame->GS_BALL_WALL_COLLISION, "resources\\Sounds\\SFX\\collision1.wav");
	pGame->m_pSound->CreateSound(pGame->GS_BALL_PADDLE_COLLISION, "resources\\Sounds\\SFX\\collision2.wav");
	pGame->m_pSound->CreateSound(pGame->GS_WIN, "resources\\Sounds\\SFX\\win.wav");

	pGame->m_pSound->CreateStream(pGame->GS_MAIN_MENU_MUSIC, "resources\\Sounds\\Music\\MainMenu.mid");
	pGame->m_pSound->PlaySound(pGame->GS_MAIN_MENU_MUSIC);

	OnResetDevice(pGame);
}
// ***************************************************************

void cStatePlayGame::Execute(cGame *pGame)
{
	for(int i=0; i<pGame->PGE_TOTAL; i++)
	{
		pGame->m_pGameElements[i]->OnUpdate(pGame->m_pGameTimer->GetElapsedTime());
	}
	pGame->CheckForCollisions();
	pGame->CheckForWin();
}
// ***************************************************************

void cStatePlayGame::Exit(cGame *pGame)
{
	SAFE_DELETE_ARRAY(pGame->m_pScore);
	pGame->m_pPongView->RemoveElements();
	for(int i=0;i<pGame->PGE_TOTAL;i++)
	{
		SAFE_DELETE(pGame->m_pGameElements[i]);
	}
	if(ICollisionChecker::TheCollisionChecker())
		ICollisionChecker::TheCollisionChecker()->Destroy();

	pGame->Cleanup();

}
// ***************************************************************

bool cStatePlayGame::OnMessage(cGame *pGame, const Telegram &msg)
{
	return false;
}
// ***************************************************************

void cStatePlayGame::OnLostDevice( cGame *pGame )
{
	pGame->m_pScore[0].OnLostDevice();
	pGame->m_pScore[1].OnLostDevice();
}
// ***************************************************************

void cStatePlayGame::OnResetDevice( cGame *pGame )
{
	pGame->m_pScore[0].OnResetDevice(pGame->m_pD3dDevice);
	pGame->m_pScore[1].OnResetDevice(pGame->m_pD3dDevice);
}
// ***************************************************************