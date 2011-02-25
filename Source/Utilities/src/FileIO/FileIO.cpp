#include "stdafx.h"
#include "FileIO.h"

bool cFileIO::OpenTry(const char * const strFileName)
{
	char strReason[100];
	if (m_fStdOut!= NULL)
	{
		if(fclose(m_fStdOut))
		{
			sprintf_s(strReason, 100, "Could not close file: %s", strFileName);
			Log_Write_L1(ILogger::LT_ERROR, strReason);
			return false;
		}
	}
	errno_t err;
	err = fopen_s(&m_fStdOut, strFileName, "r");
	if(err != 0)
	{
		sprintf_s(strReason, 100, "Could not open file: %s", strFileName);
		Log_Write_L1(ILogger::LT_ERROR, strReason);
	}
}