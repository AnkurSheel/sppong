// ***************************************************************
//  EntityManager   version:  1.0   Ankur Sheel  date: 2012/07/31
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef EntityManager_hxx__
#define EntityManager_hxx__

#include "GameBaseDefines.h"

namespace GameBase
{
	class IBaseEntity;
}

namespace GameBase
{
	class IEntityManager
		: public Base::cNonCopyable
	{
	public:
		virtual ~IEntityManager(){}
		virtual void VRegisterEntity(IBaseEntity * const pNewEntity) = 0;
		virtual IBaseEntity * const VGetEntityFromID(const int iID) = 0;
		virtual Base::cString const VGetEntityNameFromID(const int iID) = 0;
		virtual void VDestroy() = 0;
		GAMEBASE_API static IEntityManager * GetInstance();
	};
}

#endif // EntityManager_hxx__