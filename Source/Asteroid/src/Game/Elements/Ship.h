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

class cShip 
	: public cAsteroidGameElement
{
	typedef std::vector<shared_ptr<cBullet>	>  BulletList;

public:
	cShip();
	~cShip();
	void VInitialize(const GameBase::cGameElementDef & def);
	void OnUpdate(float fElapsedTime);
	void MoveBack(const float fElapsedTime);
	void MoveForward(const float fElapsedTime);
	void RotateLeft(const float fElapsedTime);
	void RotateRight(const float fElapsedTime);
	void Fire();
	void OnRestart();
	cShip * CastToShip();
	void Cleanup();
	void BulletDestroyed(cBullet * const pBullet);
	void IncrementScore(const int iValue);
	int GetScore() const;

private:
	int			m_iMaxNumberOfBullets;
	BulletList	m_Bullets;
	int			m_iActiveBullets;
	float		m_fBulletCountDown;
	float		m_fLastBulletTime;
	int			m_iScore;
};
#endif // Ship_h__