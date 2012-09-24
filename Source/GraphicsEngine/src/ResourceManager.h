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
		, public Base::cNonCopyable
	{
	public:
		static void Create();
		static void Destroy();
	
	private:
		cResourceManager();
		~cResourceManager();
		void Init(const Base::cString strPath);
		Utilities::IResCache * GetResourceCache() const;

	private:
		Utilities::IResCache *	m_pResourceCache;

	public:
		static IResourceManager* s_pResourceManager;
	};

}
#endif // ResourceManager_h__