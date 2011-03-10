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

bool cFileIO::Open(const cString & strFileName)
{
	Close();
	errno_t err;
	
	m_strFileName = strFileName;
	err = fopen_s(&m_fStdOut, m_strFileName.GetData(), "rb");

	if(err != 0)
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Could not open file: %s, %s", m_strFileName.GetData(), strerror(err)));
		return false;
	}
	Log_Write_L2(ILogger::LT_COMMENT, cString(100, "Opened file: %s", m_strFileName.GetData()));
	return true;
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
		return true;
	}
	else
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "File Handle not found : %s", m_strFileName.GetData()));

	return false;
}

cString cFileIO::Read()
{
	if(!m_fStdOut)
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "File Handle not found : %s", m_strFileName.GetData()));
		return "";
	}
	struct __stat64 fileStat;

	if((_stat64(m_strFileName.GetData(), &fileStat)) < 0)
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "File open failed (couldn't get file size): %s, %s", m_strFileName.GetData(), strerror(errno)));
		return false;
	}

	unsigned int cLength = (unsigned int)fileStat.st_size;
	Log_Write_L2(ILogger::LT_DEBUG, cString(100, "Size of File %s : %d", m_strFileName.GetData(), cLength));

	char * szbuffer = DEBUG_NEW char[cLength];
	unsigned int nNoOfItemsRead = fread(szbuffer, 1, cLength, m_fStdOut);

	errno_t err = errno;

	if(ferror(m_fStdOut) || nNoOfItemsRead != cLength)
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "File open failed (couldn't get file size): %s, %s", m_strFileName.GetData(), strerror(errno)));
	}

	m_strBuffer =  szbuffer;
	SAFE_DELETE_ARRAY(szbuffer);
	return m_strBuffer;
}

cString cFileIO::GetBuffer() const
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

