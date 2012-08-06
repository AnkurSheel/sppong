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
cBaseEntity::cBaseEntity(const int iID, const Base::cString strName)
: m_strName(strName)
{
	SetID(iID);
}

// ***************************************************************
cBaseEntity::cBaseEntity(const Base::cString strName)
: m_strName(strName)
{
	SetID(m_siNextValidID);
}

// ***************************************************************
cBaseEntity::~cBaseEntity()
{
}

// ***************************************************************
void cBaseEntity::SetID(const int iID)
{
	if(iID >= m_siNextValidID)
	{
		m_iID = iID;
	}
	else
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(30, "%d is less than valid id. Setting ID to %d", m_iID, m_siNextValidID));
		m_iID = m_siNextValidID;
	}
	m_siNextValidID = m_iID + 1;
}

// ***************************************************************
int cBaseEntity::VGetID() const
{
	return m_iID;
}

// ***************************************************************
Base::cString GameBase::cBaseEntity::VGetName() const
{
	return m_strName;
}
