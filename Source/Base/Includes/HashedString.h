// ****************************************************************************
//  HashedString   version:  1.0   Ankur Sheel  date: 2012/12/26
//  ---------------------------------------------------------------------------
//  
//  ---------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ****************************************************************************
// 
// ****************************************************************************
#ifndef HashedString_h__
#define HashedString_h__

#include "BaseDefines.h"

namespace Base
{
	class cHashedString
		: public Base::cNonCopyable
	{
	public:
		BASE_API explicit cHashedString(const cString & strIdent);
		BASE_API unsigned long GetChecksum() const;

	private:
		unsigned long CalculateHash(const cString & strIdent);

	private:
		unsigned long	m_lChecksum;
		cString			m_strIdent;
	};
}
#endif // HashedString_h__