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
#include <list>
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
namespace Graphics
{
	class IScreenElement;
	class IInput;
	class IFont;
	class ISprite;
	class IBaseControl;
}

namespace GameBase
{
	typedef std::list<shared_ptr<Graphics::IScreenElement> > ScreenElementList;

	class cHumanView : public IGameView
	{
	public:
		GAMEBASE_API cHumanView();
		GAMEBASE_API virtual ~cHumanView();
		GAMEBASE_API virtual void VOnCreateDevice( const HINSTANCE hInst, const HWND hWnd, int iClientWidth, int iClientHeight );
		GAMEBASE_API void VOnUpdate(const int iDeltaMilliSeconds);
		GAMEBASE_API virtual void VOnRender(TICK tickCurrent, float fElapsedTime);
		GAMEBASE_API virtual void VOnLostDevice();
		GAMEBASE_API virtual HRESULT VOnResetDevice();
		GAMEBASE_API virtual void VOnDestroyDevice();
		GAMEBASE_API virtual bool VOnMsgProc( const Graphics::AppMsg & msg );	
		GAMEBASE_API GAMEVIEWTYPE VGetType();
		GAMEBASE_API GameViewId VGetId() const;
		GAMEBASE_API void VOnAttach(GameViewId id);

		GAMEBASE_API void PushElement(shared_ptr<Graphics::IScreenElement> pScreenElement);
		GAMEBASE_API void PopElement(shared_ptr<Graphics::IScreenElement> pScreenElement);
		GAMEBASE_API void RemoveElements();
		GAMEBASE_API bool CheckZones(Base::cString & strHitZoneName );
		GAMEBASE_API void SetCursorVisible(bool bVisible);

	protected:
		void HandleLostDevice(HRESULT hr);
		GAMEBASE_API void LockKey( const DWORD dwKey );
		GAMEBASE_API HRESULT OnBeginRender(TICK tickCurrent);
		GAMEBASE_API HRESULT RenderPrivate( HRESULT & hr );
		GAMEBASE_API void OnEndRender(const HRESULT hr);

	protected:
		GameViewId						m_idView;
		Utilities::IProcessManager *	m_pProcessManager;
		TICK							m_tickCurrent;
		TICK							m_tickLastDraw;
		bool							m_bRunFullSpeed;
		ScreenElementList				m_pElementList;
		//shared_ptr<Graphics::ISprite>	m_pCursorSprite;		// the sprite for the cursor
		shared_ptr<Graphics::IFont>		m_pFont;
		bool							m_bLockedKeys[KEYBOARD_KEYS];

	public:
		Graphics::IBaseControl *		m_pParentControl;
	};
}
#endif // HumanView_h__
