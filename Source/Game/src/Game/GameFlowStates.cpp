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
#include "myString.h"
#include "Timer.hxx"
#include "BaseControl.hxx"
#include "MessageDispatchManager.hxx"
#include "FSM\Telegram.h"
#include "Color.h"
#include "FontManager.hxx"

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
		stLabelControlDef def;
		def.pFont = IFontManager::GetInstance()->VGetFont("JokerMan.fnt"); 
		def.textColor = cColor::RED;
		def.strText = "MPONG";
		def.fTextHeight = 200;

		IBaseControl * pLabelControl = IBaseControl::CreateLabelControl(def);
		pGame->m_pHumanView->m_pAppWindowControl->VAddChildControl(shared_ptr<IBaseControl>(pLabelControl));
		pLabelControl->VSetPosition(cVector2(pGame->m_iDisplayWidth/4, 0));
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
		stWindowControlDef menuDef;
		menuDef.wType = WT_STANDARD;
		IBaseControl * pMenuScreen = IBaseControl::CreateWindowControl(menuDef);
		pGame->m_pHumanView->m_pAppWindowControl->VAddChildControl(shared_ptr<IBaseControl>(pMenuScreen));
		pMenuScreen->VSetPosition(cVector2(311.f, 310.f));
		pMenuScreen->VSetSize(cVector2(400,400));

		stButtonControlDef buttonDef;
		buttonDef.bAutoSize = true;
		buttonDef.strDefaultImage = "Sprites\\buttonDefault.png";
		buttonDef.strPressedImage = "Sprites\\buttonPressed.png";
		buttonDef.labelControlDef.pFont = IFontManager::GetInstance()->VGetFont("JokerMan.fnt");
		buttonDef.labelControlDef.strText = "Single Player";
		buttonDef.labelControlDef.textColor = cColor::BLUE;
		buttonDef.labelControlDef.fTextHeight = 70;

		IBaseControl * pSinglePlayerButton = IBaseControl::CreateButtonControl(buttonDef);
		pMenuScreen->VAddChildControl(shared_ptr<IBaseControl>(pSinglePlayerButton));
		pSinglePlayerButton->VSetPosition(cVector2(0.0f, 0.0f));
		function<void (bool)> callbackSinglePlayerBtn;
		callbackSinglePlayerBtn = bind(&cGame::SinglePlayerButtonPressed, pGame, _1);
		pSinglePlayerButton->VRegisterCallBack(callbackSinglePlayerBtn);

		buttonDef.bAutoSize = false;
		buttonDef.iWidth = pSinglePlayerButton->VGetWidth();
		buttonDef.iHeight = pSinglePlayerButton->VGetHeight();
		buttonDef.labelControlDef.strText = "MultiPlayer";
		
		IBaseControl * pMultiPlayerButton = IBaseControl::CreateButtonControl(buttonDef);
		pMenuScreen->VAddChildControl(shared_ptr<IBaseControl>(pMultiPlayerButton));
		pMultiPlayerButton->VSetPosition(cVector2(0.f, 80));
		function<void (bool)> callbackMultiPlayerBtn;
		callbackMultiPlayerBtn = bind(&cGame::MultiPlayerButtonPressed, pGame, _1);
		pMultiPlayerButton->VRegisterCallBack(callbackMultiPlayerBtn);

		buttonDef.labelControlDef.strText = "Quit";
		
		IBaseControl * pQuitButton = IBaseControl::CreateButtonControl(buttonDef);
		pMenuScreen->VAddChildControl(shared_ptr<IBaseControl>(pQuitButton));
		pQuitButton->VSetPosition(cVector2(0, 160));
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
		pGame->m_pHumanView->m_pAppWindowControl->VRemoveAllChildren();
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
	//shared_ptr<ISprite> pTableSprite = ISprite::CreateSprite();

	//pTableSprite->VInitialize("Sprites\\Table.jpg");
	//pTableSprite->VSetSize(cVector2((float)pGame->m_iDisplayWidth, (float)pGame->m_iDisplayHeight));
	//pTableSprite->VSetPosition(cVector2(0.0f, 0.0f));
	//pGame->m_pHumanView->PushElement(pTableSprite);

	//cPongGameElement::SetTableHeight(pGame->m_iDisplayHeight);
	//cPongGameElement::SetTableWidth(pGame->m_iDisplayWidth);

	//shared_ptr<ISprite> pSprite;

	//pGame->m_pGameElements[pGame->PGE_PADDLE_LEFT] = DEBUG_NEW cPaddle();
	//pGame->m_pGameElements[pGame->PGE_PADDLE_LEFT]->Init(cVector3(10.0f, (float)pGame->m_iDisplayHeight/2, 0.0f), "Sprites\\paddle.jpg");
	//pSprite = const_pointer_cast<ISprite>(pGame->m_pGameElements[pGame->PGE_PADDLE_LEFT]->GetSprite());
	//pGame->m_pHumanView->PushElement(pSprite);

	//pGame->m_pGameElements[pGame->PGE_PADDLE_RIGHT] = DEBUG_NEW cPaddle();
	//pGame->m_pGameElements[pGame->PGE_PADDLE_RIGHT]->Init(cVector3((float)(pGame->m_iDisplayWidth), (float)pGame->m_iDisplayHeight/2, 0.0f), "Sprites\\paddle.jpg");
	//pSprite = const_pointer_cast<ISprite>(pGame->m_pGameElements[pGame->PGE_PADDLE_RIGHT]->GetSprite());
	//pGame->m_pHumanView->PushElement(pSprite);

	//pGame->m_pGameElements[pGame->PGE_WALL_UP] = DEBUG_NEW cWall();
	//pGame->m_pGameElements[pGame->PGE_WALL_UP]->Init(cVector3(0.0f, 0.0f, 0.0f), "Sprites\\wall.png");
	//pSprite = const_pointer_cast<ISprite>(pGame->m_pGameElements[pGame->PGE_WALL_UP]->GetSprite());
	//pGame->m_pHumanView->PushElement(pSprite);

	//pGame->m_pGameElements[pGame->PGE_WALL_DOWN] = DEBUG_NEW cWall();
	//pGame->m_pGameElements[pGame->PGE_WALL_DOWN]->Init(cVector3(0.0f, (float)pGame->m_iDisplayHeight, 0.0f), "Sprites\\wall.png");
	//pSprite = const_pointer_cast<ISprite>(pGame->m_pGameElements[pGame->PGE_WALL_DOWN]->GetSprite());
	//pGame->m_pHumanView->PushElement(pSprite);

	//pGame->m_pGameElements[pGame->PGE_BALL] = DEBUG_NEW cBall();
	//pGame->m_pGameElements[pGame->PGE_BALL]->Init(cVector3((float)pGame->m_iDisplayWidth/2, (float)pGame->m_iDisplayHeight/2, 0.0f), "Sprites\\ball.png");
	//pSprite = const_pointer_cast<ISprite>(pGame->m_pGameElements[pGame->PGE_BALL]->GetSprite());
	//pGame->m_pHumanView->PushElement(pSprite);

	//pGame->m_pScore = DEBUG_NEW cScore[2]();
	//
	//pGame->m_pScore[0].Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//pGame->m_pHumanView->m_pAppWindowControl->VAddChildControl(pGame->m_pScore[0].GetLabel());
	//
	//pGame->m_pScore[1].Init(D3DXVECTOR3((float)pGame->m_iDisplayWidth, 0.0f, 0.0f));
	//pGame->m_pHumanView->m_pAppWindowControl->VAddChildControl(pGame->m_pScore[1].GetLabel());
	//
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
		pGame->m_pGameElements[i]->OnUpdate(pGame->m_pGameTimer->VGetDeltaTime());
	}
	pGame->m_pHumanView->VOnUpdate(pGame->m_pGameTimer->VGetRunningTicks(), pGame->m_pGameTimer->VGetDeltaTime());

	pGame->CheckForCollisions();
	pGame->CheckForWin();
}
// ***************************************************************

void cStatePlayGame::VOnExit(cGame *pGame)
{
	SAFE_DELETE_ARRAY(pGame->m_pScore);
	//pGame->m_pHumanView->RemoveElements();
	for(int i=0;i<pGame->PGE_TOTAL;i++)
	{
		SAFE_DELETE(pGame->m_pGameElements[i]);
	}
	//ICollisionChecker::Destroy();

	pGame->VCleanup();
}
// ***************************************************************

bool cStatePlayGame::VOnMessage(cGame *pGame, const Telegram &msg)
{
	return false;
}
// ***************************************************************