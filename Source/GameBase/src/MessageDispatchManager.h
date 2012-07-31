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
	class cBaseEntity;
}
namespace GameBase
{
	class cMessageDispatchManager
		: public IMessageDispatchManager
	{
	public:
		~cMessageDispatchManager();
		void DispatchMessage(const double dDelay, const int iSender, const int iReciever, const unsigned iMsg, void * const pExtraInfo );
		void OnUpdate();
		static cMessageDispatchManager * GetInstance();
	private:
		cMessageDispatchManager();
		void Discharge(cBaseEntity * const pReceiver, const AI::Telegram& msg);
		void DispatchDelayedMessage();

	private: 
		std::set<AI::Telegram>	m_PriorityQueue;
		Utilities::ITimer *		m_pTimer;

	};
}
#endif // DispatchManager_h__