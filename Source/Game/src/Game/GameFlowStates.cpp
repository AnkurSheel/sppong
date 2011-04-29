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
#include "MainWindow.hxx"
#include "Sprite.hxx"
#include "CollisionChecker.hxx"
#include "MouseZone.hxx"
#include "Sound.hxx"

using namespace MySound;
using namespace Graphics;

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
	m_fCurrentTime = IMainWindow::TheWindow()->GetRunningTime();

	pGame->m_pTitleScreenSprite = ISprite::CreateSprite();
	pGame->m_pCursorSprite = ISprite::CreateSprite();

	OnResetDevice(pGame);

	pGame->m_pMouseZones->FreeZones();
	pGame->m_pMouseZones->AddZone("Title Screen", 0, 0, pGame->m_iDisplayWidth, pGame->m_iDisplayHeight, LEFTBUTTON);
}
// ***************************************************************

void cStateTitleScreen::Execute(cGame *pGame)
{
	pGame->m_pTitleScreenSprite->DrawSprite(pGame->m_pD3dDevice, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXSPRITE_ALPHABLEND);
	pGame->m_pCursorSprite->DrawSprite(pGame->m_pD3dDevice, D3DXVECTOR3((float)IMainWindow::TheWindow()->GetAbsXMousePos(), (float)IMainWindow::TheWindow()->GetAbsYMousePos(), 0.0f), D3DXSPRITE_ALPHABLEND);
	
	// display the title screen for 2 secs before displaying the menu screen
 	if(IMainWindow::TheWindow()->GetRunningTime() - m_fCurrentTime > 2.0)
 	{
 		pGame->m_pStateMachine->ChangeState(cStateMenuScreen::Instance());
 	}
}
// ***************************************************************

void cStateTitleScreen::Exit(cGame *pGame)
{
	SAFE_DELETE(pGame->m_pTitleScreenSprite);
	SAFE_DELETE(pGame->m_pCursorSprite);
}
// ***************************************************************

bool cStateTitleScreen::OnMessage(cGame *pGame, const Telegram &msg)
{
	return false;
}
// ***************************************************************

void cStateTitleScreen::OnLostDevice(cGame *pGame)
{
	pGame->m_pTitleScreenSprite->Cleanup();
	pGame->m_pCursorSprite->Cleanup();
}
// ***************************************************************

void cStateTitleScreen::OnResetDevice(cGame *pGame)
{
	pGame->m_pTitleScreenSprite->Init(pGame->m_pD3dDevice, "resources\\Sprites\\title.jpg");
	pGame->m_pTitleScreenSprite->SetSize((float)pGame->m_iDisplayWidth, (float)pGame->m_iDisplayHeight/5);

	pGame->m_pCursorSprite->Init(pGame->m_pD3dDevice, "resources\\Sprites\\cursor.png");
	pGame->m_pCursorSprite->SetSize((float)pGame->m_iDisplayWidth/30, (float)pGame->m_iDisplayHeight/30);
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
	pGame->m_pTitleScreenSprite = ISprite::CreateSprite();
	pGame->m_pCursorSprite = ISprite::CreateSprite();
	pGame->m_pSinglePlayerSprite = ISprite::CreateSprite();
	pGame->m_pTwoPlayerSprite = ISprite::CreateSprite();
	pGame->m_pQuitSprite = ISprite::CreateSprite();

	OnResetDevice(pGame);

 	pGame->m_pMouseZones->FreeZones();

	m_iSinglePlayerSpritePosY = pGame->m_pTitleScreenSprite->GetScaledHeight() + pGame->m_iDisplayHeight/5;
	pGame->m_pMouseZones->AddZone("Single Player", (pGame->m_iDisplayWidth/2 - pGame->m_pSinglePlayerSprite->GetScaledWidth()/2), m_iSinglePlayerSpritePosY , pGame->m_pSinglePlayerSprite->GetScaledWidth(), pGame->m_pSinglePlayerSprite->GetScaledHeight(), LEFTBUTTON);

	m_iTwoPlayerSpritePosY = m_iSinglePlayerSpritePosY + pGame->m_pSinglePlayerSprite->GetScaledHeight() + pGame->m_iDisplayHeight/15;
	pGame->m_pMouseZones->AddZone("Two Player", pGame->m_iDisplayWidth/2 - pGame->m_pTwoPlayerSprite->GetScaledWidth()/2, m_iTwoPlayerSpritePosY , pGame->m_pTwoPlayerSprite->GetScaledWidth(), pGame->m_pTwoPlayerSprite->GetScaledHeight(), LEFTBUTTON);
	
	m_iQuitSpritePosY = m_iTwoPlayerSpritePosY + pGame->m_pTwoPlayerSprite->GetScaledHeight() + pGame->m_iDisplayHeight/15;
	pGame->m_pMouseZones->AddZone("Quit", pGame->m_iDisplayWidth/2 - pGame->m_pQuitSprite->GetScaledWidth()/2, m_iQuitSpritePosY, pGame->m_pQuitSprite->GetScaledWidth(), pGame->m_pQuitSprite->GetScaledHeight(), LEFTBUTTON);
	pGame->m_pSound->CreateStream(pGame->GS_MAIN_MENU_MUSIC, "resources\\Sounds\\Music\\MainMenu.mid");
	pGame->m_pSound->PlaySound(pGame->GS_MAIN_MENU_MUSIC);

}
// ***************************************************************

