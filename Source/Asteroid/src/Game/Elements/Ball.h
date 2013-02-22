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

namespace Base
{
	class cString;
}
namespace Utilities
{
	class IRandomGenerator;
}

class cBall  
	: public cAsteroidGameElement
{
public:
	cBall();
	~cBall();
	void VInitialize(const GameBase::cGameElementDef & def);
	void OnRestart();
	void Cleanup();
	void OnUpdate(float fElapsedTime);
	cBall * CastToBall();

private:
	Base::cVector3					m_vSpeed;
	Utilities::IRandomGenerator *	m_pRandomGenerator;
};
#endif // Ball_h__
