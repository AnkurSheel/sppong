// *****************************************************************************
//  Game   version:  1.0   Ankur Sheel  date: 2011/02/16
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef Game_hxx__
#define Game_hxx__

#include "GameDefines.h"

namespace GameBase
{
	class IBaseApp;
}

class cPongGameElement;

class IGame 
{
public:
	enum PONGGAMEELEMENTS
	{
		PGE_UNKNOWN = -1,
		PGE_BALL,
		PGE_PADDLE_LEFT,
		PGE_PADDLE_RIGHT,
		PGE_WALL_UP,
		PGE_WALL_DOWN,
		PGE_TOTAL
	};

public:
	GAME_API virtual ~IGame(){}
	GAME_API static GameBase::IBaseApp * CreateGame(const Base::cString strName);
	virtual cPongGameElement ** const VGetGameElements() const = 0;
};
#endif // Game_h__