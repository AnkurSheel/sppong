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
	{
	public:
		BASE_API cHashedString();
		BASE_API explicit cHashedString(const cString & strIdent);
		BASE_API explicit cHashedString(const cHashedString & other);
		BASE_API cHashedString & operator =(const cHashedString & other);
		BASE_API unsigned long GetHash() const;
		BASE_API bool operator==(cHashedString const & o) const;
		BASE_API static unsigned long CalculateHash(const cString & strIdent);

	private:
		unsigned long	m_lChecksum;
		cString			m_strIdent;
	};
}
#endif // HashedString_h__