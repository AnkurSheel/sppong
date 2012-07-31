// ***************************************************************
//  EnityManager   version:  1.0   Ankur Sheel  date: 2012/07/27
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "StdAfx.h"
#include "EntityManager.h"
#include "BaseEntity.h"

using namespace Utilities;
using namespace Base;
using namespace GameBase;

// ***************************************************************
cEntityManager::cEntityManager()
{
	m_EntityMap.clear();
}

// ***************************************************************
cEntityManager::~cEntityManager()
{

}

// ***************************************************************
cEntityManager * cEntityManager::Instance()
{
	static cEntityManager instance;

	return &instance;
}

// ***************************************************************
void cEntityManager::VRegisterEntity( IBaseEntity * const pNewEntity )
{
	Log_Write_L1(ILogger::LT_DEBUG, cString(100, "Registering Entity: %d", pNewEntity->GetID()));
	m_EntityMap.insert(std::make_pair(pNewEntity->GetID(), pNewEntity));
}

// ***************************************************************
IBaseEntity * cEntityManager::GetEntityFromID( const int iID )
{
	//find the entity
	EntityMap::const_iterator ent = m_EntityMap.find(iID);

	//assert that the entity is a member of the map
	if (ent !=  m_EntityMap.end())
	{
		return ent->second;
	}
	return NULL;
}

// ***************************************************************
void cEntityManager::UnVRegisterEntity( IBaseEntity * const pNewEntity )
{
	m_EntityMap.erase(m_EntityMap.find(pNewEntity->GetID()));
}
