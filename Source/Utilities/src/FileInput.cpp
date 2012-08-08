// ***************************************************************
//  FileInput   version:  1.0   Ankur Sheel  date: 2011/04/12
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************

#include "stdafx.h"
#include "FileInput.h"
#include <sys/stat.h>
#include <errno.h>

using namespace Utilities;
using namespace Base;

cFileInput::cFileInput()
: m_fStdOut(NULL)
{
}

cFileInput::~cFileInput()
{
	Close();
}

bool cFileInput::Open(const cString & strFileName)
{
	if(m_fStdOut)
		Close();
	errno_t err;
	
	m_strFileName = strFileName;
	err = fopen_s(&m_fStdOut, m_strFileName.GetData(), "rb");

	if(err != 0)
	{
		Log_Write_L1(ILogger::LT_ERROR, "Could not open file: " + m_strFileName + " : " + strerror(err));
		return false;
	}
	Log_Write_L2(ILogger::LT_COMMENT, "Opened file: " + m_strFileName);
	return true;
}

bool cFileInput::Close()
{
	if(m_fStdOut)
	{
		if(fclose(m_fStdOut) != 0)
		{
			Log_Write_L1(ILogger::LT_ERROR, "Could not close file: " + m_strFileName + " : " + strerror(errno));
			return false;
		}
		m_fStdOut = NULL;
		return true;
	}
	else
	{
			Log_Write_L1(ILogger::LT_ERROR, "File Handle not found : " + m_strFileName);
	}

	return false;
}

cString cFileInput::ReadAll()
{
	if(!m_fStdOut)
	{
		Log_Write_L1(ILogger::LT_ERROR, "File Handle not found : " + m_strFileName);
		return "";
	}
	struct __stat64 fileStat;

	if((_stat64(m_strFileName.GetData(), &fileStat)) < 0)
	{
		Log_Write_L1(ILogger::LT_ERROR, "File open failed (couldn't get file size): " + m_strFileName + " : " + strerror(errno));
		return false;
	}

	Log_Write_L2(ILogger::LT_DEBUG, "Size of File " + m_strFileName + cString(20, " : %d bytes", fileStat.st_size));
	return Read(fileStat.st_size);
}

cString cFileInput::Read(size_t size)
{
	if(!m_fStdOut)
	{
		Log_Write_L1(ILogger::LT_ERROR, "File Handle not found : " + m_strFileName);
		return "";
	}
	
	char * szbuffer = DEBUG_NEW char[size];
	unsigned int nNoOfItemsRead = fread(szbuffer, 1, size, m_fStdOut);

	errno_t err = errno;

	if(ferror(m_fStdOut) || nNoOfItemsRead != size)
	{
		Log_Write_L1(ILogger::LT_ERROR, "File open failed (couldn't get file size): " + m_strFileName + " : " + strerror(errno));
	}
	cString str(szbuffer, nNoOfItemsRead);
	m_strBuffer = str;
	SAFE_DELETE_ARRAY(szbuffer);
	return m_strBuffer;
}

cString cFileInput::GetBuffer() const
{
	return m_strBuffer;
}

IFileInput * IFileInput::CreateUserFile()
{
	IFileInput * pFile = new cFileInput();
	return pFile;
}
