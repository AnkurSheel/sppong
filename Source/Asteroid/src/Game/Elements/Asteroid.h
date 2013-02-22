// *****************************************************************************
//  Ball   version:  1.0   Ankur Sheel  date: 05/13/2008
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef Ball_h__
#define Ball_h__

#include "AsteroidGameElement.h"

class cAsteroid  
	: public cAsteroidGameElement
{
public:
	cAsteroid();
	~cAsteroid();
	void VInitialize(const GameBase::cGameElementDef & def);
	void BaseInitialize(const GameBase::cGameElementDef & def);
	void InitializeFromParent(const GameBase::cGameElementDef & def, const int iSize);
	void RandomizeAcceleration();
	void RandomizeRotation();

	void OnRestart();
	void Cleanup();
	void Hit();
	cAsteroid * CastToAsteroid();

private:
	float		m_fMinSize;
	float		m_fSizeVariance;
	int			m_iCurrentSize;
};
#endif // Ball_h__
