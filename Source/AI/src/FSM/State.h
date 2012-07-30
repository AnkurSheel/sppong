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
		virtual void Enter(entity_type *) = 0;
		virtual void Execute(entity_type *) = 0;
		virtual void Exit(entity_type *) = 0;
		virtual bool OnMessage(entity_type*, const Telegram &msg)=0;
	};
}
#endif // State_h__
