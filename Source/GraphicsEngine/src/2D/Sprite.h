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

#include "Sprite.hxx"

namespace Base
{
	class cString;
}

namespace Graphics 
{
	class cSprite
		: public ISprite
	{
	private :
		cSprite(const cSprite&){}
		cSprite operator =(const cSprite&){}

	public:
		cSprite();
		~cSprite();
		void Init(LPDIRECT3DDEVICE9 const pDevice, const Base::cString & strFilename) ;
		void SetSize(const float fNewWidth, const float fNewHeight);
		void DrawSprite(LPDIRECT3DDEVICE9 const pDevice, const D3DXVECTOR3& vPosition, const DWORD dwFlags = NULL, const D3DCOLOR& tint = WHITE, const RECT* pSrcRect = NULL);
		void Cleanup();
		UINT GetScaledHeight() const;
		UINT GetScaledWidth() const;
		D3DXVECTOR3 GetPosition() const;

	private:

		LPD3DXSPRITE		m_pSprite;		// ptr to the sprite 
		LPDIRECT3DTEXTURE9	m_pTexture;		// the texture associated with this sprite
		UINT				m_uiHeight;		// the height of the image
		UINT				m_uiWidth;		// the width of the image
		D3DXVECTOR3			m_vScale ;		// the scaling info for the image
		D3DXVECTOR3			m_vPosition ;	// the scaling info for the image
		D3DXMATRIX			m_mScaleMatrix;	// the scaling matrix
		Base::cString		m_strFilename;
	};
#include "Sprite.inl"
}
#endif // Sprite_h__