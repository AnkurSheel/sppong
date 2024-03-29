// ***************************************************************
//  Entity2   version:  1.0   Ankur Sheel  date: 2012/07/26
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Entity2_h__
#define Entity2_h__

#include "BaseEntity.h"

namespace AI
{
	template <class entity_type> class cStateMachine;
}

class cEntity2State1;
class cEntity2State2;

class cEntity2
	: public GameBase::cBaseEntity
{
public:
	cEntity2(const int iID, const Base::cString strName);
	virtual ~cEntity2();
	void VOnUpdate();
	bool VOnHandleMessage(const AI::Telegram & telegram);
	AI::cStateMachine<cEntity2> * const GetStateMachine();

private:
	AI::cStateMachine<cEntity2> *	m_pStateMachine;
	cEntity2State1 *					m_pState1;
	cEntity2State2 *					m_pState2;

private:
	friend class cEntity2State1;
	friend class cEntity2State2;
};
#endif // Entity_h__