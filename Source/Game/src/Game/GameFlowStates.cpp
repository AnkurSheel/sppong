// *****************************************************************************
//  GameFlowStates   version:  1.0   Ankur Sheel  date: 05/24/2008
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "GameFlowStates.h"
#include "Game.h"
#include "GameFlowStateMachine.h"
#include "Elements/Paddle.h"
#include "Elements/Wall.h"
#include "Elements/Score.h"
#include "Elements/Ball.h"
#include "Sprite.hxx"
#include "MPongView.h"
#include "Timer.hxx"
#include "BaseControl.hxx"
#include "MessageDispatchManager.hxx"
#include "FSM\Telegram.h"
#include "FontManager.hxx"
#include "GraphicUtils.hxx"
#include "MainWindow.hxx"
#include "GameOptions.h"

using namespace Graphics;
using namespace Base;
using namespace AI;
using namespace GameBase;
using namespace Utilities;

cStateTitleScreen::cStateTitleScreen()
{
}
// *****************************************************************************

cStateTitleScreen::~cStateTitleScreen()
{
}
// *****************************************************************************

cStateTitleScreen* cStateTitleScreen::Instance()
{
	static cStateTitleScreen instance;
	return &instance;
}
// *****************************************************************************

void cStateTitleScreen::VOnEnter(cGame *pGame)
{
	IGameFlowStates::VOnEnter(pGame);
	if (pGame->m_pHumanView->m_pAppWindowControl != NULL)
	{
		cWindowControlDef titleDef;
		titleDef.strControlName = "TitleScreen";
		titleDef.wType = cWindowControlDef::WT_STANDARD;
		titleDef.vSize = pGame->m_pHumanView->m_pAppWindowControl->VGetSize();
		IBaseControl * pTitleScreen = IBaseControl::CreateWindowControl(titleDef);
		pGame->m_pHumanView->m_pAppWindowControl->VAddChildControl(shared_ptr<IBaseControl>(pTitleScreen));
		
		cLabelControlDef def;
		def.strControlName = "TitleLabel";
		def.pFont = IFontManager::GetInstance()->VGetFont("JokerMan.fnt"); 
		def.textColor = cColor::RED;
		def.strText = "MPONG";
		def.fTextHeight = 200;
		def.vPosition = cVector2(static_cast<float>(pGame->m_iDisplayWidth/4), 0.0f);
		IBaseControl * pLabelControl = IBaseControl::CreateLabelControl(def);
		pTitleScreen->VAddChildControl(shared_ptr<IBaseControl>(pLabelControl));
	}
	pGame->m_pHumanView->PlayMusic("Sounds\\Music\\mainmenu.ogg", true);

	IMessageDispatchManager::GetInstance()->VDispatchMessage(2.0f, pGame->VGetID(), pGame->VGetID(), MSG_SHOWMENU, NULL);
}
// *****************************************************************************

void cStateTitleScreen::VOnUpdate()
{
}
// *****************************************************************************

void cStateTitleScreen::VOnExit()
{
}
// *****************************************************************************

bool cStateTitleScreen::VOnMessage(const Telegram &msg)
{
	if(msg.Msg == MSG_SHOWMENU)
	{
		m_pOwner->m_pStateMachine->RequestChangeState(cStateMenuScreen::Instance());
		return true;
	}
	return false;
}
// *****************************************************************************

cStateMenuScreen::cStateMenuScreen()
: m_pMenuScreen(NULL)
{
}
// *****************************************************************************

cStateMenuScreen::~cStateMenuScreen()
{
}
// *****************************************************************************

cStateMenuScreen* cStateMenuScreen::Instance()
{
	static cStateMenuScreen instance;
	return &instance;
}
// *****************************************************************************

