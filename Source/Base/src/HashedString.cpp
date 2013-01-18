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

// ****************************************************************************
cHashedString::cHashedString()
: m_lChecksum(0)
{
}

// ****************************************************************************
cHashedString::cHashedString(const cString & strIdent)
: m_strIdent(strIdent)
, m_lChecksum(CalculateHash(strIdent))
{
}

// ****************************************************************************
cHashedString::cHashedString(const cHashedString & other)
: m_strIdent(other.m_strIdent)
, m_lChecksum(other.m_lChecksum)
{
}

// ****************************************************************************
cHashedString & cHashedString::operator =(const cHashedString & other)
{
	m_strIdent = other.m_strIdent;
	m_lChecksum = other.m_lChecksum;
	return *this;
}

// ****************************************************************************
unsigned long cHashedString::CalculateHash(const cString & strIdent)
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

// *****************************************************************************
unsigned long cHashedString::GetHash() const
{
	return m_lChecksum;
}

bool cHashedString::operator==(cHashedString const & o) const
{
	if(m_lChecksum != 0)
	{
		bool r = (m_lChecksum == o.GetHash() );
		return r;
	}
	return false;
}