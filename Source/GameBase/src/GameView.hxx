// ***************************************************************
//  GameView   version:  1.0   Ankur Sheel  date: 2011/05/02
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef GameView_hxx__
#define GameView_hxx__

namespace GameBase
{
	typedef unsigned int GameViewId;

	struct AppMsg
	{
		HWND	m_hWnd;
		UINT	m_uMsg;
		WPARAM	m_wParam;
		LPARAM	m_lParam;
	};

	class IGameView 
	{
	public:
		enum GAMEVIEWTYPE
		{
			GV_HUMAN,
			GV_REMOTE,
			GV_AI,
			GV_RECORDER,
			GV_OTHER
		};
	public:
		virtual ~IGameView() {}
		virtual HRESULT OnResetDevice() = 0;
		virtual void OnRender(TICK tickCurrent, float fElapsedTime) = 0;
		virtual void OnLostDevice() = 0;
		virtual GAMEVIEWTYPE GetType() = 0;
		virtual GameViewId GetId() const = 0;
		virtual void OnAttach(GameViewId vid) = 0;
		virtual void OnUpdate( int deltaMilliseconds ) = 0;
		virtual void OnDestroyDevice() = 0;
		virtual void OnCreateDevice( const HINSTANCE hInst, const HWND hWnd, int iClientWidth, int iClientHeight ) = 0;
	};
}
#endif // GameView_h__