void cStateMenuScreen::VOnEnter(cGame *pGame)
{
	IGameFlowStates::VOnEnter(pGame);
	if (pGame->m_pHumanView->m_pAppWindowControl != NULL)
	{
		cWindowControlDef menuDef;
		menuDef.strControlName = "MenuScreen";
		menuDef.wType = cWindowControlDef::WT_STANDARD;
		menuDef.vPosition = cVector2(0, 0);
		menuDef.vSize = pGame->m_pHumanView->m_pAppWindowControl->VGetSize();
		m_pMenuScreen = IBaseControl::CreateWindowControl(menuDef);
		pGame->m_pHumanView->m_pAppWindowControl->VAddChildControl(shared_ptr<IBaseControl>(m_pMenuScreen));
		pGame->m_pHumanView->m_pAppWindowControl->VMoveToFront(m_pMenuScreen);

		cButtonControlDef buttonDef;
		buttonDef.strControlName = "btnSinglePlayer";
		buttonDef.bAutoSize = true;
		//buttonDef.vPosition = cVector2(412, 170);
		buttonDef.vPosition = cVector2(412, 270);
		buttonDef.strDefaultImage = "Sprites\\buttonDefault.png";
		buttonDef.strPressedImage = "Sprites\\buttonPressed.png";
		buttonDef.labelControlDef.pFont = IFontManager::GetInstance()->VGetFont("licorice.fnt");
		buttonDef.labelControlDef.strText = "Single Player";
		buttonDef.labelControlDef.textColor = cColor::BLUE;
		buttonDef.labelControlDef.fTextHeight = 70;

		IBaseControl * pSinglePlayerButton = IBaseControl::CreateButtonControl(buttonDef);
		m_pMenuScreen->VAddChildControl(shared_ptr<IBaseControl>(pSinglePlayerButton));
		UIEventCallBackFn callbackSinglePlayerBtn;
		callbackSinglePlayerBtn = bind(&cStateMenuScreen::SinglePlayerButtonPressed, this, _1);
		pSinglePlayerButton->VRegisterCallBack(UIET_BTNRELEASED, callbackSinglePlayerBtn);

		buttonDef.strControlName = "btnMultiPlayer";
		buttonDef.bAutoSize = false;
		buttonDef.vSize = pSinglePlayerButton->VGetSize();
		//buttonDef.vPosition = cVector2(412, 270);
		buttonDef.vPosition = cVector2(412, 370);
		buttonDef.labelControlDef.strText = "MultiPlayer";
		
		IBaseControl * pMultiPlayerButton = IBaseControl::CreateButtonControl(buttonDef);
		m_pMenuScreen->VAddChildControl(shared_ptr<IBaseControl>(pMultiPlayerButton));
		UIEventCallBackFn callbackMultiPlayerBtn;
		callbackMultiPlayerBtn = bind(&cStateMenuScreen::MultiPlayerButtonPressed, this, _1);
		pMultiPlayerButton->VRegisterCallBack(UIET_BTNRELEASED, callbackMultiPlayerBtn);

		buttonDef.strControlName = "btnOption";
		buttonDef.labelControlDef.strText = "Options";
		buttonDef.vPosition = cVector2(412, 470);

		IBaseControl * pOptionsButton = IBaseControl::CreateButtonControl(buttonDef);
		m_pMenuScreen->VAddChildControl(shared_ptr<IBaseControl>(pOptionsButton));
		UIEventCallBackFn callbackOptionsBtn;
		callbackOptionsBtn = bind(&cStateMenuScreen::OptionsButtonPressed, this, _1);
		pOptionsButton->VRegisterCallBack(UIET_BTNRELEASED, callbackOptionsBtn);

		buttonDef.strControlName = "btnHelp";
		buttonDef.labelControlDef.strText = "Help";
		buttonDef.vPosition = cVector2(412, 570);

		IBaseControl * pHelpButton = IBaseControl::CreateButtonControl(buttonDef);
		m_pMenuScreen->VAddChildControl(shared_ptr<IBaseControl>(pHelpButton));
		UIEventCallBackFn callbackHelpBtn;
		callbackHelpBtn = bind(&cStateMenuScreen::HelpButtonPressed, this, _1);
		pHelpButton->VRegisterCallBack(UIET_BTNRELEASED, callbackHelpBtn);

		buttonDef.strControlName = "btnCredits";
		//buttonDef.labelControlDef.strText = "Credits";
		//buttonDef.vPosition = cVector2(412, 570);

		//IBaseControl * pCreditsButton = IBaseControl::CreateButtonControl(buttonDef);
		//m_pMenuScreen->VAddChildControl(shared_ptr<IBaseControl>(pCreditsButton));
		////UIEventCallBackFn callbackCreditsBtn;
		////callbackCreditsBtn = bind(&cGame::QuitButtonPressed, pGame, _1);
		////pCreditsButton->VRegisterCallBack(callbackCreditsBtn);

		buttonDef.strControlName = "btnQuit";
		buttonDef.labelControlDef.strText = "Quit";
		buttonDef.vPosition = cVector2(412, 670);

		IBaseControl * pQuitButton = IBaseControl::CreateButtonControl(buttonDef);
		m_pMenuScreen->VAddChildControl(shared_ptr<IBaseControl>(pQuitButton));
		UIEventCallBackFn callbackQuitBtn;
		callbackQuitBtn = bind(&cStateMenuScreen::QuitButtonPressed, this, _1);
		pQuitButton->VRegisterCallBack(UIET_BTNRELEASED, callbackQuitBtn);
	}
}
// *****************************************************************************