void cStateMenuScreen::Execute(cGame *pGame)
{
	pGame->m_pTitleScreenSprite->DrawSprite(pGame->m_pD3dDevice, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXSPRITE_ALPHABLEND);
	pGame->m_pSinglePlayerSprite->DrawSprite(pGame->m_pD3dDevice, D3DXVECTOR3((float)pGame->m_iDisplayWidth/2 - pGame->m_pSinglePlayerSprite->GetScaledWidth()/2, (float)m_iSinglePlayerSpritePosY, 0.0f), D3DXSPRITE_ALPHABLEND);
	pGame->m_pTwoPlayerSprite->DrawSprite(pGame->m_pD3dDevice, D3DXVECTOR3((float)pGame->m_iDisplayWidth/2 - pGame->m_pTwoPlayerSprite->GetScaledWidth()/2, (float)m_iTwoPlayerSpritePosY, 0.0f), D3DXSPRITE_ALPHABLEND);
	pGame->m_pQuitSprite->DrawSprite(pGame->m_pD3dDevice, D3DXVECTOR3((float)pGame->m_iDisplayWidth/2 - pGame->m_pQuitSprite->GetScaledWidth()/2, (float)m_iQuitSpritePosY, 0.0f), D3DXSPRITE_ALPHABLEND);
	pGame->m_pCursorSprite->DrawSprite(pGame->m_pD3dDevice, D3DXVECTOR3((float)IMainWindow::TheWindow()->GetAbsXMousePos(), (float)IMainWindow::TheWindow()->GetAbsYMousePos(), 0.0f), D3DXSPRITE_ALPHABLEND);
}
// ***************************************************************

void cStateMenuScreen::Exit(cGame *pGame)
{
	pGame->m_pSound->RemoveSound(pGame->GS_MAIN_MENU_MUSIC);
	SAFE_DELETE(pGame->m_pTitleScreenSprite);
	SAFE_DELETE(pGame->m_pCursorSprite);
	SAFE_DELETE(pGame->m_pSinglePlayerSprite);
	SAFE_DELETE(pGame->m_pTwoPlayerSprite);
	SAFE_DELETE(pGame->m_pQuitSprite);
}
// ***************************************************************

bool cStateMenuScreen::OnMessage(cGame *pGame, const Telegram &msg)
{
	return false;
}
// ***************************************************************

void cStateMenuScreen::OnLostDevice(cGame *pGame)
{
	pGame->m_pTitleScreenSprite->Cleanup();
	pGame->m_pCursorSprite->Cleanup();
	pGame->m_pSinglePlayerSprite->Cleanup();
	pGame->m_pTwoPlayerSprite->Cleanup();
	pGame->m_pQuitSprite->Cleanup();
}
// ***************************************************************

