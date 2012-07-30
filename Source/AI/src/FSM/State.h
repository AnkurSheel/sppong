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

namespace AI
{
	struct Telegram;
}

namespace AI
{
	template <class entity_type>
	class IState 
		: public Base::cNonCopyable
	{
	public:
		virtual ~IState(){};
		virtual void VOnEnter(entity_type *) = 0;
		virtual void VOnUpdate(entity_type *) = 0;
		virtual void VOnExit(entity_type *) = 0;
		virtual bool VOnMessage(entity_type *, const AI::Telegram & msg)=0;
	};
}
#endif // State_h__
