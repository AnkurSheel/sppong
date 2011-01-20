// ***************************************************************
//  Ball   version:  1.0   Ankur Sheel  date: 05/13/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Ball_h__
#define Ball_h__

#include "PongGameElement.h"

class cBall  
	: public cPongGameElement
{
	cBall(const cBall&){}
	cBall operator = (const cBall&) {}
public:
	cBall();
	~cBall();
	void Init(const D3DXVECTOR3& vInitialPos, const char * const strFilename);
	void Render(LPDIRECT3DDEVICE9 const pDevice, const DWORD dwFlags = NULL, const D3DCOLOR& tint = WHITE, const RECT* pSrcRect = NULL);
	void OnResetDevice(LPDIRECT3DDEVICE9 const pDevice);
	void ChangeSpeedX();
	void ChangeSpeedY();
private:
	D3DXVECTOR3		m_vSpeed;
};
#endif // Ball_h__