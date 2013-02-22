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
#include "Vector3.h"

namespace GameBase
{
	class IBaseApp;
}

class cAsteroidGameElement;

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

	typedef std::list<shared_ptr<cAsteroidGameElement> > GameElementList;

public:
	virtual ~IGame(){}
	ASTEROID_API static GameBase::IBaseApp * CreateGame(const Base::cString strName);
	virtual void VGetGameElements(GameElementList & gameElements) const = 0;
	virtual Base::cVector3 VGetScreenTopLeftPos() const = 0;
	virtual Base::cVector3 VGetScreenBottomRightPos() const = 0;
	virtual void VRoundOver(const bool bPlayer1Won) = 0;
};
#endif // Game_h__