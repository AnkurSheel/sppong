// *****************************************************************************
//  Game   version:  1.0   Ankur Sheel  date: 04/30/2008
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "Game.h"
#include "Sprite.hxx"
#include "Elements/Ship.h"
#include "Elements/Ball.h"
#include "Elements/Score.h"
#include "GameFlowStateMachine.h"
#include "GameFlowStates.h"
#include "AsteroidView.h"
#include "Timer.hxx"
#include "ProcessManager.hxx"
#include "MainWindow.hxx"
#include "ResourceManager.hxx"
#include "EntityManager.hxx"
#include "MessageDispatchManager.hxx"
#include "BaseControl.hxx"

using namespace MySound;
using namespace Graphics;
using namespace Base;
using namespace GameBase;
using namespace Utilities;

// *****************************************************************************
cGame::cGame(const cString strName)
: cBaseApp(strName)
, m_pScore(NULL)
, m_pStateMachine(NULL)
{
	// making sure our memory leak checker is working
#if _DEBUG
	int * p = DEBUG_NEW int();
#endif
}

// *****************************************************************************
cGame::~cGame()
{
	VCleanup();
}

// *****************************************************************************
void cGame::VOnInitialization(const HINSTANCE & hInstance, const int nCmdShow,
							  const cString & strOptionsFile)
{
	cBaseApp::VOnInitialization(hInstance, nCmdShow, strOptionsFile);

	m_iDisplayHeight = static_cast<int>(m_pHumanView->m_pAppWindowControl->VGetHeight());
	m_iDisplayWidth = static_cast<int>(m_pHumanView->m_pAppWindowControl->VGetWidth());

	m_pStateMachine = DEBUG_NEW cGameFlowStateMachine(this);

	IEntityManager::GetInstance()->VRegisterEntity(this);
	m_pStateMachine->SetCurrentState(cStateTitleScreen::Instance());
}

void cGame::VCreateHumanView()
{
	m_pHumanView = DEBUG_NEW cAsteroidView();
}

// *****************************************************************************
cString cGame::VGetGameTitle() const
{
	return VGetName();
}

// *****************************************************************************
void cGame::VOnUpdate()
{
	cBaseApp::VOnUpdate();
	m_pStateMachine->Update();
	//m_pSound->Update();
	IMessageDispatchManager::GetInstance()->VOnUpdate();
}

// *****************************************************************************
void cGame::Restart()
{
	Sleep(100);
	if(m_pShip != NULL)
	{
		m_pShip->OnRestart();
	}
	/*GameElementList::iterator iter;
	for (iter = m_pGameElements.begin(); iter != m_pGameElements.end(); iter++)
    {
		(*iter)->OnRestart();
	}*/

	//m_ppGameElements[PGE_PADDLE_LEFT]->OnRestart();
	//m_ppGameElements[PGE_PADDLE_RIGHT]->OnRestart();
	//m_ppGameElements[PGE_BALL]->OnRestart();
}

// *****************************************************************************
void cGame::VRoundOver(const bool bPlayer1Won)
{
	m_pHumanView->PlaySFX("win.wav");
	if (bPlayer1Won)
	{
		m_pScore[1].IncrementScore();
		Restart();
	}
	else
	{
		m_pScore[0].IncrementScore();
		Restart();
	}
}

// *****************************************************************************
void cGame::VCleanup()
{
	m_pShip.reset();
	//m_pGameElements.clear();

	/*if(m_ppGameElements)
	{
		for (int i=0; i<PGE_TOTAL; i++)
		{
			SAFE_DELETE(m_ppGameElements[i]);
		}
		SAFE_DELETE_ARRAY(m_ppGameElements);
	}*/

	SAFE_DELETE_ARRAY(m_pScore);
	SAFE_DELETE(m_pStateMachine);

	//SAFE_DELETE(m_pSound);

	cBaseApp::VCleanup();
}

void cGame::MoveShip(const ShipMovement eShipMovement)
{
	cShip * pShip = m_pShip->CastToShip();
	if(pShip)
	{
		switch(eShipMovement)
		{
		case SM_MOVE_FWD:
		{
			pShip->MoveForward(m_pGameTimer->VGetDeltaTime());
			break;
		}
		case SM_MOVE_BK:
		{
			pShip->MoveBack(m_pGameTimer->VGetDeltaTime());
			break;
		}
		case SM_ROTATE_LEFT:
		{
			pShip->RotateLeft(m_pGameTimer->VGetDeltaTime());
			break;
		}
		case SM_ROTATE_RIGHT:
		{
			pShip->RotateRight(m_pGameTimer->VGetDeltaTime());
			break;
		}
		}
	}
}

// *****************************************************************************
bool cGame::VOnHandleMessage(const AI::Telegram & telegram)
{
	return m_pStateMachine->HandleMessage(telegram);
}

//// *****************************************************************************
//void cGame::VGetGameElements(GameElementList & gameElements) const
//{
//	gameElements = m_pGameElements; 
//}

// *****************************************************************************
cVector3 cGame::VGetScreenTopLeftPos() const
{
	return m_vScreenTopLeftPos;
}

// *****************************************************************************
cVector3 cGame::VGetScreenBottomRightPos() const
{
	return m_vScreenBottomRightPos;
}

// *****************************************************************************
IBaseApp * IGame::CreateGame(const cString strName)
{
	return DEBUG_NEW cGame(strName);
}