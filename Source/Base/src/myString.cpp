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

cString::cString(const char * s, int p, int n)
: m_str(s, p, n)
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

const char * const cString::operator () ()
{ 
	return m_str.c_str(); 
}

void cString::operator = (const char * const str)
{
	m_str = str;
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
