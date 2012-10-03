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
, m_pBuffer(NULL)
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
		Log_Write_L1(ILogger::LT_ERROR, "Could not open file " + m_strFileName + " : " + strerror(errno));
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
	SAFE_DELETE_ARRAY(m_pBuffer);
	if(m_inputFile.is_open())
	{
		m_inputFile.close();
		return true;
	}
	return false;
}

const BYTE * const cFileInput::ReadAll()
{
	if(!m_inputFile)
	{
		Log_Write_L1(ILogger::LT_ERROR, "File not found : " + m_strFileName);
		return NULL;
	}
	return Read(m_iFileSize);
}

const BYTE * const cFileInput::Read(std::streamoff size)
{
	if(!m_inputFile)
	{
		Log_Write_L1(ILogger::LT_ERROR, "File not found : " + m_strFileName);
		return NULL;
	}

	m_pBuffer = DEBUG_NEW BYTE[size];
	m_inputFile.read((char *)m_pBuffer, size);
	if(m_inputFile.bad() || (m_inputFile.fail() && !m_inputFile.eof()))
	{
		Log_Write_L1(ILogger::LT_ERROR, "Error in reading file: " + m_strFileName);
		SAFE_DELETE_ARRAY(m_pBuffer);
	}
	return m_pBuffer;
}

bool cFileInput::IsEOF()
{
	return m_inputFile.eof();
}

const BYTE * const cFileInput::GetBuffer() const
{
	return m_pBuffer;
}

Base::cString cFileInput::ReadLine()
{
	std::string str;
	std::getline(m_inputFile, str);
	m_strBuffer = str;
	return m_strBuffer;
}

IFileInput * IFileInput::CreateInputFile()
{
	IFileInput * pFile = DEBUG_NEW cFileInput();
	return pFile;
}

// ***************************************************************
std::streamoff Utilities::cFileInput::VGetFileSize() const
{
	return m_iFileSize;
}
