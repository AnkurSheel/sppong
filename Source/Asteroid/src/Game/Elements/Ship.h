// *****************************************************************************
//  Ship   version:  1.0   Ankur Sheel  date: 2013/02/21
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef Ship_h__
#define Ship_h__

#include "AsteroidGameElement.h"

namespace Base
{
	class cString;
}

class cShip 
	: public cAsteroidGameElement
{
public:
	cShip();
	~cShip();
	void VInitialize(const GameBase::cGameElementDef & def);
	void OnUpdate(float fElapsedTime);
	void MoveBack(const float fElapsedTime);
	void MoveForward(const float fElapsedTime);
	void RotateLeft(const float fElapsedTime );
	void RotateRight(const float fElapsedTime );
	void OnRestart();
	cShip * CastToShip();
};
#endif // Ship_h__