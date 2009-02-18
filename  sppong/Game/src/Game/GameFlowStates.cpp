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
#include "fsm/StateMachine.h"
#include "Elements/Paddle.h"
#include "Elements/Wall.h"
#include "Elements/Score.h"
#include "Elements/Ball.h"
#include "Essentials/MainWindow.h"
#include "2D/Sprite.h"

#include "Input/MouseZone.h"

cStateTitleScreen::cStateTitleScreen()
{
}
// ***************************************************************

cStateTitleScreen::~cStateTitleScreen()
{
}
// ***************************************************************

// ***************************************************************
// Instance
// ***************************************************************
cStateTitleScreen* cStateTitleScreen::Instance()
{
	static cStateTitleScreen instance;
	return &instance;
}
// ***************************************************************

// ***************************************************************
// State Enter, Execute and Exit
// ***************************************************************
void cStateTitleScreen::Enter(cGame *pGame)
{
	//MyTrace("Enter : ccStateEnterGame\n");
	pGame->m_pTitleScreenSprite = new cSprite();
	pGame->m_pTitleScreenSprite->Init(pGame->m_pD3dDevice, _T("..\\bin\\resources\\title.jpg"));
	m_fCurrentTime = cMainWindow::GetInstance().GetRunningTime();

	pGame->m_pTitleScreenSprite->SetSize((float)pGame->m_iDisplayWidth, (float)pGame->m_iDisplayHeight/5);

	pGame->m_pCursorSprite = new cSprite();
	pGame->m_pCursorSprite->Init(pGame->m_pD3dDevice, _T("..\\bin\\resources\\cursor.png"));
	pGame->m_pCursorSprite->SetSize(16.0f, 16.0f);
	
	pGame->m_pMouseZones->FreeZones();
	pGame->m_pMouseZones->AddZone(_T("Title Screen"), 0, 0, pGame->m_iDisplayWidth, pGame->m_iDisplayHeight, LEFTBUTTON);
}
// ***************************************************************

void cStateTitleScreen::Execute(cGame *pGame)
{
	pGame->m_pTitleScreenSprite->DrawSprite(pGame->m_pD3dDevice, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXSPRITE_ALPHABLEND);
	pGame->m_pCursorSprite->DrawSprite(pGame->m_pD3dDevice, D3DXVECTOR3((float)cMainWindow::GetInstance().GetAbsXMousePos(), (float)cMainWindow::GetInstance().GetAbsYMousePos(), 0.0f), D3DXSPRITE_ALPHABLEND);
	
	// display the title screen for 5 secs before displaying the menu screen
 	if(cMainWindow::GetInstance().GetRunningTime() - m_fCurrentTime > 1.0)
 	{
 		pGame->m_pStateMachine->ChangeState(cStateMenuScreen::Instance());
 	}
}
// ***************************************************************

void cStateTitleScreen::Exit(cGame *pGame)
{
}
// ***************************************************************

// ***************************************************************
// Messages
// ***************************************************************
bool cStateTitleScreen::OnMessage(cGame *pGame, const Telegram &msg)
{
	return false;
}


cStateMenuScreen::cStateMenuScreen()
{
}
// ***************************************************************

cStateMenuScreen::~cStateMenuScreen()
{
}
// ***************************************************************

// ***************************************************************
// Instance
// ***************************************************************
cStateMenuScreen* cStateMenuScreen::Instance()
{
	static cStateMenuScreen instance;
	return &instance;
}
// ***************************************************************

