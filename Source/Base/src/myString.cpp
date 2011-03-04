#include "stdafx.h"
#include "myString.h"

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

bool cString::operator<(const cString & str) const
{
	return m_str < str.m_str;
}

const char * const cString::GetData() const
{ 
	return m_str.c_str(); 
}

bool cString::IsEmpty() const
{
	return m_str.empty();
}