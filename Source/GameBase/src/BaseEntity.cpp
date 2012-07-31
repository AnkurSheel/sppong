// ***************************************************************
//  BaseEntity   version:  1.0   Ankur Sheel  date: 2012/07/30
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "BaseEntity.h"
#include "FSM/StateMachine.h"

using namespace AI;
using namespace Utilities;
using namespace Base;
using namespace GameBase;

int cBaseEntity::m_siNextValidID = 0;

// ***************************************************************
cBaseEntity::cBaseEntity(const int iID)
{
	SetID(iID);
}

// ***************************************************************
cBaseEntity::~cBaseEntity()
{
}

// ***************************************************************
void cBaseEntity::SetID(const int iID)
{
	//make sure the val is equal to or greater than the next available ID
	if(iID >= m_siNextValidID)
	{
		m_iID = iID;
		m_siNextValidID = m_iID + 1;
	}
}

// ***************************************************************
int cBaseEntity::GetID() const
{
	return m_iID;
}