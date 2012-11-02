// *************************************************************************
//  TextureManager   version:  1.0   Ankur Sheel  date: 2012/10/28
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************

#include "TextureManager.hxx"

namespace Graphics
{
	class ITexture;
}

namespace Graphics
{
	/********************************************//**
     * @brief Class Declaration for \c ITextureManager
     * interface
     ***********************************************/
	class cTextureManager
		: public ITextureManager
	{
		typedef std::map<Base::cString, shared_ptr <ITexture> > TextureMap;

	public:
		/********************************************//**
 		 * @return An Object of this class
		 *
		 * Creates an object of this class and returns it
		 ***********************************************/
		static ITextureManager * Create();

	private:
		cTextureManager();
		~cTextureManager();
		shared_ptr<ITexture> VGetTexture(const Base::cString & strTexturePath);
		/********************************************//**
 		 * param[in] strTexturePath The path of the texture file
		 * @return Pointer to the texture if it is found in the texture list. NULL otherwise
		 *
		 * Checks if the texture has already been loaded. Returns a pointer to the texture if
		 * it is found. NULL otherwise.
		 ***********************************************/
		shared_ptr<ITexture> Find(const Base::cString & strTexturePath);

	private:
		TextureMap	m_pTextures;						/*!< map of the textures that have already been loaded */

	public:
		static ITextureManager * s_pTexturemanager;		/*!< static object of this class */
	};
}