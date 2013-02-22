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
	void OnRestart();
	void Cleanup();
	cAsteroid * CastToAsteroid();

private:
	float		m_fMinSize;
	float		m_fSizeVariance;
};
#endif // Ball_h__
