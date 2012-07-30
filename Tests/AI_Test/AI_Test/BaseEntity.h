// ***************************************************************
//  BaseEntity   version:  1.0   Ankur Sheel  date: 2012/07/30
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef BaseEntity_h__
#define BaseEntity_h__

class cTestState1;
class cTestState2;
namespace AI
{
	struct Telegram;
	template <class entity_type> class cStateMachine;
}
class cBaseEntity
	: public Base::cNonCopyable
{
public:
	cBaseEntity(const int iID);
	virtual ~cBaseEntity();
	virtual void VOnUpdate() = 0;
	int GetID();
	virtual bool VOnHandleMessage(const AI::Telegram & telegram) = 0;

private:
	void SetID(const int iID);

private:
	int			m_iID;
	static int	m_siNextValidID;
};
#endif // BaseEntity_h__