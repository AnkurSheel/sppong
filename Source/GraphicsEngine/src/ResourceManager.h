// ***************************************************************
//  ResourceManager   version:  1.0   Ankur Sheel  date: 2011/11/16
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef ResourceManager_h__
#define ResourceManager_h__

#include "ResourceManager.hxx"

namespace Utilities
{
	class IResCache;
}

namespace Graphics
{
	class cResourceManager
		: public IResourceManager
	{
	public:
		cResourceManager();
		~cResourceManager();
		void Init();
		Utilities::IResCache * GetResourceCache() const;
		void OnDestroyDevice();
		void Destroy();
	private:
		cResourceManager(const cResourceManager &){}
		cResourceManager operator =(const cResourceManager&){}
	private:
		Utilities::IResCache *	m_pResourceCache;

	};
	static IResourceManager* s_pResourceManager = NULL;
}
#endif // ResourceManager_h__