#include "stdafx.h"
#include "FileOutput.h"
#include <errno.h>

using namespace Utilities;
using namespace Base;
using namespace std;

// *************************************************************************
cFileOutput::cFileOutput()
{
}

// *************************************************************************
cFileOutput::~cFileOutput()
{
	Close();
}

// *************************************************************************
bool cFileOutput::Open(const cString & strFileName, const std::ios_base::openmode mode)
{
	if(m_OutputFile.is_open())
		Close();

	m_strFileName = strFileName;
	m_OutputFile.open(m_strFileName.GetData(), mode);

	if(!m_OutputFile)
	{
		Log_Write_L1(ILogger::LT_ERROR, "Could not open file " + m_strFileName + " : " + strerror(errno));
		return false;
	}
	Log_Write_L2(ILogger::LT_COMMENT, "Opened file: " + m_strFileName);
	return true;
}

// *************************************************************************
void cFileOutput::WriteLine(const Base::cString & strLine)
{
	m_OutputFile<<strLine.GetData();
}

// *************************************************************************
bool cFileOutput::Close()
{
	if(m_OutputFile.is_open())
	{
		m_OutputFile.close();
		return true;
	}
	return false;
}

// *************************************************************************
IFileOutput * IFileOutput::CreateOutputFile()
{
	IFileOutput * pFile = new cFileOutput();
	return pFile;
}