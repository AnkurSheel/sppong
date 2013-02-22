// *****************************************************************************
//  Paddle   version:  1.0   Ankur Sheel  date: 05/12/2008
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef Paddle_h__
#define Paddle_h__

#include "PongGameElement.h"

namespace Base
{
	class cString;
}

class cPaddle 
	: public cPongGameElement
{
public:
	cPaddle();
	~cPaddle();
	void VInitialize(const GameBase::cGameElementDef & def );
	void MoveDown(const float fElapsedTime);
	void MoveUp(const float fElapsedTime);
	void MoveLeft( const float fElapsedTime );
	void MoveRight( const float fElapsedTime );
	cPaddle * CastToPaddle();

private:
	float			m_fMoveFactor;
};
#endif // Paddle_h__