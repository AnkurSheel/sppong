// ***************************************************************
//  Paddle   version:  1.0   Ankur Sheel  date: 05/12/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Paddle_h__
#define Paddle_h__

#include "Elements/GameElement.h"

class cPaddle 
	: public cGameElement
{
private:
	cPaddle(const cPaddle&){}
	cPaddle operator = (const cPaddle&) {}
public:
	cPaddle();
	~cPaddle();
	void Init(const D3DXVECTOR3& vInitialPos);
	void Render(LPDIRECT3DDEVICE9 const pDevice);
	void OnResetDevice(ISprite* const sprite);
	void MoveDown(const float fElapsedTime);
	void MoveUp(const float fElapsedTime);
	void OnRestart(const D3DXVECTOR3& vInitialPos);
	void MoveLeft( const float fElapsedTime );
	void MoveRight( const float fElapsedTime );
private:
	UINT			m_iMoveFactor;
};
#endif // Paddle_h__