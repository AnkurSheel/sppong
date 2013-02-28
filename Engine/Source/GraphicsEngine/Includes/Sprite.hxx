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
	/********************************************//**
	 * @brief Interface for 2D Sprites.
	 ***********************************************/	
	class ISprite
	{
	public:
		virtual ~ISprite(){}
		/********************************************//**
 		 * @param[in] pTexture The texture associated with this sprite
		 * return  True if the sprite was created.
		 *
		 * Initializes the sprite with the texture
		 ***********************************************/
		virtual bool VInitialize(shared_ptr<ITexture> const pTexture) = 0;
		/********************************************//**
 		 * @param[in] strTextureFilename The path of the tmexture associated with this sprite
		 * return  True if the sprite was created.
		 *
		 * Creates the texture and Initializes the sprite with the texture
		 ***********************************************/
		virtual bool VInitialize(const Base::cString & strTextureFilename) = 0;
		/********************************************//**
 		 * @param[in] pCamera The camera which contains the current view matrix
		 *
		 * Puts the 2d texture on the video card to prepare it for drawing
		 * by the shader
		 ***********************************************/
		virtual void VRender(const ICamera * const pCamera) = 0;
		/********************************************//**
		 *
		 * Releases and destroys all the resources 
		 ***********************************************/
		virtual void VCleanup() = 0;
		/********************************************//**
 		 * @param[in] vPosition The new position at which the sprite should be shown
		 *
		 * Sets the position of the sprite
		 ***********************************************/
		virtual void VSetPosition(const Base::cVector2 & vPosition) = 0;
		/********************************************//**
 		 * @param[in] vSize The new size of the sprite
		 *
		 * Sets the size(scale in pixels) of the sprite
		 ***********************************************/
		virtual void VSetSize(const Base::cVector2 & vSize) = 0;
		/********************************************//**
 		 * @return The size of the sprite
		 *
		 * Gets the size(scale in pixels) of the sprite
		 ***********************************************/
		virtual Base::cVector2 VGetSize() const = 0;
		/********************************************//**
 		 * @param[in] pTexture The new texture of the sprite
		 *
		 * Sets the texture of the sprite
		 ***********************************************/
		virtual void VSetTexture( shared_ptr<ITexture> const pTexture) = 0;
		/********************************************//**
		 * @return An object to use this interface
		 *
		 * Returns an object to use this interface
		 ***********************************************/
		GRAPHIC_API static shared_ptr<ISprite> CreateSprite();
	};
}
#endif // Sprite_h__