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
#include "Elements/Asteroid.h"
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
#include "RandomGenerator.hxx"

using namespace MySound;
using namespace Graphics;
using namespace Base;
using namespace GameBase;
using namespace Utilities;

// *****************************************************************************
cGame::cGame(const cString strName)
: cBaseApp(strName)
, m_pStateMachine(NULL)
, m_pRandomGenerator(NULL)
, m_pHUDScreen(NULL)
{
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

	m_pRandomGenerator = IRandomGenerator::CreateRandomGenerator();
	if (m_pRandomGenerator)
	{
		Log_Write_L1(ILogger::LT_DEBUG, cString(100, "Random Generator created with seed %u", m_pRandomGenerator->GetRandomSeed()));
	}

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
	IMessageDispatchManager::GetInstance()->VOnUpdate();
}

// *****************************************************************************
void cGame::Restart()
{
	Sleep(100);
	GameElementList::iterator iter;
	for (iter = m_pGameElements.begin(); iter != m_pGameElements.end(); iter++)
    {
		(*iter)->OnRestart();
	}

	//m_ppGameElements[PGE_PADDLE_LEFT]->OnRestart();
	//m_ppGameElements[PGE_PADDLE_RIGHT]->OnRestart();
	//m_ppGameElements[PGE_BALL]->OnRestart();
}

// *****************************************************************************
void cGame::VCleanup()
{
	m_pGameElements.clear();

	SAFE_DELETE(m_pRandomGenerator);
	SAFE_DELETE(m_pStateMachine);

	cBaseApp::VCleanup();
}

void cGame::MoveShip(const ShipActions eShipActions)
{
	cShip * pShip = (m_pGameElements.front())->CastToShip();
	if(pShip)
	{
		switch(eShipActions)
		{
			case SA_MOVE_FWD:
			{
				pShip->MoveForward(m_pGameTimer->VGetDeltaTime());
				break;
			}
			case SA_MOVE_BK:
			{
				pShip->MoveBack(m_pGameTimer->VGetDeltaTime());
				break;
			}
			case SA_ROTATE_LEFT:
			{
				pShip->RotateLeft(m_pGameTimer->VGetDeltaTime());
				break;
			}
			case SA_ROTATE_RIGHT:
			{
				pShip->RotateRight(m_pGameTimer->VGetDeltaTime());
				break;
			}
			case SA_FIRE:
			{
				pShip->Fire();
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
void cGame::VGetGameElements(GameElementList & gameElements) const
{
	gameElements = m_pGameElements; 
}

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
IRandomGenerator * const cGame::GetRandomGenerator() const
{
	return m_pRandomGenerator;
}

// *****************************************************************************
void cGame::AddGameElement(shared_ptr<cAsteroidGameElement> const pGameElement)
{
	m_pGameElements.push_back(pGameElement);
}

// *****************************************************************************
void cGame::AsteroidHitByBullet(cAsteroidGameElement * const pBulletElement,
								cAsteroidGameElement * const pAsteroidElement)
{
	cBullet * pBullet = pBulletElement->CastToBullet();
	m_pGameElements.front()->CastToShip()->BulletDestroyed(pBullet);

	cAsteroid * pAsteroid = pAsteroidElement->CastToAsteroid();
	if (pAsteroid != NULL)
	{
		cShip * pShip = m_pGameElements.front()->CastToShip();
		if (pShip)
		{
			pShip->IncrementScore(pAsteroid->GetCurrentSize() * 10);
			IBaseControl * pScoreLabel = m_pHUDScreen->VFindChildControl("ScoreLabel");
			if (pScoreLabel != NULL)
			{
				pScoreLabel->VSetText(cString(20, "Score: %02d", pShip->GetScore()));
			}
		}
		pAsteroid->Hit();
	}
}

// *****************************************************************************
void cGame::ShipHitByAsteroid()
{
	cShip * pShip = (m_pGameElements.front())->CastToShip();
	pShip->MakeInactiveFor(1);
}

// *****************************************************************************
IBaseApp * IGame::CreateGame(const cString strName)
{
	return DEBUG_NEW cGame(strName);
}

