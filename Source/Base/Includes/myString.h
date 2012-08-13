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
#include <iostream>

namespace Base
{
	template<class T>
	class tOptional;
}

namespace Base
{
	class cString
	{
	public:
		BASE_API cString();
		BASE_API cString(const char * s);
		BASE_API cString(std::string const & s);
		BASE_API cString(const char * s, int n);
		BASE_API cString(const cString & str); // ankur - move to private when changing back to char * instead of string
		BASE_API cString operator =(const cString & str);
		
		BASE_API explicit cString(int iMaxSize, const char * const  lpFmt, ...);

		BASE_API void operator += (const char * const str);
		BASE_API void operator += (const cString & str);
		BASE_API bool operator < (const cString & str) const;
		BASE_API bool operator == (const char * szRight) const;
		BASE_API bool operator == (const cString & strRight) const;
		BASE_API const char operator[](const int index) const;
		BASE_API char operator[](const int index);
		BASE_API const char * const GetData()const;
		BASE_API bool IsEmpty() const ;
		BASE_API int GetLength() const;
		BASE_API cString GetSubString(const size_t iStartIndex, const size_t iEndIndex) const;
		BASE_API Base::tOptional<int> FindIndex(const char chChar, const int iOffset) const;
		BASE_API Base::tOptional<int> FindFirstNotOf(const cString & strDelims, const int iOffset) const;
		BASE_API Base::tOptional<int> FindFirstOf(const cString & strDelims, const int iOffset) const;
		BASE_API Base::tOptional<int> FindLastNotOf(const cString & strDelims, const int iOffset) const;
		BASE_API Base::tOptional<int> FindLastOf(const cString & strDelims, const int iOffset) const;
		BASE_API void Insert(const int iIndex, const cString & strText);
		BASE_API void Remove(const int iIndex, const int iQuantity);
		BASE_API bool Compare (const cString & strRight) const;
		BASE_API bool CompareInsensitive (const cString & strRight) const;
		BASE_API void TrimLeft();
		BASE_API void TrimRight();
		BASE_API void TrimBoth();
		
		BASE_API Base::tOptional<int> ToInt() const;
		BASE_API Base::tOptional<float> ToFloat() const;
		BASE_API Base::tOptional<bool> ToBool() const;

		BASE_API static cString TimeToString(time_t time);

	private:
		std::string m_str;
	};

	BASE_API cString operator + (const cString & lhs, const cString & rhs);
	BASE_API cString operator + (const char * lhs, const cString & rhs);
	BASE_API cString operator + (const cString & lhs, const char* rhs);
	BASE_API std::ostream& operator << (std::ostream& os, const cString & str);

}
#endif // myString_h__