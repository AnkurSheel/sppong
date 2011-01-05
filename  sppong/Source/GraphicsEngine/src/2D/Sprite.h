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

class ISprite
{
public:
	GRAPHIC_API virtual void Init(LPDIRECT3DDEVICE9 const pDevice, const char  * const  strFilename) = 0;
	GRAPHIC_API virtual void SetSize(const float fNewWidth, const float fNewHeight) = 0;
	GRAPHIC_API virtual void DrawSprite(LPDIRECT3DDEVICE9 const pDevice, const D3DXVECTOR3& vPosition, const DWORD dwFlags = NULL, const D3DCOLOR& tint = WHITE, const RECT* pSrcRect = NULL) = 0;
	GRAPHIC_API virtual void Cleanup() = 0;
	GRAPHIC_API virtual UINT GetScaledHeight() const = 0;
	GRAPHIC_API virtual UINT GetScaledWidth() const = 0;
	GRAPHIC_API virtual D3DXVECTOR3 GetPosition() const = 0;
	GRAPHIC_API static ISprite * CreateSprite();
};
#endif // Sprite_h__