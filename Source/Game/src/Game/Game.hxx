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
#include "Essentials/BaseApp.hxx"

class IGame 
	: public Graphics::IBaseApp
{
public:
	GAME_API virtual ~IGame(){}
	GAME_API virtual void Cleanup() = 0;
	GAME_API virtual void CheckForWin() = 0;
	GAME_API virtual void CheckForCollisions() = 0;
	GAME_API static IGame * CreateGame();
};
#endif // Game_h__