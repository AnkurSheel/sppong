#pragma once

#include "FileIO.hxx"

namespace Base
{
	class cString;
}

namespace Utilities
{
	class cFileIO
		: public IFileIO
	{
	public:
		cFileIO();
		~cFileIO();
		bool OpenAndRead(const Base::cString & strFileName);
		bool Close();
		Base::cString GetBuffer();

	private:
		FILE *			m_fStdOut;
		Base::cString	m_strFileName;
		Base::cString	m_strBuffer;
	};
}