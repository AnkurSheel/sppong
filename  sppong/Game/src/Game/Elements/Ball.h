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

#include "GameElement.h"

class cBall  : public cGameElement
{
private:
	D3DXVECTOR3		m_vSpeed;

	cBall(const cBall&){}
	cBall operator = (const cBall&) {}
public:
	cBall();
	~cBall();
	void Init(const D3DXVECTOR3& vInitialPos, const UINT iTableWidth, const UINT iTableHeight);
	void Render(LPDIRECT3DDEVICE9 const pDevice, const float fElapsedTime);
	void OnResetDevice(cSprite* const sprite);
	void ChangeSpeedX();
	void ChangeSpeedY();
};
#endif // Ball_h__