// ***************************************************************
//  MessageDispatchManager   version:  1.0   Ankur Sheel  date: 2012/07/31
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef MessageDispatchManager_hxx__
#define MessageDispatchManager_hxx__

#include "GameBaseDefines.h"

namespace GameBase
{
	class IMessageDispatchManager
		: public Base::cNonCopyable
	{
	public:
		virtual ~IMessageDispatchManager(){}
		virtual void VDispatchMessage(const double dDelay, const int iSender, const int iReciever, const unsigned iMsg, void * const pExtraInfo ) = 0;
		virtual void VOnUpdate() = 0;
		virtual void VDestroy() = 0;
		GAMEBASE_API static IMessageDispatchManager * GetInstance();
	};
}
#endif // MessageDispatchManager_hxx__