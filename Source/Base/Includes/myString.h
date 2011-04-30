// ***************************************************************
//  myString   version:  1.0   Ankur Sheel  date: 2011/03/08
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef myString_h__
#define myString_h__

#include "BaseDefines.h"
#include <string>

namespace Base
{
	class cString
	{
	public:
		BASE_API cString();
		BASE_API cString(const char * s);
		BASE_API cString(std::string const & s);
		BASE_API cString(const char * s, int n);
		BASE_API cString(const char * s, int p, int n);
		BASE_API cString(const cString & str); // ankur - move to private when changing back to char * instead of string
		BASE_API cString operator =(const cString & str);
		
		BASE_API explicit cString(int iMaxSize, const char * const  lpFmt, ...);

		BASE_API const char * const operator ()();
		BASE_API void operator = (const char * const str);
		BASE_API void operator += (const char * const str);
		BASE_API void operator += (const cString & str);
		BASE_API bool operator < (const cString & str) const;
		BASE_API bool operator == (const char * szRight) const;
		BASE_API bool operator == (const cString & strRight) const;

		BASE_API const char * const GetData()const;
		BASE_API bool IsEmpty() const ;
		BASE_API static cString TimeToString(time_t time);
		BASE_API int Compare (const cString & strRight) const;

	private:
		std::string m_str;
	};
}
#endif // myString_h__