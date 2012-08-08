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
: m_iFileSize(0)
{
}

cFileInput::~cFileInput()
{
	Close();
}

bool cFileInput::Open(const cString & strFileName, const std::ios_base::openmode mode)
{
	if(m_inputFile.is_open())
		Close();

	m_strFileName = strFileName;
	m_inputFile.open(m_strFileName.GetData(), mode);

	if(!m_inputFile)
	{
		Log_Write_L1(ILogger::LT_ERROR, "Could not open file: " + m_strFileName);
		return false;
	}
	Log_Write_L2(ILogger::LT_COMMENT, "Opened file: " + m_strFileName);
	m_inputFile.seekg(0, std::ios::end);
	m_iFileSize = m_inputFile.tellg();
	m_inputFile.seekg(0, std::ios::beg);
	Log_Write_L2(ILogger::LT_DEBUG, "Size of File " + m_strFileName + cString(20, " : %d bytes", m_iFileSize));
	return true;
}

bool cFileInput::Close()
{
	if(m_inputFile.is_open())
	{
		m_inputFile.close();
		return true;
	}
	return false;
}

cString cFileInput::ReadAll()
{
	if(!m_inputFile)
	{
		Log_Write_L1(ILogger::LT_ERROR, "File not found : " + m_strFileName);
		return "";
	}
	return Read(m_iFileSize);
}

cString cFileInput::Read(size_t size)
{
	if(!m_inputFile)
	{
		Log_Write_L1(ILogger::LT_ERROR, "File not found : " + m_strFileName);
		return "";
	}

	char * szbuffer = DEBUG_NEW char[size];
	m_inputFile._Read_s(szbuffer, size, size);

	cString str(szbuffer, size);
	m_strBuffer = str;
	SAFE_DELETE_ARRAY(szbuffer);
	return m_strBuffer;
}

cString cFileInput::GetBuffer() const
{
	return m_strBuffer;
}

IFileInput * IFileInput::CreateInputFile()
{
	IFileInput * pFile = new cFileInput();
	return pFile;
}
