// ***************************************************************
//  myString   version:  1.0   Ankur Sheel  date: 2011/03/08
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "myString.h"
#include <time.h>
#include "Optional.h"

using namespace Base;

cString::cString()
{
}

cString::cString(const char * s)
: m_str(s) 
{
}

cString::cString(std::string const & s)
: m_str(s)
{
}

cString::cString(const char * s, int n)
: m_str(s, n) 
{
}

cString::cString(int iMaxSize, const char * const lpFmt, ... )
{
	char * szBuffer = DEBUG_NEW char[iMaxSize+1];
	va_list argptr;
	int cnt;

	va_start(argptr, lpFmt);
	cnt = vsprintf_s(szBuffer, iMaxSize, lpFmt, argptr);
	va_end(argptr);
	
	m_str += szBuffer;
	SAFE_DELETE_ARRAY(szBuffer);
}

cString::cString( const cString & str)
{
	m_str = str.m_str;
}

cString cString::operator=( const cString & str)
{
	m_str = str.m_str;
	return m_str;
}

void cString::operator += (const char * const str)
{
	m_str += str;
}

void cString::operator += (const cString & str)
{
	m_str += str.GetData();
}

bool cString::operator < (const cString & str) const
{
	return m_str < str.m_str;
}

bool cString::operator == (const char * szRight) const
{
	return strcmp(m_str.c_str(), szRight) == 0;
}

bool cString::operator == (const cString & strRight) const 
{
	return m_str.compare(strRight.m_str) == 0;
}

int cString::Compare (const cString & strRight) const
{
	return m_str.compare(strRight.m_str);
}

const char * const cString::GetData() const
{ 
	return m_str.c_str(); 
}

bool cString::IsEmpty() const
{
	return m_str.empty();
}

cString cString::TimeToString(time_t time)
{
	char str[26];
	ctime_s(str, 26, &time);
	str[24] = ' '; // remove the '/n' from the time string
	return str;
}
// ***************************************************************

int Base::cString::GetLength() const
{
	return m_str.length();
}
// ***************************************************************

cString Base::cString::GetSubString( const size_t iStartIndex, const size_t iEndIndex ) const
{
	if (iStartIndex < 0 || iEndIndex > m_str.length())
	{
		return "";
	}

	return m_str.substr(iStartIndex, (iEndIndex-iStartIndex));
}

tOptional<int> Base::cString::ToInt() const
{
	size_t idx;
	tOptional<int> val = std::stoi(m_str, &idx);
	if(idx != m_str.length())
	{
		val.clear();
	}
	return val;
}

tOptional<float> Base::cString::ToFloat() const
{
	size_t idx;
	tOptional<float> val = std::stof(m_str, &idx);
	if(idx != m_str.length())
	{
		val.clear();
	}
	return val;
}

tOptional<bool> Base::cString::ToBool() const
{
	size_t idx;
	tOptional<bool> val;
	std::string str;
	
	if(stricmp(m_str.data(), "true") == 0)
	{
		val = true;
	}
	else if(stricmp(m_str.data(), "false") == 0)
	{
		val = false;
	}
	else
	{
		val.clear();
	}
	return val;
}

tOptional<int> Base::cString::FindFirstNotOf(const cString & strDelims, const int iOffset) const
{
	tOptional<int> val;
	
	std::string::size_type pos = m_str.find_first_not_of(strDelims.GetData(), iOffset);
	if(pos == std::string::npos)
	{
		val.clear();
	}
	else
	{
		val = pos;
	}

	return val;
}

BASE_API tOptional<int> Base::cString::FindFirstOf(const cString & strDelims, const int iOffset) const
{
	tOptional<int> val;
	
	std::string::size_type pos = m_str.find_first_of(strDelims.GetData(), iOffset);
	if(pos == std::string::npos)
	{
		val.clear();
	}
	else
	{
		val = pos;
	}

	return val;
}

// ***************************************************************
tOptional<int> Base::cString::FindIndex(const char chChar, const int iOffset) const
{
	tOptional<int> val;

	std::string::size_type pos = m_str.find(chChar, iOffset);
	if(pos == std::string::npos)
	{
		val.clear();
	}
	else
	{
		val = pos;
	}

	return val;

}

void Base::cString::Insert( const int iIndex, const cString & strText )
{
	m_str.insert(iIndex, strText.GetData());
}
// ***************************************************************

void Base::cString::Remove( const int iIndex, const int iQuantity )
{
	m_str.erase(iIndex, iQuantity);
}

cString Base::operator + (const cString & lhs, const cString & rhs)
{
	cString str = lhs;
	str += rhs;
	return str;
}

cString Base::operator + (const char * lhs, const cString & rhs)
{
	cString str = lhs;
	str += rhs;
	return str;
}

cString Base::operator + (const cString & lhs, const char* rhs)
{
	cString str = lhs;
	str += rhs;
	return str;
}

std::ostream& Base::operator << (std::ostream& os, const cString & str)
{
	os << str.GetData();
	return os;
}