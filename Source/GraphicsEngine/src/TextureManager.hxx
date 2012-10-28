// *************************************************************************
//  TextureManager   version:  1.0   Ankur Sheel  date: 2012/10/28
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************

#include "GraphicEngineDefines.h"

namespace Graphics
{
	class ITexture;
}

namespace Graphics
{
	class ITextureManager
	{
	public:
		virtual ~ITextureManager(){}
		virtual shared_ptr<ITexture> VGetTexture(const Base::cString & strTexturePath) = 0;

		GRAPHIC_API static ITextureManager * GetInstance();
		GRAPHIC_API static void Destroy();
	};
}