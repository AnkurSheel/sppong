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

namespace AI
{
	struct Telegram;
}

class cBaseEntity;
namespace Utilities
{
	class  ITimer;
}

class cMessageDispatchManager
	: public Base::cNonCopyable
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

#endif // DispatchManager_h__