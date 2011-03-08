#pragma once

namespace Utilities
{
	class cFileIO
	{
	public:
		bool Open(const Base::cString & strFileName);

	private:
		FILE *			m_fStdOut;
		Base::cString	m_strFileName;
	};
}