// ***************************************************************
// State Enter, Execute and Exit
// ***************************************************************
void cStateMenuScreen::Enter(cGame *pGame)
{
	pGame->m_pSinglePlayerSprite = new cSprite();
	pGame->m_pSinglePlayerSprite->Init(pGame->m_pD3dDevice, _T("..\\bin\\resources\\SinglePlayer.jpg"));
	pGame->m_pSinglePlayerSprite->SetSize((float)pGame->m_iDisplayWidth/10, (float)pGame->m_iDisplayHeight/10);

	pGame->m_pTwoPlayerSprite = new cSprite();
	pGame->m_pTwoPlayerSprite->Init(pGame->m_pD3dDevice, _T("..\\bin\\resources\\TwoPlayer.jpg"));
	pGame->m_pTwoPlayerSprite->SetSize((float)pGame->m_iDisplayWidth/10, (float)pGame->m_iDisplayHeight/10);

	pGame->m_pQuitSprite = new cSprite();
	pGame->m_pQuitSprite->Init(pGame->m_pD3dDevice, _T("..\\bin\\resources\\Quit.jpg"));
	pGame->m_pQuitSprite->SetSize((float)pGame->m_iDisplayWidth/10, (float)pGame->m_iDisplayHeight/10);

 	pGame->m_pMouseZones->FreeZones();

	m_iSinglePlayerSpritePosY = pGame->m_pTitleScreenSprite->GetScaledHeight() + pGame->m_iDisplayHeight/5;
 	pGame->m_pMouseZones->AddZone(_T("Single Player"), (pGame->m_iDisplayWidth/2 - pGame->m_pSinglePlayerSprite->GetScaledWidth()/2), m_iSinglePlayerSpritePosY , pGame->m_pSinglePlayerSprite->GetScaledWidth(), pGame->m_pSinglePlayerSprite->GetScaledHeight(), LEFTBUTTON);

	m_iTwoPlayerSpritePosY = m_iSinglePlayerSpritePosY + pGame->m_pSinglePlayerSprite->GetScaledHeight() + pGame->m_iDisplayHeight/15;
	pGame->m_pMouseZones->AddZone(_T("Two Player"), pGame->m_iDisplayWidth/2 - pGame->m_pTwoPlayerSprite->GetScaledWidth()/2, m_iTwoPlayerSpritePosY , pGame->m_pTwoPlayerSprite->GetScaledWidth(), pGame->m_pTwoPlayerSprite->GetScaledHeight(), LEFTBUTTON);

	m_iQuitSpritePosY = m_iTwoPlayerSpritePosY + pGame->m_pTwoPlayerSprite->GetScaledHeight() + pGame->m_iDisplayHeight/15;
	pGame->m_pMouseZones->AddZone(_T("Quit"), pGame->m_iDisplayWidth/2 - pGame->m_pQuitSprite->GetScaledWidth()/2, m_iQuitSpritePosY, pGame->m_pQuitSprite->GetScaledWidth(), pGame->m_pQuitSprite->GetScaledHeight(), LEFTBUTTON);
}
// ***************************************************************

void cStateMenuScreen::Execute(cGame *pGame)
{
	pGame->m_pTitleScreenSprite->DrawSprite(pGame->m_pD3dDevice, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXSPRITE_ALPHABLEND);
	pGame->m_pSinglePlayerSprite->DrawSprite(pGame->m_pD3dDevice, D3DXVECTOR3((float)pGame->m_iDisplayWidth/2 - pGame->m_pSinglePlayerSprite->GetScaledWidth()/2, (float)m_iSinglePlayerSpritePosY, 0.0f), D3DXSPRITE_ALPHABLEND);
	pGame->m_pTwoPlayerSprite->DrawSprite(pGame->m_pD3dDevice, D3DXVECTOR3((float)pGame->m_iDisplayWidth/2 - pGame->m_pTwoPlayerSprite->GetScaledWidth()/2, (float)m_iTwoPlayerSpritePosY, 0.0f), D3DXSPRITE_ALPHABLEND);
	pGame->m_pQuitSprite->DrawSprite(pGame->m_pD3dDevice, D3DXVECTOR3((float)pGame->m_iDisplayWidth/2 - pGame->m_pQuitSprite->GetScaledWidth()/2, (float)m_iQuitSpritePosY, 0.0f), D3DXSPRITE_ALPHABLEND);
	pGame->m_pCursorSprite->DrawSprite(pGame->m_pD3dDevice, D3DXVECTOR3((float)cMainWindow::GetInstance().GetAbsXMousePos(), (float)cMainWindow::GetInstance().GetAbsYMousePos(), 0.0f), D3DXSPRITE_ALPHABLEND);
}
// ***************************************************************