void cStateMenuScreen::VOnUpdate()
{
	if (m_pOwner && m_pOwner->m_pStateMachine)
	{
		if (m_pOwner->m_bSinglePlayer)
		{
			m_pOwner->m_pStateMachine->RequestChangeState(cStatePlayGame::Instance());
		}
		if (m_pOwner->m_bMultiPlayer)
		{
			m_pOwner->m_pStateMachine->RequestChangeState(cStatePlayGame::Instance());
		}
	}
}
// *****************************************************************************

void cStateMenuScreen::VOnExit()
{
	if (m_pOwner->m_pHumanView->m_pAppWindowControl != NULL)
	{
		m_pOwner->m_pHumanView->m_pAppWindowControl->VRemoveChildControl("TitleScreen");
		m_pOwner->m_pHumanView->m_pAppWindowControl->VRemoveChildControl("MenuScreen");
	}
}
// *****************************************************************************

bool cStateMenuScreen::VOnMessage(const Telegram &msg)
{
	return false;
}

// *****************************************************************************
void cStateMenuScreen::VOnPause()
{
	IGameFlowStates::VOnPause();
	if (m_pMenuScreen != NULL)
	{
		m_pMenuScreen->VSetVisible(false);
	}
}

// *****************************************************************************
void cStateMenuScreen::VOnResume()
{
	IGameFlowStates::VOnResume();
	if (m_pMenuScreen != NULL)
	{
		m_pMenuScreen->VSetVisible(true);
	}
}

// *****************************************************************************
void cStateMenuScreen::SinglePlayerButtonPressed(const unUIEventCallbackParam & params)
{
	m_pOwner->m_bSinglePlayer = true;
	cMPongView * pView = dynamic_cast<cMPongView *>(m_pOwner->m_pHumanView);
	if(pView)
		pView->OnSinglePlayerSelected(m_pOwner);
}

// *****************************************************************************
void cStateMenuScreen::MultiPlayerButtonPressed(const unUIEventCallbackParam & params)
{
	m_pOwner->m_bMultiPlayer = true;
	cMPongView * pView = dynamic_cast<cMPongView *>(m_pOwner->m_pHumanView);
	if(pView)
		pView->OnMultiPlayerSelected(m_pOwner);
}

// *****************************************************************************
void cStateMenuScreen::HelpButtonPressed(const unUIEventCallbackParam & params)
{
	if(m_pOwner != NULL && m_pOwner->m_pStateMachine != NULL)
	{
		m_pOwner->m_pStateMachine->RequestPushState(cStateHelpScreen::Instance());
	}
}

// *****************************************************************************
void cStateMenuScreen::OptionsButtonPressed(const unUIEventCallbackParam & params)
{
	if(m_pOwner != NULL && m_pOwner->m_pStateMachine != NULL)
	{
		m_pOwner->m_pStateMachine->RequestPushState(cStateOptionsScreen::Instance());
	}
}

// *****************************************************************************
void cStateMenuScreen::QuitButtonPressed(const unUIEventCallbackParam & params)
{
	PostQuitMessage(0);
}

// *****************************************************************************
cStatePlayGame::cStatePlayGame()
{
}
// *****************************************************************************

cStatePlayGame::~cStatePlayGame()
{
}
// *****************************************************************************

cStatePlayGame* cStatePlayGame::Instance()
{
	static cStatePlayGame instance;
	return &instance;
}

