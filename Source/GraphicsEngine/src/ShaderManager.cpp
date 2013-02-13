// *****************************************************************************
//  ShaderManager   version:  1.0   Ankur Sheel  date: 2012/10/26
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************

#include "stdafx.h"
#include "ShaderManager.h"
#include "Shader.hxx"

using namespace Graphics;
using namespace Utilities;
using namespace Base;

IShaderManager * cShaderManager::s_pShadermanager = NULL;

// *****************************************************************************
cShaderManager::cShaderManager()
{

}

// *****************************************************************************
cShaderManager::~cShaderManager()
{
	m_pShaders.clear();
}

// *****************************************************************************
bool cShaderManager::VGetShader(shared_ptr<IShader> & pShader,
							   const cString & strShaderName)
{
	bool bSuccess = true;
	unsigned long hash = cHashedString::CalculateHash(strShaderName);
	shared_ptr<IShader> ptr = Find(hash);

	if(ptr == NULL)
	{
		bSuccess = pShader->VInitialize(strShaderName);
		m_pShaders[hash] = pShader;
	}
	else
	{
		Log_Write_L2(ILogger::LT_COMMENT,  "Shader already loaded " + strShaderName);
		pShader = ptr;
	}
	return bSuccess;
}

// *****************************************************************************
shared_ptr<IShader> cShaderManager::Find(const unsigned long ulShaderHash)
{
	ShaderMap::const_iterator itr = m_pShaders.find(ulShaderHash);
	if(itr == m_pShaders.end())
	{
		return shared_ptr<IShader>(); 
	}

	return (*itr).second;
}

// *****************************************************************************
IShaderManager * IShaderManager::GetInstance()
{
	if(cShaderManager::s_pShadermanager == NULL)
		cShaderManager::s_pShadermanager = DEBUG_NEW cShaderManager();
	return cShaderManager::s_pShadermanager ;
}

// *****************************************************************************
void IShaderManager::Destroy()
{
	SAFE_DELETE(cShaderManager::s_pShadermanager);
}