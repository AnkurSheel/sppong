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


IEntityManager * GameBase::cEntityManager::s_pEntityManager = NULL;

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
void cEntityManager::VRegisterEntity( IBaseEntity * const pNewEntity )
{
	Log_Write_L1(ILogger::LT_DEBUG, cString(100, "Registering Entity: %d ", pNewEntity->VGetID()) + pNewEntity->VGetName());
	m_EntityMap.insert(std::make_pair(pNewEntity->VGetID(), pNewEntity));
}

// ***************************************************************
IBaseEntity * const cEntityManager::VGetEntityFromID( const int iID )
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
cString const cEntityManager::VGetEntityNameFromID( const int iID )
{
	IBaseEntity * pEntity = VGetEntityFromID(iID);
	if (pEntity != NULL)
	{
		return pEntity->VGetName();
	}
	return "";
}

// ***************************************************************
void cEntityManager::UnRegisterEntity( IBaseEntity * const pNewEntity )
{
	m_EntityMap.erase(m_EntityMap.find(pNewEntity->VGetID()));
}

// ***************************************************************
void cEntityManager::CreateEntityManager()
{
	s_pEntityManager = DEBUG_NEW cEntityManager();
}

// ***************************************************************
void cEntityManager::Destroy()
{
	SAFE_DELETE(s_pEntityManager);
}

// ***************************************************************
IEntityManager * IEntityManager::GetInstance()
{
	if(cEntityManager::s_pEntityManager == NULL)
		cEntityManager::CreateEntityManager();
	return cEntityManager::s_pEntityManager;

}

// ***************************************************************
void IEntityManager::Destroy()
{
	cEntityManager::Destroy();
}
