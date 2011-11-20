// ***************************************************************
//  Game   version:  1.0   Ankur Sheel  date: 2011/02/16
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

namespace GameBase
{
	class IBaseApp;
}

class IGame 
{
public:
	GAME_API virtual ~IGame(){}
	GAME_API static GameBase::IBaseApp * CreateGame();

};
#endif // Game_h__