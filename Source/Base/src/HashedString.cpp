// ****************************************************************************
//  HashedString   version:  1.0   Ankur Sheel  date: 2012/12/26
//  ---------------------------------------------------------------------------
//  
//  ---------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ****************************************************************************
// 
// ****************************************************************************
#include "stdafx.h"
#include "HashedString.h"

using namespace Base;

///////////////////////////////////////////////////////////////////////////////
/// @brief Implementation of cHashedString 
///
/// 
///////////////////////////////////////////////////////////////////////////////
class cHashedString::cImpl
{
private:
	cImpl();
	cImpl(const cString & string);
	cImpl(const cImpl & other);
	cImpl & operator =(const cImpl & other);
	static unsigned long CalculateHash(const cString & strIdent);
	bool operator==(cImpl const & o) const;

private:
	unsigned long	m_lChecksum;	///< The hash associated with this string.
	cString			m_strIdent;	///< The string

	friend class cHashedString;
};

// ****************************************************************************
cHashedString::cHashedString()
: m_pImpl(DEBUG_NEW cImpl())
{
}

// ****************************************************************************
cHashedString::cHashedString(const cString & string)
: m_pImpl(DEBUG_NEW cImpl(string))
{
}

// ****************************************************************************
unsigned long cHashedString::CalculateHash(const cString & strIdent)
{
	return cImpl::CalculateHash(strIdent);
}

// *****************************************************************************
unsigned long cHashedString::GetHash() const
{
	return m_pImpl->m_lChecksum;
}

// ****************************************************************************
bool cHashedString::operator==(cHashedString const & o) const
{
	return m_pImpl == o.m_pImpl;
}

// ****************************************************************************
cHashedString::cImpl::cImpl()
: m_lChecksum(0)
{
}

// ****************************************************************************
cHashedString::cImpl::cImpl(const cString & string)
: m_strIdent(string)
, m_lChecksum(CalculateHash(string))
{
}

// ****************************************************************************
cHashedString::cImpl::cImpl(const cHashedString::cImpl & other)
: m_lChecksum(other.m_lChecksum)
, m_strIdent(other.m_strIdent)
{
}

// ****************************************************************************
cHashedString::cImpl & cHashedString::cImpl::operator =(const cHashedString::cImpl & other)
{
	m_strIdent = other.m_strIdent;
	m_lChecksum = other.m_lChecksum;
	return *this;
}

// ****************************************************************************
unsigned long cHashedString::cImpl::CalculateHash(const cString & strIdent)
{
	if(strIdent.IsEmpty())
	{
		return 0;
	}
	// largest prime smaller than 65536
	unsigned long lBASE = 65521L;
	
	// lMAX is the largest n such that // 255n(n+1)/2 + (n+1)(BASE-1) <= 2^32-1
	unsigned int lMAX = 5522;

	unsigned int s1 = 0;
	unsigned int s2 = 0;

	int i = 0;
	unsigned int length = strIdent.GetLength();
	while(length > 0)
	{
		int k = length < lMAX ? length : lMAX;
		length -= k;
		while(--k >= 0)
		{
			s1 += (unsigned int)(tolower(strIdent[i++]) & 0XFF);
			s2 += s1;
		}
		s1 %= lBASE;
		s2 %= lBASE;
	}
	return ((s2 << 16) | s1);
}

// ****************************************************************************
bool cHashedString::cImpl::operator==(cImpl const & o) const
{
	if(m_lChecksum != 0)
	{
		bool r = (m_lChecksum == o.m_lChecksum);
		return r;
	}
	return false;
}
