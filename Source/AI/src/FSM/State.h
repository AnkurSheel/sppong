// ***************************************************************
//  State   version:  1.0   Ankur Sheel  date: 05/23/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef State_h__
#define State_h__

#include "AIDefines.h"

namespace AI
{
	struct Telegram;
	class cStateImpl;
}

namespace AI
{
	template <class entity_type>
	class cState 
		: public Base::cNonCopyable
	{
	public:
		cState();
		virtual ~cState(){};
		virtual void VOnEnter(entity_type *) = 0;
		virtual void VOnUpdate(entity_type *) = 0;
		virtual void VOnExit(entity_type *) = 0;
		virtual void VOnPause(entity_type *) = 0;
		virtual void VOnResume(entity_type *) = 0;
		virtual bool VOnMessage(entity_type *, const AI::Telegram & msg) = 0;
		bool IsPaused() const;
	protected:
		bool	m_bIsPaused;
	};

#include "State.inl"

}
#endif // State_h__
