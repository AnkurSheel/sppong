// *****************************************************************************
//  HumanView   version:  1.0   Ankur Sheel  date: 2011/05/02
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "HumanView.h"
#include "GraphicsClass.hxx"
#include "ProcessManager.hxx"
#include "BaseApp.hxx"
#include "BaseControl.hxx"
#include "MainWindow.hxx"
#include "Camera.hxx"
#include "ParamLoaders.hxx"
#include "Audio.hxx"
#include "SoundProcess.hxx"
#include "GameOptions.h"
#include "GameDirectories.h"

using namespace Utilities;
using namespace Graphics;
using namespace Base;
using namespace GameBase;
using namespace Sound;

// *****************************************************************************
cHumanView::cHumanView()
: m_bRunFullSpeed(true)
, m_pProcessManager(NULL)
, m_pAppWindowControl(NULL) 
, m_pCamera(NULL)
, m_bDisplayFPS(false)
, m_hashSFXChannel("SFXChannelProcess")
, m_hashMusicChannel("MusicChannelProcess")
{
	memset(m_bLockedKeys, 0, sizeof(m_bLockedKeys));
}

// *****************************************************************************
cHumanView::~cHumanView()
{
	VOnDestroyDevice();
}

// *****************************************************************************
void cHumanView::VOnCreateDevice(IBaseApp * pGame, const HINSTANCE & hInst, 
								 const HWND & hWnd)
{
	m_pGame = pGame;
	m_pProcessManager = IProcessManager::CreateProcessManager();
	if(m_pGame->VGetParamLoader() != NULL)
	{
		m_bDisplayFPS = m_pGame->VGetParamLoader()->VGetParameterValueAsBool("-DisplayFPS", false);
	}
	cWindowControlDef def;
	def.wType = cWindowControlDef::WT_DESKTOP;
	def.strControlName = "App";
	def.vSize = cVector2(static_cast<float>(cGameOptions::GameOptions().iWidth), static_cast<float>(cGameOptions::GameOptions().iHeight));
	if(m_pGame->VGetParamLoader() != NULL)
	{
		def.bAllowMovingControls = m_pGame->VGetParamLoader()->VGetParameterValueAsBool("-AllowMovingControls", false);
	}
	m_pAppWindowControl = IBaseControl::CreateWindowControl(def);
	m_pCamera = ICamera::CreateCamera();

// 	m_pCursorSprite = ISprite::CreateSprite();
// 	m_pCursorSprite->Init(IDXBase::GetInstance()->VGetDevice(), 
// 		"cursor.png");
// 	m_pCursorSprite->SetSize((float)iClientWidth/30, (float)iClientHeight/30);
// 	m_pCursorSprite->SetFlags(D3DXSPRITE_ALPHABLEND);

	cLabelControlDef fpsLabelDef;
	fpsLabelDef.strControlName = "FPSLabel";
	fpsLabelDef.strFont= "arial"; 
	fpsLabelDef.textColor = cColor::WHITE;
	fpsLabelDef.fTextHeight = 30;
	fpsLabelDef.vPosition = cVector2(static_cast<float>(cGameOptions::GameOptions().iWidth/2- 75), 0.0f);
	fpsLabelDef.bAutoSize = false;
	fpsLabelDef.vSize = cVector2(150, 30);
	m_pFpsLabel = shared_ptr<IBaseControl>(IBaseControl::CreateLabelControl(fpsLabelDef));
	m_pAppWindowControl->VAddChildControl(m_pFpsLabel);

	IAudio::GetInstance()->VInitialize(hWnd);
}

// *****************************************************************************
void cHumanView::VOnUpdate(const TICK tickCurrent, const float fElapsedTime)
{
	if(m_pProcessManager)
	{
		m_pProcessManager->UpdateProcesses(tickCurrent);
	}
	if (m_pCamera)
	{
		m_pCamera->VUpdate();
	}
}

// *****************************************************************************
void cHumanView::VOnRender(const TICK tickCurrent, const float fElapsedTime)
{
	HRESULT hr;
	hr = OnBeginRender(tickCurrent);
	if(SUCCEEDED(hr))
	{
		VRenderPrivate();
		OnEndRender(hr);
	}
}

// *****************************************************************************
void cHumanView::VOnDestroyDevice()
{
	SAFE_DELETE(m_pAppWindowControl);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pProcessManager);
	IAudio::Destroy();
	//SAFE_DELETE(m_pCursorSprite);
}

