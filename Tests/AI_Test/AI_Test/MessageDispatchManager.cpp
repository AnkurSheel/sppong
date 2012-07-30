// ***************************************************************
//  DispatchManager   version:  1.0   Ankur Sheel  date: 2012/07/27
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "MessageDispatchManager.h"
#include "Timer.hxx"
#include "EntityManager.h"
#include "FSM/Telegram.h"

using namespace Utilities;
using namespace AI;

// ***************************************************************
cMessageDispatchManager::cMessageDispatchManager()
{
	m_pTimer = ITimer::CreateTimer();
	m_pTimer->VStartTimer();
}

// ***************************************************************
cMessageDispatchManager::~cMessageDispatchManager()
{
	SAFE_DELETE(m_pTimer);
}

// ***************************************************************
void cMessageDispatchManager::DispatchMessage( const double dDelay, const int iSender, const int iReciever, const int iMsg, void * const pExtraInfo )
{
	cEntity	* pReciever = cEntityManager::Instance()->GetEntityFromID(iReciever);
	Telegram telegram(0, iSender, iReciever, iMsg, pExtraInfo);
	if (dDelay <= 0.0)
	{
		Discharge(pReciever, telegram);
	}
	else
	{
		double dCurrentTime = m_pTimer->VGetRunningTime();
		telegram.DispatchTime = dCurrentTime + dDelay;
		m_PriorityQueue.insert(telegram);
	}
}

// ***************************************************************
void cMessageDispatchManager::DispatchDelayedMessage()
{
	double dCurrentTime = m_pTimer->VGetRunningTime();
	while ((m_PriorityQueue.begin()->DispatchTime < dCurrentTime)
			&& m_PriorityQueue.begin()->DispatchTime > 0)
	{
		Telegram telegram = *m_PriorityQueue.begin();
		cEntity * pReciever = cEntityManager::Instance()->GetEntityFromID(telegram.Receiver);
		Discharge(pReciever, telegram);
		m_PriorityQueue.erase(m_PriorityQueue.begin());
	}
}

// ***************************************************************
cMessageDispatchManager * cMessageDispatchManager::GetInstance()
{
	static cMessageDispatchManager instance;

	return &instance;
}

// ***************************************************************
void cMessageDispatchManager::Discharge( cEntity* const pReceiver, const Telegram& msg )
{

}
