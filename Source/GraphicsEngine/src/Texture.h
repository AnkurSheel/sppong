// ***************************************************************
//  Texture   version:  1.0   Ankur Sheel  date: 2011/07/21
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************

#ifndef Texture_h__
#define Texture_h__

#include "Texture.hxx"

namespace Base
{
	class cString;
}

namespace Graphics 
{
	class cTexture
		: public ITexture
		, public Base::cNonCopyable
	{
	public:
		cTexture();
		~cTexture();
		void Init(LPDIRECT3DDEVICE9 pDevice, const Base::cString & strFilename);
		LPDIRECT3DTEXTURE9 GetTexture();
		void Cleanup();
		DWORD GetWidth();
		DWORD GetHeight();

	private :
		cTexture(const cTexture&){}
		cTexture operator =(const cTexture&){}
	
	private:
		LPDIRECT3DTEXTURE9	m_pTexture;
		DWORD m_dwHeight;
		DWORD m_dwWidth;
	};
#include "Texture.inl"
}
#endif // Texture_h__
