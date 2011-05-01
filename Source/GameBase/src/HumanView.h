#pragma once

#include "GameBaseDefines.h"
#include "GameView.hxx"

namespace Utilities
{
	class IProcessManager;
}

namespace Graphics
{
	class IFont;
	class ISprite;
	class IInput;
	class IFPS;
}

namespace GameBase
{
	class cHumanView : public IGameView
	{
	public:
		GAMEBASE_API cHumanView();
		GAMEBASE_API virtual ~cHumanView();
		GAMEBASE_API virtual HRESULT OnResetDevice();
		virtual void OnRender(float fTime, float fElapsedTime);
		GAMEBASE_API virtual void OnLostDevice();
		GAMEBASE_API virtual void OnCreateDevice( const HINSTANCE hInst, const HWND hWnd, int iClientWidth, int iClientHeight );
		GAMEBASE_API virtual void OnDestroyDevice();
		GAMEBASE_API GAMEVIEWTYPE GetType();
		GAMEBASE_API GameViewId GetId() const;
		GAMEBASE_API virtual void OnAttach(GameViewId id);

		virtual void OnUpdate( int deltaMilliseconds );

	protected:
		void RenderText();
		void HandleLostDevice(HRESULT hr);
		void GetInput()  const;
		GAMEBASE_API HRESULT OnBeginRender(TICK tickCurrent);
		GAMEBASE_API void OnEndRender(const HRESULT hr);


	protected:
		GameViewId						m_idView;
		Utilities::IProcessManager *	m_pProcessManager;
		TICK							m_tickCurrent;
		TICK							m_tickLastDraw;
		bool							m_bRunFullSpeed;
		//IFont *							m_pFont;
		//ISprite *						m_pTextSprite;
		//GameBase::IBaseApp *						m_pGameApp;				// pointer to the game app
		//Graphics::IInput *				m_pInput;				// pointer to input class
		//Graphics::IFPS *				m_pFPS;
	};
}
