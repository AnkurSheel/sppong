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
	class cTextureManager
		: public ITextureManager
	{
		typedef std::map<Base::cString, shared_ptr <ITexture> > TextureMap;

	public:
		static ITextureManager * Create();

	private:
		cTextureManager();
		~cTextureManager();
		shared_ptr<ITexture> VGetTexture(const Base::cString & strTexturePath);
		shared_ptr<ITexture> Find(const Base::cString & strTexturePath);

	private:
		TextureMap	m_pTextures;

	public:
		static ITextureManager * s_pTexturemanager;		/*!< static object of this class */
	};
}