// *****************************************************************************
void cStatePlayGame::VOnEnter(cGame *pGame)
{
	IGameFlowStates::VOnEnter(pGame);
	cPongGameElement::SetGame(pGame);

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

	pGame->m_vScreenTopLeftPos = IGraphicUtils::GetInstance()->ScreenToWorldSpace(cVector2(0,0), pGame->m_pHumanView->GetCamera());
	pGame->m_vScreenBottomRightPos = IGraphicUtils::GetInstance()->ScreenToWorldSpace(cVector2(static_cast<float>(pGame->m_iDisplayWidth), static_cast<float>(pGame->m_iDisplayHeight)),
		pGame->m_pHumanView->GetCamera());

	cGameElementDef paddleDef;
	paddleDef.strModelPath = "Media\\cube.spdo";
	paddleDef.vPosition= cVector3(pGame->m_vScreenTopLeftPos.x, 0.0f, 0.0f);
	paddleDef.vScale = cVector3(0.5f, 1.5f, 0.5f);
	pGame->m_ppGameElements[pGame->PGE_PADDLE_LEFT] = DEBUG_NEW cPaddle();
	pGame->m_ppGameElements[pGame->PGE_PADDLE_LEFT]->VInitialize(paddleDef);

	paddleDef.vPosition= cVector3(pGame->m_vScreenBottomRightPos.x, 0.0f, 0.0f);
	pGame->m_ppGameElements[pGame->PGE_PADDLE_RIGHT] = DEBUG_NEW cPaddle();
	pGame->m_ppGameElements[pGame->PGE_PADDLE_RIGHT]->VInitialize(paddleDef);

	cGameElementDef wallDef;
	wallDef.strModelPath = "Media\\cube.spdo";
	wallDef.vPosition= cVector3(0, pGame->m_vScreenTopLeftPos.y, 0.0f);
	wallDef.vScale = cVector3(abs(pGame->m_vScreenTopLeftPos.x), 0.5f, 0.5f);
	pGame->m_ppGameElements[pGame->PGE_WALL_UP] = DEBUG_NEW cWall();
	pGame->m_ppGameElements[pGame->PGE_WALL_UP]->VInitialize(wallDef);

	wallDef.vPosition= cVector3(0, pGame->m_vScreenBottomRightPos.y, 0.0f);
	pGame->m_ppGameElements[pGame->PGE_WALL_DOWN] = DEBUG_NEW cWall();
	pGame->m_ppGameElements[pGame->PGE_WALL_DOWN]->VInitialize(wallDef);

	cGameElementDef ballDef;
	ballDef.strModelPath = "Media\\sphere.spdo";
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
	
	//pGame->m_pHumanView->SetCursorVisible(false);
}
// *****************************************************************************

void cStatePlayGame::VOnUpdate()
{
	for(int i=0; i<m_pOwner->PGE_TOTAL; i++)
	{
		if(m_pOwner->m_ppGameElements[i])
		{
			m_pOwner->m_ppGameElements[i]->OnUpdate(m_pOwner->m_pGameTimer->VGetDeltaTime());
		}
	}
	m_pOwner->m_pHumanView->VOnUpdate(m_pOwner->m_pGameTimer->VGetRunningTicks(), m_pOwner->m_pGameTimer->VGetDeltaTime());
	if(m_pOwner->IsSinglePlayer())
	{
		m_pOwner->HandlePaddleAI(m_pOwner->m_pGameTimer->VGetDeltaTime());
	}
}
// *****************************************************************************

void cStatePlayGame::VOnExit()
{
	SAFE_DELETE_ARRAY(m_pOwner->m_pScore);

	m_pOwner->VCleanup();
}
// *****************************************************************************

bool cStatePlayGame::VOnMessage(const Telegram &msg)
{
	return false;
}

// *****************************************************************************
cStateHelpScreen::cStateHelpScreen()
{
}

// *****************************************************************************
cStateHelpScreen::~cStateHelpScreen()
{
}

// *****************************************************************************
cStateHelpScreen* cStateHelpScreen::Instance()
{
	static cStateHelpScreen instance;
	return &instance;
}

