// ***************************************************************
//  Sprite   version:  1.0   Ankur Sheel  date: 2011/02/16
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Sprite_hxx__
#define Sprite_hxx__

#include "GraphicEngineDefines.h"
#include "Constants.h"
#include "ScreenElement.hxx"

namespace Base
{
	class cString;
}

namespace Graphics
{
	class ITexture;
}

namespace Graphics
{
	class ISprite
		: public IScreenElement
	{
	public:
		virtual ~ISprite(){}
		virtual void Init(LPDIRECT3DDEVICE9 const pDevice, shared_ptr<ITexture> const pTexture) = 0;
		virtual void Init(LPDIRECT3DDEVICE9 const pDevice, const Base::cString & strFilename) = 0;
		virtual void SetSize(const float fNewWidth, const float fNewHeight) = 0;
		virtual UINT GetScaledHeight() const = 0;
		virtual UINT GetScaledWidth() const = 0;
		virtual D3DXVECTOR3 GetPosition() const = 0;
		virtual void SetPosition(const D3DXVECTOR3& vPosition) = 0;
		virtual void SetFlags(const DWORD dwFlags) = 0;
		virtual void SetTintColor(const D3DCOLOR & tintColor) = 0;
		virtual void SetSourceRect(const RECT &	pSrcRect) = 0;
		virtual void SetTexture( shared_ptr<ITexture> const pTexture) = 0;

		GRAPHIC_API static shared_ptr<ISprite> CreateSprite();
	};
}
#endif // Sprite_h__