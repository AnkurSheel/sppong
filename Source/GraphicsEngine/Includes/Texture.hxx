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
		virtual void VInitialize(const Base::cString & strTexturePath) = 0;
		virtual ID3D11ShaderResourceView * VGetTexture() const = 0;
		GRAPHIC_API static shared_ptr<ITexture> CreateTexture();
	};
}

#endif // Texture_hxx__