// *****************************************************************************
void cStateHelpScreen::VOnEnter(cGame *pGame)
{
	IGameFlowStates::VOnEnter(pGame);
	if (pGame->m_pHumanView->m_pAppWindowControl != NULL)
	{
		cWindowControlDef helpDef;
		helpDef.strControlName = "HelpScreen";
		helpDef.wType = cWindowControlDef::WT_STANDARD;
		helpDef.vPosition = cVector2(0, 0);
		helpDef.vSize = pGame->m_pHumanView->m_pAppWindowControl->VGetSize();
		IBaseControl * pHelpScreen = IBaseControl::CreateWindowControl(helpDef);
		pGame->m_pHumanView->m_pAppWindowControl->VAddChildControl(shared_ptr<IBaseControl>(pHelpScreen));
		pGame->m_pHumanView->m_pAppWindowControl->VMoveToFront(pHelpScreen);

		cLabelControlDef def;
		def.strControlName = "labelHelp";
		def.pFont = IFontManager::GetInstance()->VGetFont("licorice.fnt"); 
		def.textColor = cColor::VIOLET;
		def.strText = "SinglePlayer\n Press W to Move up\n Press S to Move Down";
		def.strText += "\n\n\nMultiplayer\n Press up arrow to Move up\n Press ";
		def.strText += "down arrow to Move Down";
		def.fTextHeight = 30;
		def.vPosition = cVector2(0, 170);
		IBaseControl * pLabelControl = IBaseControl::CreateLabelControl(def);
		pHelpScreen->VAddChildControl(shared_ptr<IBaseControl>(pLabelControl));

		cButtonControlDef buttonDef;
		buttonDef.strControlName = "btnBack";
		buttonDef.bAutoSize = true;
		buttonDef.vPosition = cVector2(0, 480);
		buttonDef.strDefaultImage = "Sprites\\buttonDefault.png";
		buttonDef.strPressedImage = "Sprites\\buttonPressed.png";
		buttonDef.labelControlDef.pFont = IFontManager::GetInstance()->VGetFont("licorice.fnt");
		buttonDef.labelControlDef.strText = "Back";
		buttonDef.labelControlDef.textColor = cColor::BLUE;
		buttonDef.labelControlDef.fTextHeight = 50;

		IBaseControl * pBackButton = IBaseControl::CreateButtonControl(buttonDef);
		pHelpScreen->VAddChildControl(shared_ptr<IBaseControl>(pBackButton));
		UIEventCallBackFn callBackBtn;
		callBackBtn = bind(&cStateHelpScreen::BackButtonPressed, this, _1);
		pBackButton->VRegisterCallBack(UIET_BTNRELEASED, callBackBtn);
	}
}

// *****************************************************************************
void cStateHelpScreen::VOnUpdate()
{

}

// *****************************************************************************
void cStateHelpScreen::VOnExit()
{
	if (m_pOwner->m_pHumanView->m_pAppWindowControl != NULL)
	{
		m_pOwner->m_pHumanView->m_pAppWindowControl->VRemoveChildControl("HelpScreen");
	}
}

// *****************************************************************************
bool cStateHelpScreen::VOnMessage(const Telegram &msg)
{
	return false;
}

void cStateHelpScreen::BackButtonPressed(const unUIEventCallbackParam & params)
{
	if(m_pOwner != NULL && m_pOwner->m_pStateMachine != NULL)
	{
		m_pOwner->m_pStateMachine->RequestPopState();
	}
}

// *****************************************************************************
cStateOptionsScreen::cStateOptionsScreen()
: m_pOptionsScreen(NULL)
{
}

// *****************************************************************************
cStateOptionsScreen::~cStateOptionsScreen()
{
}

// *****************************************************************************
cStateOptionsScreen* cStateOptionsScreen::Instance()
{
	static cStateOptionsScreen instance;
	return &instance;
}

