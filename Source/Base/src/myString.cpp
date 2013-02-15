// *****************************************************************************
//  myString   version:  1.0   Ankur Sheel  date: 2011/03/08
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "myString.h"
#include <time.h>
#include "Optional.h"

using namespace Base;

// ****************************************************************************
cString::cString()
{
}

// *****************************************************************************
cString::cString(const char * s)
{
	if (s != NULL)
	{
		m_str = s;
	}
}

// *****************************************************************************
cString::cString(std::string const & s)
: m_str(s)
{
}

// *****************************************************************************
cString::cString(const int iMaxSize, const char * const  lpFmt, ...)
{
	va_list argptr;
	va_start(argptr, lpFmt);
	char * szBuffer = DEBUG_NEW char[iMaxSize];
	int cnt = vsprintf_s(szBuffer, iMaxSize, lpFmt, argptr);
	va_end(argptr);
	
	m_str += szBuffer;
	SAFE_DELETE_ARRAY(szBuffer);
}

// ****************************************************************************
cString::cString(const cString & other)
: m_str(other.m_str)
{
}

// ****************************************************************************
cString & cString::operator=(const cString & other)
{
	m_str = other.m_str;
	return *this;
}

// *****************************************************************************
void cString::operator+=(const cString & str)
{
	m_str.append(str.GetData());
}

// *****************************************************************************
bool cString::operator < (const cString & str) const
{
	return m_str.compare(str.m_str) < 0;
}

// *****************************************************************************
bool cString::operator == (const cString & str) const 
{
	return m_str.compare(str.m_str) == 0;
}

// *****************************************************************************
const char cString::operator[](const unsigned int index) const
{
	if(index < GetLength())
	{
		return m_str[index];
	}
	return '\0';
}

// *****************************************************************************
char cString::operator[](const unsigned int index)
{
	if(index < GetLength())
	{
		return m_str[index];
	}
	return '\0';
}

// *****************************************************************************
const char * const cString::GetData() const
{ 
	return m_str.c_str();
}

// *****************************************************************************
bool cString::IsEmpty() const
{
	return m_str.empty();
}

// *****************************************************************************
unsigned int cString::GetLength() const
{
	return m_str.length();
}

// *****************************************************************************
cString cString::GetSubString(const unsigned int uiStartIndex,
							  const unsigned int uiEndIndex) const
{
	if (uiStartIndex < 0 || uiEndIndex > GetLength())
	{
		return "";
	}

	return m_str.substr(uiStartIndex, (uiEndIndex - uiStartIndex));
}

// *****************************************************************************
tOptional<int> cString::FindIndex(const char chChar, const int iOffset) const
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

// *****************************************************************************
tOptional<int> cString::FindFirstOf(const cString & strChars,
										   const int iOffset) const
{
	tOptional<int> val;
	
	std::string::size_type pos = m_str.find_first_of(strChars.GetData(), iOffset);
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

// *****************************************************************************
tOptional<int> cString::FindFirstNotOf(const cString & strChars,
											  const int iOffset) const
{
	tOptional<int> val;
	
	std::string::size_type pos = m_str.find_first_not_of(strChars.GetData(), iOffset);
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

// *****************************************************************************
tOptional<int> cString::FindLastOf(const cString & strChars,
								   const int iOffset) const
{
	tOptional<int> val;

	std::string::size_type pos = m_str.find_last_of(strChars.GetData(), iOffset);
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

// *****************************************************************************
tOptional<int> cString::FindLastNotOf(const cString & strChars,
									  const int iOffset) const
{
	tOptional<int> val;

	std::string::size_type pos = m_str.find_last_not_of(strChars.GetData(), iOffset);
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

// *****************************************************************************
bool cString::CompareInsensitive (const cString & str) const
{
	return _stricmp(GetData(), str.GetData()) == 0;
}

// *****************************************************************************
void cString::TrimLeft()
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

// *****************************************************************************
void cString::TrimRight()
{
	const cString delims(" \t\r\n");
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

// *****************************************************************************
void cString::TrimBoth()
{
	if (IsEmpty())
	{
		return;
	}
	TrimLeft();
	TrimRight();
}

// *****************************************************************************
void cString::Insert( const int iIndex, const cString & strText )
{
	m_str.insert(iIndex, strText.GetData());
}

// *****************************************************************************
void cString::Remove( const int iIndex, const int iQuantity )
{
	m_str.erase(iIndex, iQuantity);
}

// *****************************************************************************
void cString::Tokenize(char cToken, std::vector<cString> & vValue) const
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

// *****************************************************************************
tOptional<int> cString::ToInt() const
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

// *****************************************************************************
tOptional<float> cString::ToFloat() const
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
		decimalDigit *= 0.1f;
	}
	floatVal += intVal; 
	if(bNegative)
	{
		floatVal = -floatVal;
	}
	value = floatVal;
	return value;
}

// *****************************************************************************
tOptional<bool> cString::ToBool() const
{
	tOptional<bool> val;
	std::string str;
	
	if(_stricmp(m_str.data(), "true") == 0 || _stricmp(m_str.data(), "yes") == 0
		|| _stricmp(m_str.data(), "1") == 0)
	{
		val = true;
	}
	else if(_stricmp(m_str.data(), "false") == 0 || _stricmp(m_str.data(), "no") == 0
		|| _stricmp(m_str.data(), "0") == 0)
	{
		val = false;
	}
	else
	{
		val.clear();
	}
	return val;
}

// *****************************************************************************
cString cString::GetExtensionFromFileName() const
{
	tOptional<int> index = FindLastOf(".", GetLength());
	if (index.IsValid())
	{
		return GetSubString(*index + 1, GetLength());
	}
	return "";
}

// *****************************************************************************
cString cString::TimeToString(time_t time)
{
	char str[26];
	ctime_s(str, 26, &time);
	str[24] = ' '; // remove the '/n' from the time string
	return str;
}

// *****************************************************************************
cString Base::operator + (const cString & lhs, const cString & rhs)
{
	cString str = lhs;
	str += rhs;
	return str;
}

// *****************************************************************************
cString Base::operator + (const char * lhs, const cString & rhs)
{
	cString str = lhs;
	str += rhs;
	return str;
}

// *****************************************************************************
cString Base::operator + (const cString & lhs, const char* rhs)
{
	cString str = lhs;
	str += rhs;
	return str;
}

// *****************************************************************************
std::ostream& Base::operator << (std::ostream& os, const cString & str)
{
	os << str.GetData();
	return os;
}