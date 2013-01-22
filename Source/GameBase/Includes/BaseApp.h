// *****************************************************************************
//  BaseApp   version:  1.0   Ankur Sheel  date: 2011/10/19
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef BaseApp_h__
#define BaseApp_h__

#include "BaseApp.hxx"
#include "BaseEntity.h"
#include "GameOptions.h"
#include "GameDirectories.h"

namespace Utilities
{
	class ITimer;
	class IParamLoader;
}

namespace GameBase
{
	class cHumanView;
	class cGameOptions;
}

namespace GameBase
{
	class cBaseApp 
		: public IBaseApp
		, public cBaseEntity
	{
	public:
		virtual ~cBaseApp(){}
		GAMEBASE_API virtual cHumanView * const VGetHumanView() const;

	protected:
		GAMEBASE_API cBaseApp(const Base::cString strName);
		GAMEBASE_API virtual void VOnInitialization(const HINSTANCE & hInstance,
			const int nCmdShow, const Base::cString & strOptionsFile);
		GAMEBASE_API virtual void VCreateHumanView();
		GAMEBASE_API virtual void VRun();
		GAMEBASE_API virtual void VOnUpdate();
		GAMEBASE_API virtual bool VOnMsgProc(const Base::AppMsg & msg);
		GAMEBASE_API virtual void VRender(TICK tickCurrent, float fElapsedTime);
		GAMEBASE_API virtual void VCleanup();
		GAMEBASE_API stGameOptions & VGetGameOptions();
		GAMEBASE_API stGameDirectories & VGetGameDirectories();
		
		TICK GetRunningTicks();
		float GetRunningTime();
		GAMEBASE_API void SaveGameOptions(const Base::cString & strPlayerOptionsFile);

	private:
		GAMEBASE_API Utilities::IParamLoader * VGetParamLoader() const;
		GAMEBASE_API float VGetFPS() const;
		void InitializeGameOptions(const Base::cString & strPlayerOptionsFile);
		void InitializeGameDirectories();

	protected:
		Utilities::ITimer *					m_pGameTimer;
		cHumanView *						m_pHumanView;
		Utilities::IParamLoader *			m_pParamLoader;
		stGameOptions 						m_gameOptions;
		stGameDirectories					m_gameDirectories;
	};
}

#endif // BaseApp_h__