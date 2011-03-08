#include "stdafx.h"
#include "FileIO.h"

using namespace Utilities;
using namespace Base;

bool cFileIO::Open(const cString & strFileName)
{
	cString strReason;
	if (m_fStdOut!= NULL)
	{
		if(fclose(m_fStdOut))
		{
			Log_Write_L1(ILogger::LT_ERROR, cString(100, "Could not close file: %s", strFileName).GetData());
			return false;
		}
	}
	errno_t err;
	err = fopen_s(&m_fStdOut, strFileName.GetData(), "r");
	if(err != 0)
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Could not open file: %s", strFileName).GetData());
	}
}