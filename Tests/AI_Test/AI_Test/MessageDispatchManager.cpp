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
#include "Entity.h"

using namespace Utilities;
using namespace AI;
using namespace Base;

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
void cMessageDispatchManager::DispatchMessage( const double dDelay, const int iSender, const int iReciever, const unsigned int iMsg, void * const pExtraInfo )
{
	cEntity	* pReciever = cEntityManager::Instance()->GetEntityFromID(iReciever);
	Telegram telegram(iSender, iReciever, iMsg, 0.0, pExtraInfo);
	if (dDelay <= 0.0)
	{
		Log_Write_L1(ILogger::LT_DEBUG, cString(100, "Sending msg %d immediately to %d", iMsg, iReciever));
		Discharge(pReciever, telegram);
	}
	else
	{
		Log_Write_L1(ILogger::LT_DEBUG, cString(100, "Sending msg %d with delay of %0.2f seconds to %d", iMsg, dDelay, iReciever));
		double dCurrentTime = m_pTimer->VGetRunningTime();
		telegram.DispatchTime = dCurrentTime + dDelay;
		m_PriorityQueue.insert(telegram);
	}
}

void cMessageDispatchManager::OnUpdate()
{
	m_pTimer->VOnUpdate();
	DispatchDelayedMessage();
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
	if(pReceiver->HandleMessage(msg))
	{
		Log_Write_L1(ILogger::LT_DEBUG, cString(100, "Message %d Handled by %d", msg.Msg, pReceiver->GetID()));
	}
	else
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Message %d Not Handled by %d", msg.Msg, pReceiver->GetID()));
	}

}
