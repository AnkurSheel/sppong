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

using namespace GameBase;
using namespace Base;
using namespace Utilities;

cBaseApp::cBaseApp(const cString strName)
: cBaseEntity(strName)
, m_pGameTimer(NULL)
, m_pHumanView(NULL)
{
}

// ***************************************************************
void GameBase::cBaseApp::VOnInitialization(const HINSTANCE hInstance, 
														const int nCmdShow,
														const bool bFullScreen,
														const int iFullScreenWidth,
														const int iFullScreenHeight,
														HWND & outHwnd)
{
	outHwnd = IMainWindow::GetInstance()->VOnInitialization(hInstance, nCmdShow, this, bFullScreen, iFullScreenWidth, iFullScreenHeight);

	if(outHwnd == NULL)
	{
		PostQuitMessage(0) ;
		return;
	}
	VCreateHumanView();
	m_pHumanView->VOnCreateDevice(this, hInstance, outHwnd, iFullScreenWidth, iFullScreenHeight);
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
bool GameBase::cBaseApp::VOnMsgProc( const Graphics::AppMsg & msg )
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

