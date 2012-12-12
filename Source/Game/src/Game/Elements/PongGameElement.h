// ****************************************************************************
//  PongGameElement   version:  1.0   Ankur Sheel  date: 2011/01/21
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ****************************************************************************
// 
// ****************************************************************************
#ifndef PongGameElement_h__
#define PongGameElement_h__

#include "GameElement.h"

class cPaddle;
class cBall;
class IGame;

class cPongGameElement
	: public GameBase::cGameElement
{
public:
	cPongGameElement();
	virtual ~cPongGameElement();
	static void SetGame(const IGame * const pGame);
	virtual cPaddle * CastToPaddle();
	virtual cBall * CastToBall();
	virtual void OnUpdate(float fElapsedTime){};

protected:
	static const IGame *	m_pGame;
};

#endif // PongGameElement_h__