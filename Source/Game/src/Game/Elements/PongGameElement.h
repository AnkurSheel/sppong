// ***************************************************************
//  PongGameElement   version:  1.0   Ankur Sheel  date: 2011/01/21
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef PongGameElement_h__
#define PongGameElement_h__

#include "Elements/GameElement.h"

class cPaddle;
class cBall;

class cPongGameElement
	: public GameBase::cGameElement
{
private :
	cPongGameElement(const cPongGameElement&){}
	cPongGameElement operator =(const cPongGameElement&){}
public:
	cPongGameElement();
	virtual ~cPongGameElement();
	static void SetTableHeight(UINT val);
	static void SetTableWidth(UINT val);
	virtual cPaddle * CastToPaddle();
	virtual cBall * CastToBall();
	virtual void OnUpdate(float fElapsedTime) {}
protected:
	static UINT		m_siTableHeight;
	static UINT		m_siTableWidth;
};

#endif // PongGameElement_h__