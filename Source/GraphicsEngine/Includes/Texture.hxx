// ***************************************************************
//  Texture   version:  1.0   Ankur Sheel  date: 2011/11/23
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Texture_hxx__
#define Texture_hxx__

#include "GraphicEngineDefines.h"

namespace Base
{
	class cString;
}

namespace Graphics
{
	class ITexture
	{
	public:
		virtual ~ITexture(){}
		virtual void Init(LPDIRECT3DDEVICE9 pDevice, const Base::cString & strFilename, DWORD & outdwHeight, DWORD & outdwWidth) = 0;
		virtual LPDIRECT3DTEXTURE9 GetTexture() = 0;
		GRAPHIC_API static std::tr1::shared_ptr<ITexture> CreateTexture();
	};
}

#endif // Texture_hxx__