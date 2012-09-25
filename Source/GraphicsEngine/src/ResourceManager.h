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
	/********************************************//**
     * @brief Class Declaration for \c IResourceManager
     * interface
     ***********************************************/
	class cResourceManager
		: public IResourceManager
		, public Base::cNonCopyable
	{
	public:
		/********************************************//**
 		 * @return An Object of this class
		 *
		 * Creates an object of this class and returns it
		 ***********************************************/
		static IResourceManager * Create();
	
	private:
		cResourceManager();
		~cResourceManager();
		void VInitialize(const Base::cString strPath);
		Utilities::IResCache * VGetResourceCache() const;

	private:
		Utilities::IResCache *	m_pResourceCache;		/*!< The resource cache */

	public:
		static IResourceManager* s_pResourceManager;	/*!< static object of this class */
	};

}
#endif // ResourceManager_h__