// ***************************************************************
//  HumanView   version:  1.0   Ankur Sheel  date: 2011/05/02
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef HumanView_h__
#define HumanView_h__

#include "GameBaseDefines.h"
#include "GameView.hxx"
#include "Structures.h"

namespace Utilities
{
	class IProcessManager;
}

namespace Base
{
	class cString;
}

namespace GameBase
{
	class cBaseApp;
}

namespace Graphics
{
	class ISprite;
	class IBaseControl;
	class ICamera;
}

namespace GameBase
{
	//typedef std::list<shared_ptr<Graphics::IScreenElement> > ScreenElementList;

	class cHumanView 
		: public IGameView
	{
	public:
		GAMEBASE_API cHumanView();
		GAMEBASE_API virtual ~cHumanView();
		GAMEBASE_API virtual void VOnCreateDevice(IBaseApp * pGame,
			const HINSTANCE & hInst, const HWND & hWnd, const int iClientWidth,
			const int iClientHeight );
		GAMEBASE_API virtual bool VOnMsgProc( const Base::AppMsg & msg );	
		GAMEBASE_API virtual void VOnRender(const TICK tickCurrent, const float fElapsedTime);
		GAMEBASE_API virtual void VOnUpdate(const TICK tickCurrent, const float fElapsedTime);
		GAMEBASE_API virtual void VOnDestroyDevice();
		GAMEBASE_API void SetCursorVisible(bool bVisible);
		GAMEBASE_API GAMEVIEWTYPE VGetType();
		GAMEBASE_API GameViewId VGetId() const;
		GAMEBASE_API const Graphics::ICamera * const VGetCamera() const;

	protected:
		GAMEBASE_API virtual void VRenderPrivate();
		GAMEBASE_API void LockKey( const DWORD dwKey );
		GAMEBASE_API void UnlockKey( const DWORD dwKey );
		GAMEBASE_API bool IsKeyLocked( const DWORD dwKey ) const;
		GAMEBASE_API HRESULT OnBeginRender(TICK tickCurrent);
		GAMEBASE_API void OnEndRender(const HRESULT hr);
		GAMEBASE_API void VOnAttach(GameViewId id);
		GAMEBASE_API bool CheckZones(Base::cString & strHitZoneName );

	protected:
		Graphics::ICamera *					m_pCamera;
		shared_ptr<Graphics::IBaseControl>	m_pFpsLabel;

	private:
		GameViewId						m_idView;
		Utilities::IProcessManager *	m_pProcessManager;
		TICK							m_tickCurrent;
		TICK							m_tickLastDraw;
		bool							m_bRunFullSpeed;
		//shared_ptr<Graphics::ISprite>	m_pCursorSprite;		// the sprite for the cursor
		bool							m_bDisplayFPS;
		bool							m_bLockedKeys[KEYBOARD_KEYS];
		GameBase::IBaseApp	*			m_pGame;

	public:
		Graphics::IBaseControl *		m_pAppWindowControl;


	};
}
#endif // HumanView_h__