// ***************************************************************
//  Wall   version:  1.0   Ankur Sheel  date: 05/15/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
//***************************************************************
#ifndef Wall_h__
#define Wall_h__

#include "PongGameElement.h"

class cSprite;

class cWall 
	: public cPongGameElement
{
private:
	cWall(const cWall&){}
	cWall operator =(const cWall&){}
public:
	cWall();
	~cWall();
	void Init(const D3DXVECTOR3& vPosition, const char * const strFilename);
	void Render(LPDIRECT3DDEVICE9 const pDevice, const DWORD dwFlags = NULL, const D3DCOLOR& tint = WHITE, const RECT* pSrcRect = NULL);
	void OnResetDevice(LPDIRECT3DDEVICE9 const pDevice);
};
#endif // Wall_h__