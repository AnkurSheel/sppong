// ***************************************************************
//  BaseEntity   version:  1.0   Ankur Sheel  date: 2012/07/31
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef BaseEntity_hxx__
#define BaseEntity_hxx__

namespace AI
{
	struct Telegram;
}

namespace GameBase
{
	class IBaseEntity
		: public Base::cNonCopyable
	{
	public:
		virtual ~IBaseEntity(){}
		virtual void VOnUpdate() = 0;
		virtual bool VOnHandleMessage(const AI::Telegram & telegram) = 0;
		virtual int VGetID() const = 0;
		virtual Base::cString VGetName() const = 0;
	};
}
#endif // BaseEntity_hxx__