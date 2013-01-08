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
#include "EntityManager.hxx"
#include "MessageDispatchManager.hxx"
#include "ResourceManager.hxx"
#include "GraphicsClass.hxx"

using namespace GameBase;
using namespace Base;
using namespace Utilities;
using namespace Graphics;
using namespace std;

IParamLoader * cBaseApp::m_spParamLoader = NULL;
cBaseApp::cBaseApp(const cString strName)
: cBaseEntity(strName)
, m_pGameTimer(NULL)
, m_pHumanView(NULL)
{
}

// ***************************************************************
void cBaseApp::VOnInitialization(const HINSTANCE & hInstance,
										   const int nCmdShow)
{
	ILogger::GetInstance()->StartConsoleWin(80,60, "");
	
	if(!IResourceChecker::GetInstance()->CheckMemory(32, 64) 
		|| !IResourceChecker::GetInstance()->CheckHardDisk(6) 
		|| !IResourceChecker::GetInstance()->CheckCPUSpeedinMhz(266))
	{
		PostQuitMessage(0);
	}
	
	ILogger::GetInstance()->CreateHeader();

	IResourceChecker::Destroy();

	cString strOptionsFileName;
#ifdef _DEBUG
	strOptionsFileName = "Debug\\OptionsDebug.ini";
#else
	strOptionsFileName = "OptionsRetail.ini";
#endif

	if(m_spParamLoader == NULL)
	{
		m_spParamLoader = IParamLoader::CreateParamLoader();
		m_spParamLoader->VLoadParametersFromFile(strOptionsFileName);
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

	vector<int> vBGColor;
	if(IBaseApp::VGetParamLoader() != NULL)
	{
		IBaseApp::VGetParamLoader()->VGetParameterValueAsIntList("-BackGroundColor", vBGColor);
	}
	cColor bgColor = cColor::BLACK;
	if(!vBGColor.empty() && vBGColor.size() == 4)
	{
		bgColor = cColor(vBGColor[0], vBGColor[1], vBGColor[2], vBGColor[3]);
	}
	bool bVSyncEnabled = false;
	if(IBaseApp::VGetParamLoader() != NULL)
	{
		bVSyncEnabled = IBaseApp::VGetParamLoader()->VGetParameterValueAsBool("-VSyncEnabled", false);
	}

	float fScreenFar = 1000.0f;
	if(IBaseApp::VGetParamLoader() != NULL)
	{
		fScreenFar = IBaseApp::VGetParamLoader()->VGetParameterValueAsFloat("-ScreenFar", 1000.0f);
	}

	float fScreenNear = 0.1f;
	if(IBaseApp::VGetParamLoader() != NULL)
	{
		fScreenNear = IBaseApp::VGetParamLoader()->VGetParameterValueAsFloat("-ScreenNear", 0.1f);
	}

	IGraphicsClass::GetInstance()->VInitialize(hwnd, bgColor, bFullScreen, 
		bVSyncEnabled, iWindowWidth, iWindowHeight, fScreenFar, fScreenNear );

	// initialize resource manager
	IResourceManager::GetInstance()->VInitialize("Media\\resources.zip ");

	VCreateHumanView();
	m_pHumanView->VOnCreateDevice(this, hInstance, hwnd, iWindowWidth, iWindowHeight);
}

void cBaseApp::VCreateHumanView()
{
	m_pHumanView = DEBUG_NEW cHumanView();
}

// ***************************************************************
// the message loop
// ***************************************************************
void cBaseApp::VRun()
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

void cBaseApp::VOnUpdate()
{
	m_pGameTimer->VOnUpdate();
	m_pHumanView->VOnUpdate(m_pGameTimer->VGetRunningTicks(), m_pGameTimer->VGetDeltaTime());
}

// ***************************************************************
// Deletes the memory
// ***************************************************************
void cBaseApp::VCleanup()
{
	SAFE_DELETE(m_pGameTimer);
	SAFE_DELETE(m_spParamLoader);

	m_pHumanView->VOnDestroyDevice();
	SAFE_DELETE(m_pHumanView);

	IEntityManager::Destroy();
	IMessageDispatchManager::Destroy();
	IGraphicsClass::Destroy();
	IResourceManager::Destroy();
	IMainWindow::Destroy();
	
	ILogger::Destroy();
}

// ***************************************************************
float cBaseApp::GetRunningTime()
{
	if(m_pGameTimer)
		return m_pGameTimer->VGetRunningTime();

	return 0.f;
}

// ***************************************************************
TICK cBaseApp::GetRunningTicks()
{
	if(m_pGameTimer)
		return m_pGameTimer->VGetRunningTicks();

	return 0;
}

// ***************************************************************
// Display the FPS
// ***************************************************************
float cBaseApp::VGetFPS()
{
	return m_pGameTimer->VGetFPS();
}

// ***************************************************************
bool cBaseApp::VOnMsgProc( const Base::AppMsg & msg )
{
	return m_pHumanView->VOnMsgProc(msg);
}

// ***************************************************************
// Display the Graphics
// ***************************************************************
void cBaseApp::VRender(TICK tickCurrent, float fElapsedTime)
{
	m_pHumanView->VOnRender(tickCurrent, fElapsedTime);
}

// ***************************************************************
cHumanView * const cBaseApp::VGetHumanView() const
{
	return m_pHumanView;
}

// ***************************************************************
Utilities::IParamLoader * cBaseApp::VGetParamLoader()
{
	return m_spParamLoader;
}

// ***************************************************************
Utilities::IParamLoader * IBaseApp::VGetParamLoader()
{
	return cBaseApp::VGetParamLoader();
}