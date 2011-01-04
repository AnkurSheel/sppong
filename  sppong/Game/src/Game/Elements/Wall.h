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

#include "Elements/GameElement.h"

class cSprite;

class cWall 
	: public cGameElement
{
private:
	cWall(const cWall&){}
	cWall operator =(const cWall&){}
public:
	cWall();
	~cWall();
	void Init(const D3DXVECTOR3& vPosition);
	void Render(LPDIRECT3DDEVICE9 const pDevice);
	void OnResetDevice(ISprite* const sprite);
};
#endif // Wall_h__