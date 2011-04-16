// ***************************************************************
//  FileInput   version:  1.0   Ankur Sheel  date: 2011/04/12
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef FileInput_h__
#define FileInput_h__

#include "FileInput.hxx"

namespace Base
{
	class cString;
}

namespace Utilities
{
	class cFileInput
		: public IFileInput
	{
	public:
		cFileInput();
		~cFileInput();
		bool Open(const Base::cString & strFileName);
		Base::cString ReadAll();
		Base::cString Read(size_t size);
		bool Close();
		Base::cString GetBuffer() const;

	protected:
		FILE *			m_fStdOut;
		Base::cString	m_strFileName;
		Base::cString	m_strBuffer;
	};
}
#endif // FileInput_h__