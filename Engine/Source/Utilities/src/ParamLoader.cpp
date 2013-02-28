// *****************************************************************************
//  ParamLoader   version:  1.0   Ankur Sheel  date: 2012/08/08
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "ParamLoader.h"

using namespace Utilities;
using namespace Base;

// *****************************************************************************
cParamLoader::cParamLoader()
{
}

// *****************************************************************************
cParamLoader::~cParamLoader()
{
}

// *****************************************************************************
void cParamLoader::VLoadParametersFromFile(const cString & strFileName)
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
					if(m_strBuffer[0] != '-')
					{
						m_strBuffer.Insert(0, "-");
					}
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

// *****************************************************************************
tOptional<int> cParamLoader::VGetParameterValueAsInt(const cString & strParameter) const
{
	tOptional<int> val;
	tOptional<cString> strVal = VGetParameterValueAsString(strParameter);
	if (strVal.IsValid())
	{
		cString str = *strVal;
		val = str.ToInt();
	}
	return val;
}

// *****************************************************************************
int cParamLoader::VGetParameterValueAsInt(const cString & strParameter,
										  const int iDefaultValue) const
{
	tOptional<int> val = VGetParameterValueAsInt(strParameter);
	if (val.IsInvalid())
	{
		return iDefaultValue;
	}
	return *val;
}

// *****************************************************************************
tOptional<float> cParamLoader::VGetParameterValueAsFloat(const cString & strParameter) const
{
	tOptional<float> val;
	tOptional<cString> strVal = VGetParameterValueAsString(strParameter);
	if (strVal.IsValid())
	{
		cString str = *strVal;
		val = str.ToFloat();
	}	return val;
}

// *****************************************************************************
float cParamLoader::VGetParameterValueAsFloat(const cString & strParameter,
											  const float fDefaultValue) const
{
	tOptional<float> val = VGetParameterValueAsFloat(strParameter);
	if (val.IsInvalid())
	{
		return fDefaultValue;
	}
	return *val;
}

// *****************************************************************************
tOptional<bool> cParamLoader::VGetParameterValueAsBool(const cString & strParameter) const
{
	tOptional<bool> val;

	tOptional<cString> strVal = VGetParameterValueAsString(strParameter);
	if (strVal.IsValid())
	{
		cString str = *strVal;
		val = str.ToBool();
	}
	return val;
		
}

// *****************************************************************************
bool cParamLoader::VGetParameterValueAsBool(const cString & strParameter,
											const bool bDefaultValue) const
{
	tOptional<bool> val = VGetParameterValueAsBool(strParameter);
	if (val.IsInvalid())
	{
		return bDefaultValue;
	}
	return *val;
}

// *****************************************************************************
tOptional<cString> cParamLoader::VGetParameterValueAsString(const cString & strParameter) const
{
	tOptional<cString> val;
	std::vector<cString>::const_iterator iter;
	for(iter = m_vCommandLineArguments.begin(); iter != m_vCommandLineArguments.end(); iter++)
	{
		if ((*iter)[0] != '-')
		{
			continue;
		}
		else if(iter->CompareInsensitive(strParameter))
		{
			iter++;
			if(iter == m_vCommandLineArguments.end() || (*iter)[0] == '-')
			{
				Log_Write_L1(ILogger::LT_ERROR, "No value associated with  " + strParameter + " in " + m_strFileName);
				val.clear();
				break;
			}
			val = *iter;
			break;

		}
	}
	return val;
}

// *****************************************************************************
cString cParamLoader::VGetParameterValueAsString(const cString & strParameter,
												 const cString & strDefaultValue) const
{
	tOptional<cString> val = VGetParameterValueAsString(strParameter);
	if (val.IsInvalid())
	{
		return strDefaultValue;
	}
	return *val;
}

