// *****************************************************************************
//  AsteroidGameElement   version:  1.0   Ankur Sheel  date: 2013/02/21
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef AsteroidGameElement_h__
#define AsteroidGameElement_h__

#include "GameElement.h"

class cShip;
class cBall;
class cGame;

class cAsteroidGameElement
	: public GameBase::cGameElement
{
public:
	cAsteroidGameElement();
	virtual ~cAsteroidGameElement();
	void VInitialize(const GameBase::cGameElementDef & def);
	virtual void OnRestart();
	virtual cShip * CastToShip();
	virtual cBall * CastToBall();
	virtual void OnUpdate(float fElapsedTime){};
	static void SetGame(const cGame * const pGame);

protected:
	Base::cVector3			m_vInitialPos;
	static const cGame *	m_pGame;
};
#endif // AsteroidGameElement_h__