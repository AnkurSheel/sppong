// ***************************************************************
//  GameElement   version:  1.0   Ankur Sheel  date: 05/14/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef GameElement_h__
#define GameElement_h__

#include "GameBaseDefines.h"
#include "Constants.h"

class ISprite;

class cGameElement
{
public:
	GAMEBASE_API cGameElement();
	GAMEBASE_API ~cGameElement();
	GAMEBASE_API void Init(const D3DXVECTOR3& vInitialPos, const UINT iTableWidth =0 , const UINT iTableHeight=0);
	GAMEBASE_API void SetBoundingRectangle();
	GAMEBASE_API D3DRECT& GetBoundingRectangle();
	GAMEBASE_API void OnRestart(const D3DXVECTOR3& vInitialPos);
	GAMEBASE_API const D3DXVECTOR3& GetPosition();
	GAMEBASE_API void Render(LPDIRECT3DDEVICE9 const pDevice, const DWORD dwFlags = NULL, const D3DCOLOR& tint = WHITE, const RECT* pSrcRect = NULL);
	GAMEBASE_API void SetSprite(ISprite* const sprite );
	GAMEBASE_API const ISprite * GetSprite();

protected:
	ISprite*		m_pSprite;
	D3DXVECTOR3		m_vPosition;
	GAMEBASE_API static UINT		m_siTableHeight;
	GAMEBASE_API static UINT		m_siTableWidth;
	D3DRECT			m_BoundingRect;

};

#include "GameElement.inl"
#endif