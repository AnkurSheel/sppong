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
//#include "CollisionChecker.hxx"
#include "Sound.hxx"
#include "MPongView.h"
#include "Timer.hxx"
#include "BaseControl.hxx"
#include "MessageDispatchManager.hxx"
#include "FSM\Telegram.h"
#include "FontManager.hxx"
#include "GraphicUtils.hxx"

using namespace MySound;
using namespace Graphics;
using namespace Base;
using namespace AI;
using namespace GameBase;

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

void cStateTitleScreen::VOnEnter(cGame *pGame)
{
	if (pGame->m_pHumanView->m_pAppWindowControl != NULL)
	{
		cWindowControlDef titleDef;
		titleDef.strControlName = "TitleScreen";
		titleDef.wType = cWindowControlDef::WT_STANDARD;
		titleDef.vSize = pGame->m_pHumanView->m_pAppWindowControl->VGetSize();
		IBaseControl * pTitleScreen = IBaseControl::CreateWindowControl(titleDef);
		pGame->m_pHumanView->m_pAppWindowControl->VAddChildControl(shared_ptr<IBaseControl>(pTitleScreen));
		
		cLabelControlDef def;
		def.pFont = IFontManager::GetInstance()->VGetFont("JokerMan.fnt"); 
		def.textColor = cColor::RED;
		def.strText = "MPONG";
		def.fTextHeight = 200;
		def.vPosition = cVector2(pGame->m_iDisplayWidth/4, 0);
		IBaseControl * pLabelControl = IBaseControl::CreateLabelControl(def);
		pTitleScreen->VAddChildControl(shared_ptr<IBaseControl>(pLabelControl));
	}
	IMessageDispatchManager::GetInstance()->VDispatchMessage(2.0f, pGame->VGetID(), pGame->VGetID(), MSG_SHOWMENU, NULL);
}
// ***************************************************************

void cStateTitleScreen::VOnUpdate(cGame *pGame)
{
}
// ***************************************************************

void cStateTitleScreen::VOnExit(cGame *pGame)
{
}
// ***************************************************************

