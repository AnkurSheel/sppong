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
	class IParamLoader;
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
		virtual ~cBaseApp(){}
		static Utilities::IParamLoader * VGetParamLoader();
		GAMEBASE_API virtual cHumanView * const VGetHumanView() const;

	protected:
		GAMEBASE_API cBaseApp(const Base::cString strName);
		GAMEBASE_API virtual void VOnInitialization(const HINSTANCE & hInstance,
			const int nCmdShow);
		GAMEBASE_API virtual void VCreateHumanView();
		GAMEBASE_API virtual void VRun();
		GAMEBASE_API virtual void VOnUpdate();
		GAMEBASE_API virtual bool VOnMsgProc(const Base::AppMsg & msg);
		GAMEBASE_API virtual void VRender(TICK tickCurrent, float fElapsedTime);
		GAMEBASE_API float VGetFPS();
		GAMEBASE_API virtual void VCleanup();
		
		TICK GetRunningTicks();
		float GetRunningTime();

	protected:
		Utilities::ITimer *					m_pGameTimer;
		cHumanView *						m_pHumanView;
		static Utilities::IParamLoader *	m_spParamLoader;
	};
}

#endif // BaseApp_h__