void cStateMenuScreen::OnResetDevice(cGame *pGame)
{
	pGame->m_pTitleScreenSprite->Init(pGame->m_pD3dDevice, "resources\\Sprites\\title.jpg");
	pGame->m_pTitleScreenSprite->SetSize((float)pGame->m_iDisplayWidth, (float)pGame->m_iDisplayHeight/5);

	pGame->m_pCursorSprite->Init(pGame->m_pD3dDevice, "resources\\Sprites\\cursor.png");
	pGame->m_pCursorSprite->SetSize((float)pGame->m_iDisplayWidth/30, (float)pGame->m_iDisplayHeight/30);

	pGame->m_pSinglePlayerSprite->Init(pGame->m_pD3dDevice, "resources\\Sprites\\SinglePlayer.jpg");
	pGame->m_pSinglePlayerSprite->SetSize((float)pGame->m_iDisplayWidth/10, (float)pGame->m_iDisplayHeight/10);

	pGame->m_pTwoPlayerSprite->Init(pGame->m_pD3dDevice, "resources\\Sprites\\TwoPlayer.jpg");
	pGame->m_pTwoPlayerSprite->SetSize((float)pGame->m_iDisplayWidth/10, (float)pGame->m_iDisplayHeight/10);

	pGame->m_pQuitSprite->Init(pGame->m_pD3dDevice, "resources\\Sprites\\Quit.jpg");
	pGame->m_pQuitSprite->SetSize((float)pGame->m_iDisplayWidth/10, (float)pGame->m_iDisplayHeight/10);
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

	pGame->m_pTableSprite = ISprite::CreateSprite();

	cPongGameElement::SetTableHeight(pGame->m_iDisplayHeight);
	cPongGameElement::SetTableWidth(pGame->m_iDisplayWidth);

	pGame->m_pGameElements[pGame->PGE_PADDLE_LEFT] = DEBUG_NEW cPaddle();
	pGame->m_pGameElements[pGame->PGE_PADDLE_LEFT]->Init(D3DXVECTOR3(10.0f, (float)pGame->m_iDisplayHeight/2, 0.0f), "resources\\Sprites\\paddle.jpg");

	pGame->m_pGameElements[pGame->PGE_PADDLE_RIGHT] = DEBUG_NEW cPaddle();
	pGame->m_pGameElements[pGame->PGE_PADDLE_RIGHT]->Init(D3DXVECTOR3((float)(pGame->m_iDisplayWidth), (float)pGame->m_iDisplayHeight/2, 0.0f), "resources\\Sprites\\paddle.jpg");

	pGame->m_pGameElements[pGame->PGE_WALL_UP] = DEBUG_NEW cWall();
	pGame->m_pGameElements[pGame->PGE_WALL_UP]->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), "resources\\Sprites\\wall.png");

	pGame->m_pGameElements[pGame->PGE_WALL_DOWN] = DEBUG_NEW cWall();
	pGame->m_pGameElements[pGame->PGE_WALL_DOWN]->Init(D3DXVECTOR3(0.0f, (float)pGame->m_iDisplayHeight, 0.0f), "resources\\Sprites\\wall.png");

	pGame->m_pGameElements[pGame->PGE_BALL] = DEBUG_NEW cBall();
	pGame->m_pGameElements[pGame->PGE_BALL]->Init(D3DXVECTOR3((float)pGame->m_iDisplayWidth/2, (float)pGame->m_iDisplayHeight/2, 0.0f), "resources\\Sprites\\ball.png");

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
	pGame->m_pTableSprite->DrawSprite(pGame->m_pD3dDevice, D3DXVECTOR3(0,0,0), D3DXSPRITE_ALPHABLEND);
	
	for(int i=0;i<pGame->PGE_TOTAL;i++)
	{
		pGame->m_pGameElements[i]->Render(pGame->m_pD3dDevice); 
	}
	pGame->m_pScore[0].Render(pGame->m_pD3dDevice);
	pGame->m_pScore[1].Render(pGame->m_pD3dDevice);

	pGame->CheckForCollisions();
	pGame->CheckForWin();
}
// ***************************************************************

void cStatePlayGame::Exit(cGame *pGame)
{
	SAFE_DELETE(pGame->m_pTableSprite);
	SAFE_DELETE_ARRAY(pGame->m_pScore);
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
	for(int i=0;i<pGame->PGE_TOTAL;i++)
	{
		pGame->m_pGameElements[i]->OnLostDevice();
	}
	pGame->m_pTableSprite->Cleanup();
	pGame->m_pScore[0].OnLostDevice();
	pGame->m_pScore[1].OnLostDevice();
}
// ***************************************************************

void cStatePlayGame::OnResetDevice( cGame *pGame )
{
	pGame->m_pTableSprite->Init(pGame->m_pD3dDevice, "resources\\Sprites\\Table.jpg");
	pGame->m_pTableSprite->SetSize((float)pGame->m_iDisplayWidth, (float)pGame->m_iDisplayHeight);

	for(int i=0;i<pGame->PGE_TOTAL;i++)
	{
		pGame->m_pGameElements[i]->OnResetDevice(pGame->m_pD3dDevice);
	}

	pGame->m_pScore[0].OnResetDevice(pGame->m_pD3dDevice);
	pGame->m_pScore[1].OnResetDevice(pGame->m_pD3dDevice);
}
// ***************************************************************