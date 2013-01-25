// *****************************************************************************
//  ColorShader   version:  1.0   Ankur Sheel  date: 2012/09/15
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "ColorShader.h"
#include "DxBase.hxx"
#include "FileInput.hxx"
#include "ResCache.hxx"

using namespace Graphics;
using namespace Utilities;
using namespace Base;
using namespace std;

// *****************************************************************************
cColorShader::cColorShader()
{

}

// *****************************************************************************
cColorShader::~cColorShader()
{
}

// *****************************************************************************
bool cColorShader::VCreateLayout(shared_ptr<IResHandle const> shaderHandle)
{
	int iNumberOfLayouts = 2;
	D3D11_INPUT_ELEMENT_DESC * pPolygonLayout = DEBUG_NEW D3D11_INPUT_ELEMENT_DESC[iNumberOfLayouts];

	pPolygonLayout[0].SemanticName = "POSITION";
	pPolygonLayout[0].SemanticIndex = 0;
	pPolygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	pPolygonLayout[0].InputSlot = 0;
	pPolygonLayout[0].AlignedByteOffset = 0;
	pPolygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pPolygonLayout[0].InstanceDataStepRate = 0;

	pPolygonLayout[1].SemanticName = "COLOR";
	pPolygonLayout[1].SemanticIndex = 0;
	pPolygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	pPolygonLayout[1].InputSlot = 0;
	pPolygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	pPolygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pPolygonLayout[1].InstanceDataStepRate = 0;

	HRESULT result = IDXBase::GetInstance()->VGetDevice()->CreateInputLayout(pPolygonLayout, 
		iNumberOfLayouts, shaderHandle->GetBuffer(), shaderHandle->GetSize(), &m_pLayout);

	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Error creating Input Layout ")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result))
		SAFE_DELETE_ARRAY(pPolygonLayout);
		return false;
	}
	SAFE_DELETE_ARRAY(pPolygonLayout);
	return true;
}

// *****************************************************************************
IShader * const IShader::CreateColorShader()
{
	IShader * pShader= DEBUG_NEW cColorShader();
	return pShader;
}