bool cStateTitleScreen::VOnMessage(cGame *pGame, const Telegram &msg)
{
	if(msg.Msg == MSG_SHOWMENU)
	{
		pGame->m_pStateMachine->RequestChangeState(cStateMenuScreen::Instance());
		return true;
	}
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

void cStateMenuScreen::VOnEnter(cGame *pGame)
{
	if (pGame->m_pHumanView->m_pAppWindowControl != NULL)
	{
		cWindowControlDef menuDef;
		menuDef.strControlName = "MenuScreen";
		menuDef.wType = cWindowControlDef::WT_STANDARD;
		menuDef.vPosition = cVector2(310.f, 310.f);
		menuDef.vSize = cVector2(400, 400);
		IBaseControl * pMenuScreen = IBaseControl::CreateWindowControl(menuDef);
		pGame->m_pHumanView->m_pAppWindowControl->VAddChildControl(shared_ptr<IBaseControl>(pMenuScreen));
		pGame->m_pHumanView->m_pAppWindowControl->VMoveToFront(pMenuScreen);

		cButtonControlDef buttonDef;
		buttonDef.bAutoSize = true;
		buttonDef.vPosition = cVector2(0.0f, 0.0f);
		buttonDef.strDefaultImage = "Sprites\\buttonDefault.png";
		buttonDef.strPressedImage = "Sprites\\buttonPressed.png";
		buttonDef.labelControlDef.pFont = IFontManager::GetInstance()->VGetFont("licorice.fnt");
		buttonDef.labelControlDef.strText = "Single Player";
		buttonDef.labelControlDef.textColor = cColor::BLUE;
		buttonDef.labelControlDef.fTextHeight = 70;

		IBaseControl * pSinglePlayerButton = IBaseControl::CreateButtonControl(buttonDef);
		pMenuScreen->VAddChildControl(shared_ptr<IBaseControl>(pSinglePlayerButton));
		function<void (bool)> callbackSinglePlayerBtn;
		callbackSinglePlayerBtn = bind(&cGame::SinglePlayerButtonPressed, pGame, _1);
		pSinglePlayerButton->VRegisterCallBack(callbackSinglePlayerBtn);

		buttonDef.bAutoSize = false;
		buttonDef.vSize = pSinglePlayerButton->VGetSize();
		buttonDef.vPosition = cVector2(0.f, 80);
		buttonDef.labelControlDef.strText = "MultiPlayer";
		
		IBaseControl * pMultiPlayerButton = IBaseControl::CreateButtonControl(buttonDef);
		pMenuScreen->VAddChildControl(shared_ptr<IBaseControl>(pMultiPlayerButton));
		function<void (bool)> callbackMultiPlayerBtn;
		callbackMultiPlayerBtn = bind(&cGame::MultiPlayerButtonPressed, pGame, _1);
		pMultiPlayerButton->VRegisterCallBack(callbackMultiPlayerBtn);

		buttonDef.labelControlDef.strText = "Quit";
		buttonDef.vPosition = cVector2(0, 160);

		IBaseControl * pQuitButton = IBaseControl::CreateButtonControl(buttonDef);
		pMenuScreen->VAddChildControl(shared_ptr<IBaseControl>(pQuitButton));
		function<void (bool)> callbackQuitBtn;
		callbackQuitBtn = bind(&cGame::QuitButtonPressed, pGame, _1);
		pQuitButton->VRegisterCallBack(callbackQuitBtn);
	}
	
	//pGame->m_pSound->CreateStream(pGame->GS_MAIN_MENU_MUSIC, "resources\\Sounds\\Music\\MainMenu.mid");
	//pGame->m_pSound->PlaySound(pGame->GS_MAIN_MENU_MUSIC);
}
// ***************************************************************

void cStateMenuScreen::VOnUpdate(cGame *pGame)
{
	if (pGame->m_pStateMachine)
	{
		if (pGame->m_bSinglePlayer)
		{
			pGame->m_pStateMachine->RequestChangeState(cStatePlayGame::Instance());
		}
		if (pGame->m_bMultiPlayer)
		{
			pGame->m_pStateMachine->RequestChangeState(cStatePlayGame::Instance());
		}
	}
}
// ***************************************************************

void cStateMenuScreen::VOnExit(cGame *pGame)
{
	if (pGame->m_pHumanView->m_pAppWindowControl != NULL)
	{
		pGame->m_pHumanView->m_pAppWindowControl->VRemoveChildControl("TitleScreen");
		pGame->m_pHumanView->m_pAppWindowControl->VRemoveChildControl("MenuScreen");
	}

	pGame->m_pSound->RemoveSound(pGame->GS_MAIN_MENU_MUSIC);
}
// ***************************************************************

bool cStateMenuScreen::VOnMessage(cGame *pGame, const Telegram &msg)
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
void cStatePlayGame::VOnEnter(cGame *pGame)
{
	cPongGameElement::SetTableHeight(pGame->m_iDisplayHeight);
	cPongGameElement::SetTableWidth(pGame->m_iDisplayWidth);

	cWindowControlDef HUDDef;
	HUDDef.wType = cWindowControlDef::WT_STANDARD;
	HUDDef.vSize = pGame->m_pHumanView->m_pAppWindowControl->VGetSize();
	HUDDef.vPosition = cVector2(0.0f, 0.0f);
	IBaseControl * pHUDScreen = IBaseControl::CreateWindowControl(HUDDef);
	pGame->m_pHumanView->m_pAppWindowControl->VAddChildControl(shared_ptr<IBaseControl>(pHUDScreen));

	pGame->m_ppGameElements = DEBUG_NEW cPongGameElement*[pGame->PGE_TOTAL];
	for (int i=0; i<pGame->PGE_TOTAL; i++)
	{
		pGame->m_ppGameElements[i] = NULL;
	}
	//cLabelControlDef tableDef;
	//tableDef.strBGImageFile = "Sprites\\Table.jpg";
	//tableDef.vPosition = cVector2(0.0f, 0.0f);
	//tableDef.vSize = pHUDScreen->VGetSize();
	//tableDef.bAutoSize = false;
	//IBaseControl * pLabelControl = IBaseControl::CreateLabelControl(tableDef);
	//pHUDScreen->VAddChildControl(shared_ptr<IBaseControl>(pLabelControl));

	cVector3 vScreenTopLeftPos = IGraphicUtils::GetInstance()->ScreenToWorldSpace(cVector2(0,0), pGame->m_pHumanView->VGetCamera());
	cVector3 vscreenBottomRightPos = IGraphicUtils::GetInstance()->ScreenToWorldSpace(cVector2(pGame->m_iDisplayWidth, pGame->m_iDisplayHeight),
		pGame->m_pHumanView->VGetCamera());

	cGameElementDef paddleDef;
	paddleDef.strModelPath = "resources//cube.spdo";
	paddleDef.vPosition= cVector3(vScreenTopLeftPos.x, 0.0f, 0.0f);
	paddleDef.vScale = cVector3(0.5f, 1.5f, 0.0f);
	pGame->m_ppGameElements[pGame->PGE_PADDLE_LEFT] = DEBUG_NEW cPaddle();
	pGame->m_ppGameElements[pGame->PGE_PADDLE_LEFT]->VInitialize(paddleDef);

	paddleDef.vPosition= cVector3(vscreenBottomRightPos.x, 0.0f, 0.0f);
	pGame->m_ppGameElements[pGame->PGE_PADDLE_RIGHT] = DEBUG_NEW cPaddle();
	pGame->m_ppGameElements[pGame->PGE_PADDLE_RIGHT]->VInitialize(paddleDef);

	cGameElementDef wallDef;
	wallDef.strModelPath = "resources//cube.spdo";
	wallDef.vPosition= cVector3(0, vScreenTopLeftPos.y, 0.0f);
	wallDef.vScale = cVector3(abs(vScreenTopLeftPos.x), 0.5f, 0.0f);
	pGame->m_ppGameElements[pGame->PGE_WALL_UP] = DEBUG_NEW cWall();
	pGame->m_ppGameElements[pGame->PGE_WALL_UP]->VInitialize(wallDef);

	wallDef.vPosition= cVector3(0, vscreenBottomRightPos.y, 0.0f);
	pGame->m_ppGameElements[pGame->PGE_WALL_DOWN] = DEBUG_NEW cWall();
	pGame->m_ppGameElements[pGame->PGE_WALL_DOWN]->VInitialize(wallDef);

	cGameElementDef ballDef;
	ballDef.strModelPath = "resources//sphere.spdo";
	ballDef.vScale = cVector3(0.5f, 0.5f, 0.5f);
	pGame->m_ppGameElements[pGame->PGE_BALL] = DEBUG_NEW cBall();
	pGame->m_ppGameElements[pGame->PGE_BALL]->VInitialize(ballDef);

	pGame->m_pScore = DEBUG_NEW cScore[2]();
	
	pGame->m_pScore[0].Init(cVector2(0.0f, 0.0f));
	pHUDScreen->VAddChildControl(pGame->m_pScore[0].GetLabel());
	pHUDScreen->VMoveToFront(pGame->m_pScore[0].GetLabel().get());

	pGame->m_pScore[1].Init(cVector2((float)pGame->m_iDisplayWidth, 0.0f));
	pHUDScreen->VAddChildControl(pGame->m_pScore[1].GetLabel());
	pHUDScreen->VMoveToFront(pGame->m_pScore[1].GetLabel().get());
	
	//pGame->m_pSound->CreateSound(pGame->GS_BALL_WALL_COLLISION, "resources\\Sounds\\SFX\\collision1.wav");
	//pGame->m_pSound->CreateSound(pGame->GS_BALL_PADDLE_COLLISION, "resources\\Sounds\\SFX\\collision2.wav");
	//pGame->m_pSound->CreateSound(pGame->GS_WIN, "resources\\Sounds\\SFX\\win.wav");

	//pGame->m_pSound->CreateStream(pGame->GS_MAIN_MENU_MUSIC, "resources\\Sounds\\Music\\MainMenu.mid");
	//pGame->m_pSound->PlaySound(pGame->GS_MAIN_MENU_MUSIC);

	//pGame->m_pHumanView->SetCursorVisible(false);
}
// ***************************************************************

void cStatePlayGame::VOnUpdate(cGame *pGame)
{
	for(int i=0; i<pGame->PGE_TOTAL; i++)
	{
		if(pGame->m_ppGameElements[i])
		{
			pGame->m_ppGameElements[i]->OnUpdate(pGame->m_pGameTimer->VGetDeltaTime());
		}
	}
	pGame->m_pHumanView->VOnUpdate(pGame->m_pGameTimer->VGetRunningTicks(), pGame->m_pGameTimer->VGetDeltaTime());

	pGame->CheckForCollisions();
	pGame->CheckForWin();
}
// ***************************************************************

void cStatePlayGame::VOnExit(cGame *pGame)
{
	SAFE_DELETE_ARRAY(pGame->m_pScore);
	//ICollisionChecker::Destroy();

	pGame->VCleanup();
}
// ***************************************************************

bool cStatePlayGame::VOnMessage(cGame *pGame, const Telegram &msg)
{
	return false;
}
// ***************************************************************