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
#include "EntityManager.hxx"
#include "FSM/Telegram.h"
#include "BaseEntity.h"

using namespace Utilities;
using namespace AI;
using namespace Base;
using namespace GameBase;

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
void cMessageDispatchManager::VDispatchMessage( const double dDelay, const int iSender, const int iReciever, const unsigned int iMsg, void * const pExtraInfo )
{
	IBaseEntity	* pReciever = IEntityManager::GetInstance()->VGetEntityFromID(iReciever);
	Telegram telegram(iSender, iReciever, iMsg, 0.0, pExtraInfo);
	if (dDelay <= 0.0)
	{
		Log_Write_L1(ILogger::LT_DEBUG, cString(100, "Sending msg %d immediately from %d to %d", iMsg, iSender, iReciever));
		Discharge(pReciever, telegram);
	}
	else
	{
		Log_Write_L1(ILogger::LT_DEBUG, cString(100, "Sending msg %d with delay of %0.2f seconds from %d to %d", iMsg, dDelay, iSender, iReciever));
		double dCurrentTime = m_pTimer->VGetRunningTime();
		telegram.DispatchTime = dCurrentTime + dDelay;
		m_PriorityQueue.insert(telegram);
	}
}

void cMessageDispatchManager::VOnUpdate()
{
	m_pTimer->VOnUpdate();
	DispatchDelayedMessage();
}
// ***************************************************************
void cMessageDispatchManager::DispatchDelayedMessage()
{
	double dCurrentTime = m_pTimer->VGetRunningTime();
	while (!m_PriorityQueue.empty() 
			&& m_PriorityQueue.begin()->DispatchTime < dCurrentTime
			&& m_PriorityQueue.begin()->DispatchTime > 0)
	{
		Telegram telegram = *m_PriorityQueue.begin();
		IBaseEntity * pReciever = IEntityManager::GetInstance()->VGetEntityFromID(telegram.Receiver);
		Discharge(pReciever, telegram);
		m_PriorityQueue.erase(m_PriorityQueue.begin());
	}
}

// ***************************************************************
void cMessageDispatchManager::Discharge( IBaseEntity * const pReceiver, const AI::Telegram& msg )
{
	if(pReceiver->VOnHandleMessage(msg))
	{
		Log_Write_L1(ILogger::LT_COMMENT, cString(100, "Message %d Handled by %d", msg.Msg, pReceiver->VGetID()));
	}
	else
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Message %d Not Handled by %d", msg.Msg, pReceiver->VGetID()));
	}

}

// ***************************************************************
void cMessageDispatchManager::CreateMessageDispatchManager()
{
	s_pMessageDispatchManager = DEBUG_NEW cMessageDispatchManager();
}

// ***************************************************************
void cMessageDispatchManager::VDestroy()
{
	delete this;
	s_pMessageDispatchManager = NULL;
}

// ***************************************************************
IMessageDispatchManager * IMessageDispatchManager::GetInstance()
{
	if(!s_pMessageDispatchManager)
		cMessageDispatchManager::CreateMessageDispatchManager();
	return s_pMessageDispatchManager;
}