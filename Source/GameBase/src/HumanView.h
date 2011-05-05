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
#include <list>

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
	class IFPS;
	class IMouseZone;
	class ISprite;
}

namespace GameBase
{
	typedef std::list<Graphics::IScreenElement *> ScreenElementList;

	class cHumanView : public IGameView
	{
	public:
		GAMEBASE_API cHumanView();
		GAMEBASE_API virtual ~cHumanView();
		GAMEBASE_API virtual HRESULT OnResetDevice();
		GAMEBASE_API virtual void OnRender(TICK tickCurrent, float fElapsedTime);
		GAMEBASE_API virtual void OnLostDevice();
		GAMEBASE_API virtual void OnCreateDevice( const HINSTANCE hInst, const HWND hWnd, int iClientWidth, int iClientHeight );
		GAMEBASE_API virtual void OnDestroyDevice();
		GAMEBASE_API GAMEVIEWTYPE GetType();
		GAMEBASE_API GameViewId GetId() const;
		GAMEBASE_API virtual void OnAttach(GameViewId id);
		GAMEBASE_API virtual void PushElement(Graphics::IScreenElement * pScreenElement, const Base::cString & strZoneName);
		GAMEBASE_API virtual void PopElement(Graphics::IScreenElement * pScreenElement);
		GAMEBASE_API virtual void RemoveElements();
		GAMEBASE_API virtual void FreeZones();
		GAMEBASE_API void OnUpdate(float fElapsedTime);
		GAMEBASE_API bool CheckZones(Base::cString & strHitZoneName );
		GAMEBASE_API void SetCursorVisible(bool bVisible);

	protected:
		void RenderText();
		void HandleLostDevice(HRESULT hr);
		void GetInput()  const;
		void LockKey( const DWORD dwKey );
		GAMEBASE_API HRESULT OnBeginRender(TICK tickCurrent);
		GAMEBASE_API void OnEndRender(const HRESULT hr);
		GAMEBASE_API HRESULT RenderPrivate( HRESULT & hr );


	protected:
		GameViewId						m_idView;
		Utilities::IProcessManager *	m_pProcessManager;
		TICK							m_tickCurrent;
		TICK							m_tickLastDraw;
		bool							m_bRunFullSpeed;
		ScreenElementList				m_pElementList;
		Graphics::IInput *				m_pInput;				// pointer to input class
		Graphics::ISprite  *			m_pCursorSprite;		// the sprite for the cursor
		Graphics::IMouseZone *			m_pMouseZones;
		Graphics::IFPS *				m_pFPS;
	};
}
#endif // HumanView_h__
