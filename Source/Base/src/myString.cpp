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

Base::cString::cString()
{
}

Base::cString::cString(const char * s)
: m_str(s) 
{
}

Base::cString::cString(std::string const & s)
: m_str(s)
{
}

Base::cString::cString(const char * s, int n)
: m_str(s, n) 
{
}

Base::cString::cString(int iMaxSize, const char * const lpFmt, ... )
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

Base::cString::cString( const cString & str)
: m_str(str.m_str)
{
}

Base::cString Base::cString::operator=( const cString & str)
{
	m_str = str.m_str;
	return m_str;
}

void Base::cString::operator += (const char * const str)
{
	m_str += str;
}

void Base::cString::operator += (const cString & str)
{
	m_str += str.GetData();
}

bool Base::cString::operator < (const cString & str) const
{
	return m_str < str.m_str;
}

bool Base::cString::operator == (const char * szRight) const
{
	return strcmp(m_str.c_str(), szRight) == 0;
}

bool Base::cString::operator == (const cString & strRight) const 
{
	return m_str.compare(strRight.m_str) == 0;
}

const char Base::cString::operator[](const int index) const
{
	if(index < GetLength())
	{
		return m_str[index];
	}
	return '\0';
}

char Base::cString::operator[](const int index)
{
	if(index < GetLength())
	{
		return m_str[index];
	}
	return '\0';
}

bool Base::cString::Compare (const cString & strRight) const
{
	return m_str.compare(strRight.m_str) == 0;
}

bool Base::cString::CompareInsensitive (const cString & strRight) const
{
	return _stricmp(GetData(), strRight.GetData()) == 0;
}

const char * const Base::cString::GetData() const
{ 
	return m_str.c_str(); 
}

bool Base::cString::IsEmpty() const
{
	return m_str.empty();
}

Base::cString Base::cString::TimeToString(time_t time)
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

Base::cString Base::cString::GetSubString( const size_t iStartIndex, const size_t iEndIndex ) const
{
	if (iStartIndex < 0 || iEndIndex > m_str.length())
	{
		return "";
	}

	return m_str.substr(iStartIndex, (iEndIndex-iStartIndex));
}

 Base::tOptional<int> Base::cString::ToInt() const
{
	tOptional<int> value = 0;
	int len = m_str.length();
	if(len == 0)
	{
		value.clear();
		return value;
	}
	
	int startIndex = 0;
	bool bNegative = false;

	if(m_str[0] == '-')
	{
		startIndex++;
		bNegative = true;
	}
	int intVal = m_str[startIndex++] - '0';
	for(int i = startIndex; i < len; i++)
	{
		char ch = m_str[i];
		if(ch < '0' || ch > '9')
		{
			value.clear();
			return value;
		}
		intVal = (intVal * 10 )+ ((ch - '0'));
	}

	if(bNegative)
	{
		intVal = -intVal;
	}
	value = intVal;
	return value;
}

Base::tOptional<float> Base::cString::ToFloat() const
{
	tOptional<float> value = 0;
	int len = m_str.length();
	if(len == 0)
	{
		value.clear();
		return value;
	}
	
	int startIndex = 0;
	bool bNegative = false;

	if(m_str[0] == '-')
	{
		startIndex++;
		bNegative = true;
	}

	int intVal = m_str[startIndex++] - '0';

	int index = startIndex;
	for(; index < len; index++)
	{
		char ch = m_str[index];
		if(ch < '0' || ch > '9')
		{
			if(ch == '.')
			{
				index++;
				break;
			}
			else
			{
				value.clear();
				return value;
			}
		}
		intVal = (intVal * 10 )+ ((ch - '0'));
	}
	float floatVal = 0.0f;

	float decimalDigit = 0.1f;
	for(; index < len; index++)
	{
		char ch = m_str[index];
		if(ch < '0' || ch > '9')
		{
			value.clear();
			return value;
		}
		floatVal = floatVal + ((ch - '0') * decimalDigit);
	}
	floatVal += intVal; 
	if(bNegative)
	{
		floatVal = -floatVal;
	}
	value = floatVal;
	return value;
}

Base::tOptional<bool> Base::cString::ToBool() const
{
	tOptional<bool> val;
	std::string str;
	
	if(_stricmp(m_str.data(), "true") == 0)
	{
		val = true;
	}
	else if(_stricmp(m_str.data(), "false") == 0)
	{
		val = false;
	}
	else
	{
		val.clear();
	}
	return val;
}

Base::tOptional<int> Base::cString::FindFirstNotOf(const cString & strDelims, const int iOffset) const
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

Base::tOptional<int> Base::cString::FindFirstOf(const cString & strDelims, const int iOffset) const
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
Base::tOptional<int> Base::cString::FindLastNotOf( const cString & strDelims, const int iOffset ) const
{
	tOptional<int> val;

	std::string::size_type pos = m_str.find_last_not_of(strDelims.GetData(), iOffset);
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
Base::tOptional<int> Base::cString::FindLastOf( const cString & strDelims, const int iOffset ) const
{
	tOptional<int> val;

	std::string::size_type pos = m_str.find_last_of(strDelims.GetData(), iOffset);
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
Base::tOptional<int> Base::cString::FindIndex(const char chChar, const int iOffset) const
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

// ***************************************************************
void Base::cString::TrimLeft()
{
	const cString delims(" \t");
	tOptional<int> endIndex;

	endIndex = FindFirstNotOf(delims, 0);
	if(endIndex.IsInvalid())
	{
		m_str.clear();
	}
	else if(*endIndex > 0)
	{
		tOptional<int> begIndex;

		begIndex = FindFirstOf(delims, 0);
		if(begIndex.IsValid())
		{
			m_str = m_str.substr(*endIndex, (m_str.length()-*endIndex));
		}
	}
}

// ***************************************************************
void Base::cString::TrimRight()
{
	const cString delims(" \t");
	tOptional<int> endIndex;

	endIndex = FindLastNotOf(delims, GetLength());
	if(endIndex.IsInvalid())
	{
		m_str.clear();
	}
	else
	{
		m_str = m_str.substr(0, *endIndex+1);
	}
}

// ***************************************************************
void Base::cString::TrimBoth()
{
	TrimLeft();
	TrimRight();
}

// ***************************************************************
void Base::cString::Tokenize(char cToken, std::vector<Base::cString> & vValue)
{
	int n = GetLength();
	int iStartIndex = 0;

	for(int i=0; i<n; i++)
	{
		if(m_str[i] == cToken)
		{
			cString str = GetSubString(iStartIndex, i);
			vValue.push_back(str);
			iStartIndex = i+1;
		}
	}
	if (iStartIndex < n)
	{
		cString str = GetSubString(iStartIndex, n);
		vValue.push_back(str);
	}
}

Base::cString Base::operator + (const cString & lhs, const cString & rhs)
{
	cString str = lhs;
	str += rhs;
	return str;
}

Base::cString Base::operator + (const char * lhs, const cString & rhs)
{
	cString str = lhs;
	str += rhs;
	return str;
}

Base::cString Base::operator + (const cString & lhs, const char* rhs)
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