// *****************************************************************************
bool cHumanView::VOnMsgProc( const Base::AppMsg & msg )
{
	bool bHandled = false;
	switch(msg.m_uMsg)
	{
	case WM_CHAR:
		if (m_pAppWindowControl)
		{
			bHandled = m_pAppWindowControl->VPostMsg(msg);
		}
		//if(!bHandled)
		//{
		//	switch (msg.m_wParam)
		//	{ 
		//	case VK_SPACE:
		//		IMainWindow::GetInstance()->VToggleFullScreen();
		//		Log_Write_L3(ILogger::LT_DEBUG, "Toggled FullScreen");
		//	}
		//}
		break;
	case WM_MOUSEMOVE:
	case WM_LBUTTONUP:
	case WM_LBUTTONDOWN:
	case WM_KEYUP:
	case WM_KEYDOWN:
		if (m_pAppWindowControl)
		{
			bHandled = m_pAppWindowControl->VPostMsg(msg);
		}
		if (msg.m_wParam == VK_F2 && !IsKeyLocked(VK_F2) )
		{
			// lock the F2 key
			LockKey(VK_F2);
			m_bDisplayFPS = !m_bDisplayFPS;
			if(m_pFpsLabel)
			{
				m_pFpsLabel->VSetVisible(m_bDisplayFPS);
			}
		}
		break;
	}
	return bHandled;
}

// *****************************************************************************
IGameView::GAMEVIEWTYPE cHumanView::VGetType()
{
	return GV_HUMAN;
}

// *****************************************************************************
GameViewId cHumanView::VGetId() const
{
	return -1;
}

// *****************************************************************************
void cHumanView::VOnAttach(GameViewId id)
{
	m_idView = id;
}

const ICamera * const cHumanView::GetCamera() const
{
	return m_pCamera;
}

// *****************************************************************************
HRESULT cHumanView::OnBeginRender(TICK tickCurrent)
{
	m_tickCurrent = tickCurrent; 
	HRESULT hr = S_OK;
	IGraphicsClass::GetInstance()->VBeginRender();
	return hr;
}

// *****************************************************************************
void cHumanView::VRenderPrivate()
{
	if (m_pAppWindowControl)
	{
		m_pAppWindowControl->VRender(m_pCamera);
	}

// 		if (m_pCursorSprite->IsVisible())
// 		{
// 			m_pCursorSprite->SetPosition(D3DXVECTOR3((float)m_pInput->GetX(), (float)m_pInput->GetY(), 0.0f));
// 			m_pCursorSprite->OnRender(IDXBase::GetInstance()->VGetDevice());
// 		}
	if (m_bDisplayFPS && m_pFpsLabel && m_pGame)
	{
		m_pFpsLabel->VSetText(cString(20, "%0.2f", m_pGame->VGetFPS()));
	}
}

// *****************************************************************************
void cHumanView::OnEndRender(const HRESULT hr)
{
	m_tickLastDraw = m_tickCurrent; 
	IGraphicsClass::GetInstance()->VEndRender();
}

bool cHumanView::IsKeyLocked( const DWORD dwKey )  const
{
	return m_bLockedKeys[dwKey];
}

// *****************************************************************************
// Locks the key on the keyboard
// *****************************************************************************
void cHumanView::LockKey( const DWORD dwKey ) 
{
	m_bLockedKeys[dwKey] = true;
}

void cHumanView::UnlockKey( const DWORD dwKey ) 
{
	m_bLockedKeys[dwKey] = false;
}

// *****************************************************************************
void cHumanView::SetCursorVisible( bool bVisible )
{
// 	if (m_pCursorSprite)
// 	{
// 		m_pCursorSprite->SetVisible(bVisible);
// 	}
}

// *******************************************************************************************
void cHumanView::PlaySFX(const cString & strSoundFile)
{
	if(cGameOptions::GameOptions().bPlaySfx)
	{
		shared_ptr<ISoundProcess> pSFXChannelProcess(ISoundProcess::CreateSoundProcess(m_hashSFXChannel,
			cGameDirectories::GameDirectories().strSoundDirectory + strSoundFile, 100, false));
		m_pProcessManager->VAttachProcess(pSFXChannelProcess);
	}
}

// *******************************************************************************************
void cHumanView::PlayMusic(const cString & strMusicFile, const bool bLooping)
{
	shared_ptr<ISoundProcess> pMusicChannelProcess = ISoundProcess::CreateSoundProcess(m_hashMusicChannel,
		cGameDirectories::GameDirectories().strSoundDirectory + strMusicFile, 100, bLooping);
	m_pProcessManager->VAttachProcess(pMusicChannelProcess);
	m_pProcessManager->VSetProcessesActive(m_hashMusicChannel, cGameOptions::GameOptions().bPlayMusic);
}

// *******************************************************************************************
void cHumanView::MusicCheckBoxPressed(const unUIEventCallbackParam & params)
{
	cGameOptions::GameOptions().bPlayMusic = params.bChecked;
	m_pProcessManager->VSetProcessesActive(m_hashMusicChannel, cGameOptions::GameOptions().bPlayMusic);
}

// *******************************************************************************************
void cHumanView::SfxCheckBoxPressed(const unUIEventCallbackParam & params)
{
	cGameOptions::GameOptions().bPlaySfx = params.bChecked;
	m_pProcessManager->VSetProcessesActive(m_hashSFXChannel, cGameOptions::GameOptions().bPlaySfx);
}

// *******************************************************************************************
void cHumanView::FullScreenCheckBoxPressed(const unUIEventCallbackParam & params)
{
	IMainWindow::GetInstance()->VToggleFullScreen();
}
