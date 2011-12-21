// ***************************************************************
//  NonCopyable   version:  1.0   Ankur Sheel  date: 2011/12/20
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef NonCopyable_h__
#define NonCopyable_h__

namespace Base
{
	class cNonCopyable
	{
	public:
	protected:
		cNonCopyable(){}
	private:
		cNonCopyable(const cNonCopyable&);
		cNonCopyable& operator =(const cNonCopyable&);
	};
}
#endif // NonCopyable_h__