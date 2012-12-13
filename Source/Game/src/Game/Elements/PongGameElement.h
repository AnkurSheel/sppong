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
	void VInitialize(const GameBase::cGameElementDef & def);
	void OnRestart();
	virtual cPaddle * CastToPaddle();
	virtual cBall * CastToBall();
	virtual void OnUpdate(float fElapsedTime){};
	static void SetGame(const IGame * const pGame);

protected:
	Base::cVector3			m_vInitialPos;
	static const IGame *	m_pGame;
};

#endif // PongGameElement_h__