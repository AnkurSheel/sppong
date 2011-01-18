// ***************************************************************
//  GameElement   version:  1.0   Ankur Sheel  date: 05/14/2008
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
#include "Constants.h"

class cPongGameElement
	: public cGameElement
{
private :
	cPongGameElement(const cPongGameElement&){}
	cPongGameElement operator =(const cPongGameElement&){}
public:
	cPongGameElement();
	~cPongGameElement();
	void OnRestart(const D3DXVECTOR3& vInitialPos);
	static void SetTableHeight(UINT val);
	static void SetTableWidth(UINT val);

protected:
	static UINT		m_siTableHeight;
	static UINT		m_siTableWidth;
};

#endif