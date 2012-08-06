// ***************************************************************
//  EnityManager   version:  1.0   Ankur Sheel  date: 2012/07/27
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************

#ifndef EntityManager_h__
#define EntityManager_h__

#include "EntityManager.hxx"

namespace GameBase
{
	class cBaseEntity;
}

namespace GameBase
{
	class cEntityManager
		: public IEntityManager
	{
	private:
		typedef std::map<int, IBaseEntity * const > EntityMap;

	public:
		~cEntityManager();
		void VRegisterEntity(IBaseEntity * const pNewEntity);
		void UnRegisterEntity(IBaseEntity * const pNewEntity);
		IBaseEntity * const VGetEntityFromID(const int iID);
		Base::cString const VGetEntityNameFromID(const int iID);
		static void CreateEntityManager();
		void VDestroy();
	private:
		cEntityManager();

	private:
		EntityMap		m_EntityMap;

	};
	static IEntityManager * s_pEntityManager = NULL;
}
#endif // EnityManager_h__
