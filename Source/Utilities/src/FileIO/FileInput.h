#pragma once

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