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
#include "ShaderFactory.h"
#include "Shader.hxx"

using namespace Graphics;
using namespace Utilities;

IShaderFactory * cShaderFactory::s_pShadermanager = NULL;

// *************************************************************************
cShaderFactory::cShaderFactory()
{

}

// *************************************************************************
cShaderFactory::~cShaderFactory()
{
	m_pShaders.clear();
}

// *************************************************************************
IShaderFactory * cShaderFactory::Create()
{
	return DEBUG_NEW cShaderFactory();
}

// *************************************************************************
bool cShaderFactory::VGetShader(shared_ptr<IShader> & pShader,
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

shared_ptr<IShader> cShaderFactory::Find(const Base::cString & strVertexShaderPath,
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
IShaderFactory * IShaderFactory::GetInstance()
{
	if(cShaderFactory::s_pShadermanager == NULL)
		cShaderFactory::s_pShadermanager = cShaderFactory::Create();
	return cShaderFactory::s_pShadermanager ;
}

// *************************************************************************
void IShaderFactory::Destroy()
{
	SAFE_DELETE(cShaderFactory::s_pShadermanager);
}