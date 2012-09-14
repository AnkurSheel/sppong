// ***************************************************************
//  BaseApp   version:  1.0   Ankur Sheel  date: 2011/10/19
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "BaseApp.h"
#include "MainWindow.hxx"
#include "Timer.hxx"
#include "HumanView.h"
#include "ParamLoaders.hxx"
#include "Optional.h"
#include "Checks.hxx"

using namespace GameBase;
using namespace Base;
using namespace Utilities;

IParamLoader * cBaseApp::m_spParamLoader = NULL;
cBaseApp::cBaseApp(const cString strName)
: cBaseEntity(strName)
, m_pGameTimer(NULL)
, m_pHumanView(NULL)
{
}

// ***************************************************************
void GameBase::cBaseApp::VOnInitialization(const HINSTANCE hInstance, const int nCmdShow, const cString & strOptionsFileName)
{
	if(m_spParamLoader == NULL)
	{
		m_spParamLoader = IParamLoader::CreateParamLoader();
	}
	if(!strOptionsFileName.IsEmpty())
	{
		if(m_spParamLoader != NULL)
		{
			m_spParamLoader->VLoadParametersFromFile(strOptionsFileName);
		}
	}
	bool bMultipleInstances = m_spParamLoader->VGetParameterValueAsBool("-multipleinstances", false);
	cString strTitle = m_spParamLoader->VGetParameterValueAsString("-title", "Game");
	m_strName = strTitle;
	if (bMultipleInstances)
	{
		if (!IResourceChecker::GetInstance()->IsOnlyInstance(strTitle))
		{
			PostQuitMessage(0);
			return;
		}
	}
	
	bool bFullScreen = m_spParamLoader->VGetParameterValueAsBool("-fullscreen", false);
	int iWindowWidth = m_spParamLoader->VGetParameterValueAsInt("-WindowWidth", 1024);
	int iWindowHeight = m_spParamLoader->VGetParameterValueAsInt("-WindowHeight", 720);

	HWND hwnd = IMainWindow::GetInstance()->VOnInitialization(hInstance, nCmdShow, this, bFullScreen, iWindowWidth, iWindowHeight);

	if(hwnd == NULL)
	{
		PostQuitMessage(0) ;
		return;
	}
	VCreateHumanView();
	m_pHumanView->VOnCreateDevice(this, hInstance, hwnd, iWindowWidth, iWindowHeight);
}

void GameBase::cBaseApp::VCreateHumanView()
{
	m_pHumanView = DEBUG_NEW cHumanView();
}

// ***************************************************************
// the message loop
// ***************************************************************
void GameBase::cBaseApp::VRun()
{
	MSG Msg ;

	m_pGameTimer = ITimer::CreateTimer();
	m_pGameTimer->VStartTimer();

	PeekMessage(&Msg, NULL, 0, 0, PM_NOREMOVE) ;
	// run till completed
	while (Msg.message!=WM_QUIT)
	{
		// is there a message to process?
		if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
		{
			// dispatch the message
			TranslateMessage(&Msg) ;
			DispatchMessage(&Msg) ;
		}
		else
		{
			//No message to process?
			// Then do your game stuff here
			VOnUpdate();
			VRender(m_pGameTimer->VGetRunningTicks(), m_pGameTimer->VGetDeltaTime());
		}
	}
}

void GameBase::cBaseApp::VOnUpdate()
{
	m_pGameTimer->VOnUpdate();
}

// ***************************************************************
// Deletes the memory
// ***************************************************************
void GameBase::cBaseApp::VCleanup()
{
	SAFE_DELETE(m_pGameTimer);
	SAFE_DELETE(m_spParamLoader);

	m_pHumanView->VOnDestroyDevice();
	SAFE_DELETE(m_pHumanView);


	IMainWindow::Destroy();
}

// ***************************************************************
float GameBase::cBaseApp::GetRunningTime()
{
	if(m_pGameTimer)
		return m_pGameTimer->VGetRunningTime();

	return 0.f;
}

// ***************************************************************
TICK GameBase::cBaseApp::GetRunningTicks()
{
	if(m_pGameTimer)
		return m_pGameTimer->VGetRunningTicks();

	return 0;
}

// ***************************************************************
// Display the FPS
// ***************************************************************
float GameBase::cBaseApp::GetFPS()
{
	return m_pGameTimer->VGetFPS();
}

// ***************************************************************
void GameBase::cBaseApp::VOnLostDevice()
{
	m_pHumanView->VOnLostDevice();
}

// ***************************************************************
HRESULT GameBase::cBaseApp::VOnResetDevice()
{
	return(m_pHumanView->VOnResetDevice());
}

// ***************************************************************
bool GameBase::cBaseApp::VOnMsgProc( const Base::AppMsg & msg )
{
	return m_pHumanView->VOnMsgProc(msg);
}

// ***************************************************************
// Display the Graphics
// ***************************************************************
void GameBase::cBaseApp::VRender(TICK tickCurrent, float fElapsedTime)
{
	m_pHumanView->VOnRender(tickCurrent, fElapsedTime);
}

// ***************************************************************
Utilities::IParamLoader * GameBase::cBaseApp::VGetParamLoader()
{
	return m_spParamLoader;
}

// ***************************************************************
Utilities::IParamLoader * GameBase::IBaseApp::VGetParamLoader()
{
	return cBaseApp::VGetParamLoader();
}
