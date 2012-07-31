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

#include "BaseEntity.hxx"

namespace GameBase
{
	class cBaseEntity
		: public IBaseEntity
	{
	public:
		cBaseEntity(const int iID);
		virtual ~cBaseEntity();
		int GetID() const;

	private:
		void SetID(const int iID);

	private:
		int			m_iID;
		static int	m_siNextValidID;
	};
}
#endif // BaseEntity_h__