// *****************************************************************************
void cParamLoader::VGetParameterValueAsIntList(const cString & strParameter,
											   std::vector<int> & vValue) const
{
	std::vector<cString> vValueStr;
	VGetParameterValueAsStringList(strParameter, vValueStr);
	for(unsigned int i=0; i< vValueStr.size(); i++)
	{
		vValueStr[i].TrimBoth();
		vValue.push_back(*(vValueStr[i].ToInt()));
	}

}

// *****************************************************************************
void cParamLoader::VGetParameterValueAsFloatList(const cString & strParameter,
												 std::vector<float> & vValue) const
{
	std::vector<cString> vValueStr;
	VGetParameterValueAsStringList(strParameter, vValueStr);
	for(unsigned int i=0; i< vValueStr.size(); i++)
	{
		vValueStr[i].TrimBoth();
		vValue.push_back(*(vValueStr[i].ToFloat()));
	}

}

// *****************************************************************************
void cParamLoader::VGetParameterValueAsBoolList(const cString & strParameter,
												std::vector<bool> & vValue) const
{
	std::vector<cString> vValueStr;
	VGetParameterValueAsStringList(strParameter, vValueStr);
	for(unsigned int i=0; i< vValueStr.size(); i++)
	{
		vValueStr[i].TrimBoth();
		vValue.push_back(*(vValueStr[i].ToBool()));
	}
}

// *****************************************************************************
void cParamLoader::VGetParameterValueAsStringList(const cString & strParameter,
												  std::vector<cString> & vValue) const
{
	std::vector<cString>::const_iterator iter;
	for(iter = m_vCommandLineArguments.begin(); iter != m_vCommandLineArguments.end(); iter++)
	{
		if ((*iter)[0] != '-')
		{
			continue;
		}
		else if(iter->CompareInsensitive(strParameter))
		{
			iter++;
			if(iter == m_vCommandLineArguments.end() || (*iter)[0] == '-')
			{
				Log_Write_L1(ILogger::LT_ERROR, "No value associated with  " + strParameter + " in " + m_strFileName);
				vValue.clear();
				break;
			}
			cString str = *iter;
			str.Tokenize(',', vValue);
			return;
		}
	}
}

// *****************************************************************************
bool cParamLoader::VIsParameter(const cString & strParameter) const
{
	std::vector<cString>::const_iterator iter;
	for(iter = m_vCommandLineArguments.begin(); iter != m_vCommandLineArguments.end(); iter++)
	{
		if ((*iter)[0] != '-')
		{
			continue;
		}
		else if(iter->CompareInsensitive(strParameter))
		{
			return true;
		}
	}
	return false;
}

tOptional<int> cParamLoader::GetNextParameterAsInt()
{ 
	GetNextParameter();
	tOptional<int> val =  m_strBuffer.ToInt();
	if(val.IsInvalid())
	{
		Log_Write_L1(ILogger::LT_ERROR, "Error in getting int parameter");
	}
	return val;
}

tOptional<float> cParamLoader::GetNextParameterAsFloat()
{
	GetNextParameter();
	tOptional<float> val =  m_strBuffer.ToFloat();
	if(val.IsInvalid())
	{
		Log_Write_L1(ILogger::LT_ERROR, "Error in getting float parameter");
	}
	return val;
}

tOptional<bool> cParamLoader::GetNextParameterAsBool()
{
	GetNextParameter();
	tOptional<bool> val =  m_strBuffer.ToBool();
	if(val.IsInvalid())
	{
		Log_Write_L1(ILogger::LT_ERROR, "Error in getting bool parameter");
	}
	return val;
}

void cParamLoader::GetNextParameter()
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

void cParamLoader::GetParameterValueAsString()
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

void cParamLoader::RemoveCommentsFromLine()
{
	const cString delims("/;");
	tOptional<int> index;
	index = m_strBuffer.FindFirstOf(delims, 0);
	if(index.IsValid())
	{
		m_strBuffer = m_strBuffer.GetSubString(0, *index);
	}
}

IParamLoader * IParamLoader::CreateParamLoader()
{
	IParamLoader * pFile = DEBUG_NEW cParamLoader();
	return pFile;
}