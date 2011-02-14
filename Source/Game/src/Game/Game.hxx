// ***************************************************************
//  Game   version:  1.0   ·  date: 04/30/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Game_hxx__
#define Game_hxx__

#include "GameDefines.h"

class IGame 
{
public:
	GAME_API virtual ~IGame(){}
	GAME_API virtual void Render() = 0;
	GAME_API virtual void OnResetDevice() = 0;
	GAME_API virtual void OnLostDevice() = 0;
	GAME_API virtual void OnInit(LPDIRECT3DDEVICE9 const pDevice, const UINT iDisplayHeight, const UINT iDisplayWidth) = 0;
	GAME_API virtual void ProcessInput(const long xDelta,const long yDelta, const long zDelta, const bool* const pbPressedKeys, const bool* const pbMouseButtons, const float fElapsedTime ) = 0;
	GAME_API virtual void Cleanup() = 0;
	GAME_API virtual void Restart() = 0;
	GAME_API virtual void CheckForWin() = 0;
	GAME_API virtual void CheckForCollisions() = 0;
	GAME_API static IGame * CreateGame();
};
#endif // Game_h__