// ***************************************************************
//  ParamLoader   version:  1.0   Ankur Sheel  date: 2012/08/08
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "ParamLoader.h"
#include "logger.hxx"

using namespace Base;

Utilities::cParamLoader::cParamLoader()
{
}

Utilities::cParamLoader::~cParamLoader()
{
}

//bool Utilities::cParamLoader::VOpen(const Base::cString & strFileName)
//{
//	return cFileInput::Open(strFileName, std::ios_base::in);
//}
//
//bool Utilities::cParamLoader::VClose()
//{
//	return cFileInput::Close();
//}

// ***************************************************************
void Utilities::cParamLoader::VLoadParametersFromFile(const Base::cString & strFileName)
{
	if(cFileInput::Open(strFileName, std::ios_base::in))
	{
		const cString delims(" =\t");
		tOptional<int> begIndex;
		tOptional<int> endIndex;
		
		cString strParam1;
		cString strParam2;

		ReadLine();

		while(!IsEOF() || !m_strBuffer.IsEmpty())
		{
			if(!m_strBuffer.IsEmpty())
			{
				RemoveCommentsFromLine();
				m_strBuffer.TrimBoth();
				if(!m_strBuffer.IsEmpty())
				{
					endIndex = m_strBuffer.FindFirstOf(delims, 0);
					if(endIndex.IsInvalid())
					{
						m_vCommandLineArguments.push_back(m_strBuffer);
					}
					else
					{
						strParam1 = m_strBuffer.GetSubString(0, *endIndex);
						m_vCommandLineArguments.push_back(strParam1);

						begIndex = m_strBuffer.FindFirstNotOf(delims, *endIndex);
						if(begIndex.IsValid())
						{
							strParam2 = m_strBuffer.GetSubString(*begIndex, *endIndex);
							m_vCommandLineArguments.push_back(strParam2);
						}
					}
				}
			}
			ReadLine();
		}
		cFileInput::Close();
	}
}

tOptional<int> Utilities::cParamLoader::VGetNextParameterAsInt()
{
	GetNextParameter();
	tOptional<int> val =  m_strBuffer.ToInt();
	if(val.IsInvalid())
	{
		Log_Write_L1(ILogger::LT_ERROR, "Error in getting int parameter");
	}
	return val;
}

tOptional<float> Utilities::cParamLoader::VGetNextParameterAsFloat()
{
	GetNextParameter();
	tOptional<float> val =  m_strBuffer.ToFloat();
	if(val.IsInvalid())
	{
		Log_Write_L1(ILogger::LT_ERROR, "Error in getting float parameter");
	}
	return val;
}

tOptional<bool> Utilities::cParamLoader::VGetNextParameterAsBool()
{
	GetNextParameter();
	tOptional<bool> val =  m_strBuffer.ToBool();
	if(val.IsInvalid())
	{
		Log_Write_L1(ILogger::LT_ERROR, "Error in getting bool parameter");
	}
	return val;
}

void Utilities::cParamLoader::GetNextParameter()
{
	do
	{
		ReadLine();
	}
	while(m_strBuffer.IsEmpty() && !IsEOF());
	if(!m_strBuffer.IsEmpty())
	{
		m_strBuffer.TrimLeft();
		RemoveCommentsFromLine();
		m_strBuffer.TrimBoth();
		if(m_strBuffer.IsEmpty())
		{
			GetNextParameter();
			return;
		}
	}
	GetParameterValueAsString();
}

void Utilities::cParamLoader::GetParameterValueAsString()
{
	const cString delims(" /;=,\t");
	tOptional<int> begIndex;
	tOptional<int> endIndex;

	begIndex = m_strBuffer.FindFirstNotOf(delims, 0);
	if(begIndex.IsValid())
	{
		endIndex = m_strBuffer.FindFirstOf(delims, *begIndex);
		if(endIndex.IsInvalid())
		{
			endIndex = m_strBuffer.GetLength();
		}
	}

	begIndex = m_strBuffer.FindFirstNotOf(delims, *endIndex);
	if(begIndex.IsValid())
	{
		endIndex = m_strBuffer.FindFirstOf(delims, *begIndex);
		if(endIndex.IsInvalid())
		{
			endIndex = m_strBuffer.GetLength();
		}
	}
	m_strBuffer = m_strBuffer.GetSubString(*begIndex, *endIndex);
}

void Utilities::cParamLoader::RemoveCommentsFromLine()
{
	tOptional<int> index = m_strBuffer.FindIndex('/', 0);
	if(index.IsValid())
	{
		m_strBuffer = m_strBuffer.GetSubString(0, *index);
	}
}

Utilities::IParamLoader * Utilities::IParamLoader::CreateParamLoader()
{
	IParamLoader * pFile = DEBUG_NEW cParamLoader();
	return pFile;
}