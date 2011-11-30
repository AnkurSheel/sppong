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
	{
	public:
		cTexture();
		~cTexture();
		void Init(LPDIRECT3DDEVICE9 pDevice, const Base::cString & strFilename, DWORD & outdwHeight, DWORD & outdwWidth);
		LPDIRECT3DTEXTURE9 GetTexture();
		void Cleanup();

	private :
		cTexture(const cTexture&){}
		cTexture operator =(const cTexture&){}
	
	private:
		LPDIRECT3DTEXTURE9	m_pTexture;
	};
#include "Texture.inl"
}
#endif // Texture_h__
