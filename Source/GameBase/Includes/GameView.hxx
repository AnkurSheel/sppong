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
	class IBaseApp;
}

namespace GameBase
{
	typedef unsigned int GameViewId;

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
		virtual void VOnCreateDevice(IBaseApp * pGame,  const HINSTANCE hInst, const HWND hWnd, int iClientWidth, int iClientHeight ) = 0;
		virtual void VOnUpdate(const TICK tickCurrent, const float fElapsedTime) = 0;
		virtual void VOnRender(const TICK tickCurrent, const float fElapsedTime) = 0;
		virtual void VOnLostDevice() = 0;
		virtual HRESULT VOnResetDevice() = 0;
		virtual void VOnDestroyDevice() = 0;
		virtual void VOnAttach(GameViewId vid) = 0;
		virtual GAMEVIEWTYPE VGetType() = 0;
		virtual GameViewId VGetId() const = 0;
	};
}
#endif // GameView_h__