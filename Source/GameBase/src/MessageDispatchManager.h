// ***************************************************************
//  DispatchManager   version:  1.0   Ankur Sheel  date: 2012/07/27
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef DispatchManager_h__
#define DispatchManager_h__

#include "MessageDispatchManager.hxx"

namespace AI
{
	struct Telegram;
}

namespace Utilities
{
	class  ITimer;
}

namespace GameBase
{
	class IBaseEntity;
}

namespace GameBase
{
	class cMessageDispatchManager
		: public IMessageDispatchManager
	{
	public:
		void VDispatchMessage(const double dDelay, const int iSender, const int iReciever, const unsigned iMsg, void * const pExtraInfo );
		void VOnUpdate();
		static void CreateMessageDispatchManager();
		static void Destroy();

	private:
		cMessageDispatchManager();
		~cMessageDispatchManager();
		void Discharge(GameBase::IBaseEntity * const pReceiver, const AI::Telegram& msg);
		void DispatchDelayedMessage();

	private: 
		std::set<AI::Telegram>	m_PriorityQueue;
		Utilities::ITimer *		m_pTimer;
	public:
		static IMessageDispatchManager * s_pMessageDispatchManager;
	};
}
#endif // DispatchManager_h__