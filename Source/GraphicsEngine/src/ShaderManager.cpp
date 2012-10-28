// *************************************************************************
//  ShaderManager   version:  1.0   Ankur Sheel  date: 2012/10/26
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************

#include "stdafx.h"
#include "ShaderManager.h"
#include "Shader.hxx"

using namespace Graphics;
using namespace Utilities;

IShaderManager * cShaderManager::s_pShadermanager = NULL;

// *************************************************************************
cShaderManager::cShaderManager()
{

}

// *************************************************************************
cShaderManager::~cShaderManager()
{
	m_pShaders.clear();
}

// *************************************************************************
IShaderManager * cShaderManager::Create()
{
	return DEBUG_NEW cShaderManager();
}

// *************************************************************************
bool cShaderManager::VGetShader(shared_ptr<IShader> & pShader,
							   const Base::cString & strVertexShaderPath,
							   const Base::cString & strPixelShaderPath)
{
	bool bSuccess = true;
	shared_ptr<IShader> ptr = Find(strVertexShaderPath, strPixelShaderPath);

	if(ptr == NULL)
	{
		bSuccess = pShader->VInitialize(strVertexShaderPath, strPixelShaderPath);
		m_pShaders[strVertexShaderPath] = pShader;
	}
	else
	{
		pShader = ptr;
	}
	return bSuccess;
}

shared_ptr<IShader> cShaderManager::Find(const Base::cString & strVertexShaderPath,
										 const Base::cString & strPixelShaderPath)
{

	ShaderMap::const_iterator itr = m_pShaders.find(strVertexShaderPath);
	if(itr == m_pShaders.end())
	{
		return shared_ptr<IShader>(); 
	}
	Log_Write_L2(ILogger::LT_COMMENT,  "Shader already loaded " + 
		strVertexShaderPath + " " + strPixelShaderPath);

	return (*itr).second;
}

// *************************************************************************
IShaderManager * IShaderManager::GetInstance()
{
	if(cShaderManager::s_pShadermanager == NULL)
		cShaderManager::s_pShadermanager = cShaderManager::Create();
	return cShaderManager::s_pShadermanager ;
}

// *************************************************************************
void IShaderManager::Destroy()
{
	SAFE_DELETE(cShaderManager::s_pShadermanager);
}