void cStateMenuScreen::Exit(cGame *pGame)
{
	//MyTrace("Exit : ccStateEnterGame\n\n");
	pGame->m_pTitleScreenSprite->Cleanup();
	SAFE_DELETE(pGame->m_pTitleScreenSprite);
	pGame->m_pCursorSprite->Cleanup();
	SAFE_DELETE(pGame->m_pCursorSprite);
	pGame->m_pSinglePlayerSprite->Cleanup();
	SAFE_DELETE(pGame->m_pSinglePlayerSprite);
}
// ***************************************************************

// ***************************************************************
// Messages
// ***************************************************************
bool cStateMenuScreen::OnMessage(cGame *pGame, const Telegram &msg)
{
	return false;
}


cStatePlayGame::cStatePlayGame()
{
}
// ***************************************************************

cStatePlayGame::~cStatePlayGame()
{
}
// ***************************************************************

// ***************************************************************
// Instance
// ***************************************************************
cStatePlayGame* cStatePlayGame::Instance()
{
	static cStatePlayGame instance;
	return &instance;
}
// ***************************************************************

// ***************************************************************
// State Enter, Execute and Exit
// ***************************************************************
void cStatePlayGame::Enter(cGame *pGame)
{
	pGame->m_pBall->Init(D3DXVECTOR3((float)pGame->m_iDisplayWidth/2, (float)pGame->m_iDisplayHeight/2, 0.0f), pGame->m_iDisplayWidth, pGame->m_iDisplayHeight);

	pGame->m_pPaddle[0].Init(D3DXVECTOR3(10.0f, (float)pGame->m_iDisplayHeight/2, 0.0f));
	pGame->m_pPaddle[1].Init(D3DXVECTOR3((float)(pGame->m_iDisplayWidth), (float)pGame->m_iDisplayHeight/2, 0.0f));

	pGame->m_pWall[0].Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pGame->m_pWall[1].Init(D3DXVECTOR3(0.0f, (float)pGame->m_iDisplayHeight, 0.0f));

	pGame->m_pScore[0].Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pGame->m_pScore[1].Init(D3DXVECTOR3((float)pGame->m_iDisplayWidth, 0.0f, 0.0f));

	pGame->OnResetDevice();
}
// ***************************************************************

void cStatePlayGame::Execute(cGame *pGame)
{
	////MyTrace("Execute : ccStatePlayGame\n");
	pGame->m_pPaddle[0].Render(pGame->m_pD3dDevice); 
	pGame->m_pPaddle[1].Render(pGame->m_pD3dDevice); 
	pGame->m_pWall[0].Render(pGame->m_pD3dDevice);
	pGame->m_pWall[1].Render(pGame->m_pD3dDevice);
	pGame->m_pBall->Render(pGame->m_pD3dDevice, cMainWindow::GetInstance().GetElapsedTime());
	pGame->m_pScore[0].Render(pGame->m_pD3dDevice);
	pGame->m_pScore[1].Render(pGame->m_pD3dDevice);

	pGame->CheckForCollisions();
	pGame->CheckForWin();
	//pGame->m_pStateMachine->ChangeState(StateCoinToss::Instance());
}
// ***************************************************************

void cStatePlayGame::Exit(cGame *pGame)
{
	pGame->Cleanup();
}
// ***************************************************************

// ***************************************************************
// Messages
// ***************************************************************
bool cStatePlayGame::OnMessage(cGame *pGame, const Telegram &msg)
{
	return false;
}
// ***************************************************************