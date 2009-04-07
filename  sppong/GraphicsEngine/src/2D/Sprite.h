// ***************************************************************
//  Sprite   version:  1.0   Ankur Sheel  date: 05/09/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Sprite_h__
#define Sprite_h__

#include "GraphicEngineDefines.h"
#include "Constants.h"

class cSprite
{
private:

	LPD3DXSPRITE		m_pSprite;		// ptr to the sprite 
	LPDIRECT3DTEXTURE9	m_pTexture;		// the texture associated with this sprite
	UINT				m_uiHeight;		// the height of the image
	UINT				m_uiWidth;		// the width of the image
	D3DXVECTOR3			m_vScale ;		// the scaling info for the image
	D3DXVECTOR3			m_vPosition ;	// the scaling info for the image
	D3DXMATRIX			m_mScaleMatrix;	// the scaling matrix
	cSprite(const cSprite&){}
	cSprite operator =(const cSprite&){}

public:
	GRAPHIC_API cSprite();
	GRAPHIC_API ~cSprite();
	GRAPHIC_API void Init(LPDIRECT3DDEVICE9 const pDevice, const char  * const  strFilename) ;
	GRAPHIC_API void SetSize(const float fNewWidth, const float fNewHeight);
	GRAPHIC_API void DrawSprite(LPDIRECT3DDEVICE9 const pDevice, const D3DXVECTOR3& vPosition, const DWORD dwFlags = NULL, const D3DCOLOR& tint = WHITE, const RECT* pSrcRect = NULL);
	GRAPHIC_API void Cleanup();
	GRAPHIC_API UINT GetScaledHeight();
	GRAPHIC_API UINT GetScaledWidth();
	GRAPHIC_API D3DXVECTOR3 GetPosition();
};
#include "Sprite.inl"

#endif // Sprite_h__