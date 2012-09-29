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

namespace Base
{
	class cString;
	class cVector2;
}

namespace Graphics
{
	class ICamera;
	class ITexture;
}

namespace Graphics
{
	class ISprite
	{
	public:
		virtual ~ISprite(){}
		virtual bool VOnInitialization(shared_ptr<ITexture> const pTexture) = 0;
		virtual bool VOnInitialization(const Base::cString & strTextureFilename) = 0;
		virtual void VRender(const ICamera * const pCamera) = 0;
		virtual void VCleanup() = 0;
		virtual void VSetPosition(const Base::cVector2 & vPosition) = 0;
		virtual void VSetSize(const Base::cVector2 & vSize) = 0;
		
		GRAPHIC_API static shared_ptr<ISprite> CreateSprite();
	};
}
#endif // Sprite_h__