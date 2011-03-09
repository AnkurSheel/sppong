#include "stdafx.h"
#include "FileIO.h"
#include <sys/stat.h>
#include <errno.h>

using namespace Utilities;
using namespace Base;

cFileIO::cFileIO()
: m_fStdOut(NULL)
{
}

cFileIO::~cFileIO()
{
	Close();
}

bool cFileIO::OpenAndRead(const cString & strFileName)
{
	Close();
	errno_t err;
	
	err = fopen_s(&m_fStdOut, strFileName.GetData(), "rb");

	if(err != 0)
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Could not open file: %s, %s", strFileName.GetData(), strerror(err)));
		return false;
	}

	struct __stat64 fileStat;

	if((_stat64(strFileName.GetData(), &fileStat)) < 0)
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "File open failed (couldn't get file size): %s, %s", strFileName.GetData(), strerror(errno)));
		return false;
	}

	unsigned int cLength = (unsigned int)fileStat.st_size;
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "File %s size : %d", strFileName.GetData(), cLength));

	char * szbuffer = DEBUG_NEW char[cLength];
	unsigned int nNoOfItemsRead = fread(szbuffer, 1, cLength, m_fStdOut);

	err = errno;
	
	if(ferror(m_fStdOut) || nNoOfItemsRead != cLength)
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "File open failed (couldn't get file size): %s, %s", strFileName.GetData(), strerror(errno)));
	}

	m_strBuffer =  szbuffer;
	SAFE_DELETE_ARRAY(szbuffer);
}

bool cFileIO::Close()
{
	if(m_fStdOut)
	{
		if(fclose(m_fStdOut) != 0)
		{
			Log_Write_L1(ILogger::LT_ERROR, cString(100, "Could not close file: %s, %s", m_strFileName.GetData(), strerror(errno)));
			return false;
		}
		m_fStdOut = NULL;
	}
}

Base::cString cFileIO::GetBuffer()
{
	return m_strBuffer;
}

IFileIO * IFileIO::CreateFile()
{
	IFileIO * pFile = new cFileIO();
	return pFile;
}

void  IFileIO::Destroy()
{
	delete this;
}

