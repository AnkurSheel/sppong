// ***************************************************************
//  BaseApp   version:  1.0   Ankur Sheel  date: 2011/10/19
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef BaseApp_h__
#define BaseApp_h__

#include "BaseApp.hxx"
#include "BaseEntity.h"

namespace Utilities
{
	class ITimer;
}

namespace GameBase
{
	class cHumanView;
}

namespace GameBase
{
	class cBaseApp 
		: public IBaseApp
		, public cBaseEntity
	{
	public:
		GAMEBASE_API cBaseApp(const Base::cString strName);
		virtual ~cBaseApp(){}
		GAMEBASE_API float GetFPS();

	protected:
		GAMEBASE_API virtual void VOnInitialization(const HINSTANCE hInstance, const int nCmdShow,const bool bFullScreen, const int iFullScreenWidth, const int iFullScreenHeight, HWND & outHwnd);
		GAMEBASE_API virtual void VCreateHumanView();
		GAMEBASE_API virtual void VRun();
		GAMEBASE_API virtual void VOnUpdate();
		GAMEBASE_API virtual void VOnLostDevice();
		GAMEBASE_API virtual HRESULT VOnResetDevice();
		GAMEBASE_API virtual bool VOnMsgProc(const Graphics::AppMsg & msg);
		GAMEBASE_API virtual void VRender(TICK tickCurrent, float fElapsedTime);
		GAMEBASE_API virtual void VCleanup();
		GAMEBASE_API TICK GetRunningTicks();
		GAMEBASE_API float GetRunningTime();

	protected:
		Utilities::ITimer *	m_pGameTimer;
		cHumanView *		m_pHumanView;
	};
}

#endif // BaseApp_h__