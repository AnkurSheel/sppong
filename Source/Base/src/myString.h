#pragma once

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

		BASE_API const char * const operator ()();
		BASE_API void operator = (const char * const str);
		BASE_API void operator += (const char * const str);
		BASE_API bool operator<(const cString & str) const;
		
		BASE_API const char * const GetData()const;
		BASE_API bool IsEmpty() const ;

	public:
		std::string m_str;
	};
}