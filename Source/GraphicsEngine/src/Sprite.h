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
	class ITexture;
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
		void Init(LPDIRECT3DDEVICE9 const pDevice, shared_ptr<ITexture> const pTexture);
		void Init(LPDIRECT3DDEVICE9 const pDevice, const Base::cString & strFilename) ;
		void SetSize(const float fNewWidth, const float fNewHeight);
		void Render(LPDIRECT3DDEVICE9 const pDevice);
		void OnLostDevice();
		void OnResetDevice();
		UINT GetScaledHeight() const;
		UINT GetScaledWidth() const;
		D3DXVECTOR3 GetPosition() const;
		void SetPosition(const D3DXVECTOR3& vPosition);
		bool IsVisible();
		void SetVisible(const bool bVisible);
		void SetFlags(const DWORD dwFlags);
		void SetTintColor(const D3DCOLOR & tintColor);
		void SetSourceRect(const RECT &	rectSrc);
		void SetTexture( shared_ptr<ITexture> const pTexture);

	private:
		void Cleanup();
		void MakeTransformMatrix();
	
	private:

		LPD3DXSPRITE					m_pSprite;		// ptr to the sprite 
		shared_ptr<ITexture>			m_pTexture;		// the texture associated with this sprite
		DWORD							m_dwHeight;		// the height of the image
		DWORD							m_dwWidth;		// the width of the image
		D3DXVECTOR3						m_vScale;		// the scaling info for the image
		D3DXVECTOR3						m_vPosition;	// the scaling info for the image
		D3DXMATRIX						m_mScaleMatrix;	// the scaling matrix
		Base::cString					m_strFilename;
		bool							m_bIsVisible;
		DWORD							m_dwFlags;
		D3DCOLOR						m_tintColor;
		RECT *							m_pSrcRect;
	};
#include "Sprite.inl"
}
#endif // Sprite_h__