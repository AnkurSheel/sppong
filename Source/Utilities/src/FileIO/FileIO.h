#pragma once

#include "myString.h"

namespace Utilities
{
	class cFileIO
	{
	public:
		bool Open(Base::cString strFileName);

	private:
		FILE *			m_fStdOut;
		Base::cString	m_strFileName;
	};
}