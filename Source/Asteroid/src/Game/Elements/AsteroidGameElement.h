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
class cAsteroid;
class cGame;

class cAsteroidGameElement
	: public GameBase::cGameElement
{
public:
	cAsteroidGameElement();
	virtual ~cAsteroidGameElement();
	void VInitialize(const GameBase::cGameElementDef & def);
	virtual void OnRestart();
	virtual void OnUpdate(float fElapsedTime);
	static void SetGame(const cGame * const pGame);
	virtual cShip * CastToShip();
	virtual cAsteroid * CastToAsteroid();

protected:
	void WrapAround(Base::cVector3 &vPredictedPos);
	void ReCalculateLookAt();

protected:
	static const cGame *	m_pGame;

	Base::cVector3			m_vInitialPos;
	float					m_fRotationPower;
	float					m_fAcceleration;
	float					m_fDragFactor;
	Base::cVector3			m_vForward;
	Base::cVector3			m_vLookAt;
	Base::cVector3			m_vVelocity;
};
#endif // AsteroidGameElement_h__