// *****************************************************************************
void cStateOptionsScreen::VOnEnter(cGame *pGame)
{
	IGameFlowStates::VOnEnter(pGame);
	if (pGame->m_pHumanView->m_pAppWindowControl != NULL)
	{
		cWindowControlDef optionsDef;
		optionsDef.strControlName = "OptionsScreen";
		optionsDef.wType = cWindowControlDef::WT_STANDARD;
		optionsDef.vPosition = cVector2(0, 0);
		optionsDef.vSize = pGame->m_pHumanView->m_pAppWindowControl->VGetSize();
		m_pOptionsScreen = IBaseControl::CreateWindowControl(optionsDef);
		pGame->m_pHumanView->m_pAppWindowControl->VAddChildControl(shared_ptr<IBaseControl>(m_pOptionsScreen));
		pGame->m_pHumanView->m_pAppWindowControl->VMoveToFront(m_pOptionsScreen);

		cCheckBoxControlDef checkboxControlDef;
		checkboxControlDef.strControlName = "cbMusic";
		checkboxControlDef.bChecked = m_pOwner->m_gameOptions.bPlayMusic;
		checkboxControlDef.buttonControlDef.strDefaultImage = "Sprites\\Unchecked.png";
		checkboxControlDef.buttonControlDef.strPressedImage = "Sprites\\Checked.png";
		checkboxControlDef.labelControlDef.strText = "Music";
		checkboxControlDef.labelControlDef.pFont = IFontManager::GetInstance()->VGetFont("licorice.fnt");
		checkboxControlDef.labelControlDef.fTextHeight = 20;
		checkboxControlDef.labelControlDef.textColor = cColor::WHITE;
		checkboxControlDef.buttonControlDef.vSize = cVector2(50, 30);
		checkboxControlDef.iSpaceCaption = 10;
		checkboxControlDef.vPosition = cVector2(0.f, 250.f);

		IBaseControl * pMusicCheckBoxControl = IBaseControl::CreateCheckBoxControl(checkboxControlDef);
		m_pOptionsScreen->VAddChildControl(shared_ptr<IBaseControl>(pMusicCheckBoxControl));
		UIEventCallBackFn musicCheckBoxCallback;
		musicCheckBoxCallback = bind(&cHumanView::MusicCheckBoxPressed, m_pOwner->m_pHumanView, _1);
		pMusicCheckBoxControl->VRegisterCallBack(UIET_BTNPRESSED, musicCheckBoxCallback);

		checkboxControlDef.strControlName = "cbSFX";
		checkboxControlDef.labelControlDef.strText = "SFX";
		checkboxControlDef.vPosition = cVector2(0.f, 300.f);
		checkboxControlDef.bChecked = m_pOwner->m_gameOptions.bPlaySfx;

		IBaseControl * pSfxCheckBoxControl = IBaseControl::CreateCheckBoxControl(checkboxControlDef);
		m_pOptionsScreen->VAddChildControl(shared_ptr<IBaseControl>(pSfxCheckBoxControl ));
		UIEventCallBackFn sfxCheckBoxCallback;
		sfxCheckBoxCallback = bind(&cHumanView::SfxCheckBoxPressed, m_pOwner->m_pHumanView, _1);
		pSfxCheckBoxControl->VRegisterCallBack(UIET_BTNPRESSED, sfxCheckBoxCallback);

		checkboxControlDef.strControlName = "cbFullscreen";
		checkboxControlDef.labelControlDef.strText = "FullScreen";
		checkboxControlDef.vPosition = cVector2(0.f, 350.f);
		checkboxControlDef.bChecked = m_pOwner->VGetGameOptions().bFullScreen;
		
		IBaseControl * pFullscreenCheckBoxControl = IBaseControl::CreateCheckBoxControl(checkboxControlDef);
		m_pOptionsScreen->VAddChildControl(shared_ptr<IBaseControl>(pFullscreenCheckBoxControl));
		UIEventCallBackFn fullScreenCheckBoxCallback;
		fullScreenCheckBoxCallback = bind(&cHumanView::FullScreenCheckBoxPressed, m_pOwner->m_pHumanView, _1);
		pFullscreenCheckBoxControl->VRegisterCallBack(UIET_BTNPRESSED, fullScreenCheckBoxCallback);

		cScrollBarControlDef hScrollBarDef;
		hScrollBarDef.strControlName = "hsbMusicVolume";
		hScrollBarDef.strBGImage = "Sprites\\ScrollBar_BG.png";
		hScrollBarDef.iMinPos = 0;
		hScrollBarDef.iMaxPos = 20;
		hScrollBarDef.iInitialThumbPosition = (m_pOwner->m_gameOptions.iMusicVolume) / 5;
		hScrollBarDef.thumbBtnDef.strDefaultImage= "Sprites\\ScrollBar_Thumb.png";
		hScrollBarDef.thumbBtnDef.strPressedImage = "Sprites\\ScrollBar_Thumb.png";
		hScrollBarDef.TopLeftArrowDef.strDefaultImage = "Sprites\\ScrollBar_Left.png";
		hScrollBarDef.TopLeftArrowDef.strPressedImage = "Sprites\\ScrollBar_Left.png";
		hScrollBarDef.BottomRightArrowDef.strDefaultImage = "Sprites\\ScrollBar_Right.png";
		hScrollBarDef.BottomRightArrowDef.strPressedImage = "Sprites\\ScrollBar_Right.png";
		hScrollBarDef.vPosition = cVector2(0.f, 400.f);
		hScrollBarDef.vSize = cVector2(200, 30);

		IBaseControl * pMusicScrollBarControl = IBaseControl::CreateHScrollBarControl(hScrollBarDef);
		m_pOptionsScreen->VAddChildControl(shared_ptr<IBaseControl>(pMusicScrollBarControl));

		UIEventCallBackFn musicScrollbarcallback;
		musicScrollbarcallback = bind(&cStateOptionsScreen::MusicScrollbarChanged, this, _1);
		pMusicScrollBarControl->VRegisterCallBack(UIET_SCBCHANGED, musicScrollbarcallback);

		cTextBoxControlDef textBoxControlDef;
		textBoxControlDef.strControlName = "tbMusicVolume";
		textBoxControlDef.strBGImage = "Sprites\\TextBox.png";
		textBoxControlDef.pFont = IFontManager::GetInstance()->VGetFont("licorice.fnt");
		textBoxControlDef.strText = cString(30, "%d", m_pOwner->m_gameOptions.iMusicVolume);
		textBoxControlDef.fTextHeight = 20;
		textBoxControlDef.textColor = cColor::BLACK;
		textBoxControlDef.strCaretImage = "Sprites\\caret.png";
		textBoxControlDef.iCaretWidth = 3;
		textBoxControlDef.fCaretUpdateTime = 0.25f;
		textBoxControlDef.vSize = cVector2(50, 30);
		textBoxControlDef.vPosition = cVector2(220, 400);

		IBaseControl * pMusicVolumeTextBoxControl = IBaseControl::CreateTextBoxControl(textBoxControlDef);
		m_pOptionsScreen->VAddChildControl(shared_ptr<IBaseControl>(pMusicVolumeTextBoxControl));

		cButtonControlDef buttonDef;
		buttonDef.bAutoSize = true;
		buttonDef.vPosition = cVector2(0, 480);
		buttonDef.strDefaultImage = "Sprites\\buttonDefault.png";
		buttonDef.strPressedImage = "Sprites\\buttonPressed.png";
		buttonDef.labelControlDef.pFont = IFontManager::GetInstance()->VGetFont("licorice.fnt");
		buttonDef.labelControlDef.strText = "Back";
		buttonDef.labelControlDef.textColor = cColor::BLUE;
		buttonDef.labelControlDef.fTextHeight = 50;

		IBaseControl * pBackButton = IBaseControl::CreateButtonControl(buttonDef);
		m_pOptionsScreen->VAddChildControl(shared_ptr<IBaseControl>(pBackButton));
		UIEventCallBackFn callBackBtn;
		callBackBtn = bind(&cStateOptionsScreen::BackButtonPressed, this, _1);
		pBackButton->VRegisterCallBack(UIET_BTNRELEASED, callBackBtn);
	}
}

// *****************************************************************************
void cStateOptionsScreen::VOnUpdate()
{

}

// *****************************************************************************
void cStateOptionsScreen::VOnExit()
{
	if (m_pOwner->m_pHumanView->m_pAppWindowControl != NULL)
	{
		m_pOwner->m_pHumanView->m_pAppWindowControl->VRemoveChildControl("OptionsScreen");
	}
}

// *****************************************************************************
bool cStateOptionsScreen::VOnMessage(const Telegram &msg)
{
	return false;
}

// *****************************************************************************
void cStateOptionsScreen::BackButtonPressed(const unUIEventCallbackParam & params)
{
	if(m_pOwner != NULL)
	{
		if(m_pOwner->m_pStateMachine != NULL)
		{
			m_pOwner->m_pStateMachine->RequestPopState();
		}
		m_pOwner->SaveGameOptions("Media//PlayerOptions.xml");
	}
}

// *****************************************************************************
void cStateOptionsScreen::MusicScrollbarChanged(const unUIEventCallbackParam & params)
{
	IBaseControl * pMusicTextBox = m_pOptionsScreen->VFindChildControl("tbMusicVolume");
	pMusicTextBox->VSetText(cString(20, "%d", params.iThumbPos * 5));
}