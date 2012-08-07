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
#include "GameBaseDefines.h"

namespace GameBase
{
	class cBaseEntity
		: public IBaseEntity
		, public Base::cNonCopyable
	{
	public:
		GAMEBASE_API cBaseEntity(const int iID, const Base::cString strName);
		GAMEBASE_API cBaseEntity(const Base::cString strName);
		GAMEBASE_API virtual ~cBaseEntity();
		GAMEBASE_API int VGetID() const;
		GAMEBASE_API Base::cString VGetName() const;
	private:
		void SetID(const int iID);

	private:
		int				m_iID;
		static int		m_siNextValidID;
		Base::cString	m_strName;
	};
}
#endif // BaseEntity_h__