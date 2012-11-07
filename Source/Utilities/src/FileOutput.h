#pragma once

#include "FileOutput.hxx"
#include <fstream>

namespace Base
{
	class cString;
}

namespace Utilities
{
	class cFileOutput
		: public IFileOutput
	{
	public:
		cFileOutput();
		~cFileOutput();
		bool Open(const Base::cString & strFileName, const std::ios_base::openmode mode);
		bool Close();
		void WriteLine(const Base::cString & strLine);

	protected:
		std::ofstream	m_OutputFile;
		Base::cString	m_strFileName;
	};
}