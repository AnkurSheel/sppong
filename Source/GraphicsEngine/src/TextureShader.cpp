// ***************************************************************
//  TextureShader   version:  1.0   Ankur Sheel  date: 2012/09/24
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "TextureShader.h"
#include "DxBase.hxx"
#include "FileInput.hxx"

using namespace Graphics;
using namespace Utilities;
using namespace Base;

// ***************************************************************
Graphics::cTextureShader::cTextureShader()
: m_pSampleState(NULL)
{

}

// ***************************************************************
Graphics::cTextureShader::~cTextureShader()
{
	VCleanup();
}

// ***************************************************************
bool Graphics::cTextureShader::VCreateLayout( const int iNumberOfLayouts,
											 const IFileInput * const pVertexShaderFile )
{
	D3D11_INPUT_ELEMENT_DESC * pPolygonLayout = DEBUG_NEW D3D11_INPUT_ELEMENT_DESC[iNumberOfLayouts];

	pPolygonLayout[0].SemanticName = "POSITION";
	pPolygonLayout[0].SemanticIndex = 0;
	pPolygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	pPolygonLayout[0].InputSlot = 0;
	pPolygonLayout[0].AlignedByteOffset = 0;
	pPolygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pPolygonLayout[0].InstanceDataStepRate = 0;

	pPolygonLayout[1].SemanticName = "TEXCOORD";
	pPolygonLayout[1].SemanticIndex = 0;
	pPolygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	pPolygonLayout[1].InputSlot = 0;
	pPolygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	pPolygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	pPolygonLayout[1].InstanceDataStepRate = 0;

	HRESULT result = IDXBase::GetInstance()->VGetDevice()->CreateInputLayout(pPolygonLayout, 
		iNumberOfLayouts, pVertexShaderFile->GetBuffer(), pVertexShaderFile->VGetFileSize(), &m_pLayout);

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

// ***************************************************************
bool Graphics::cTextureShader::VInitialize( const Base::cString & strVertexShaderPath,
										   const Base::cString & strPixelShaderPath, 
										   const int iNumberOfLayouts )
{
	if(!cBaseShader::VInitialize(strVertexShaderPath, strPixelShaderPath, iNumberOfLayouts))
		return false;
	
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory( &samplerDesc, sizeof( samplerDesc ) );
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the texture sampler state.
	HRESULT result = IDXBase::GetInstance()->VGetDevice()->CreateSamplerState(&samplerDesc,
		&m_pSampleState);
	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Error creating sampler state ")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result))
			return false;
	}
	return true;
	
}

// ***************************************************************
void Graphics::cTextureShader::VSetShaderParameters( const D3DXMATRIX & inMatWorld,
													const D3DXMATRIX & inMatView,
													const D3DXMATRIX & inMatProjection,
													ID3D11ShaderResourceView * pTexture )
{
	cBaseShader::VSetShaderParameters(inMatWorld, inMatView, inMatProjection, pTexture);
	IDXBase::GetInstance()->VGetDeviceContext()->PSSetShaderResources(0, 1, &pTexture);
}

// ***************************************************************
void Graphics::cTextureShader::VRenderShader()
{
	cBaseShader::VRenderShader();
	IDXBase::GetInstance()->VGetDeviceContext()->PSSetSamplers(0, 1, &m_pSampleState);

}

// ***************************************************************
void Graphics::cTextureShader::VCleanup()
{
	SAFE_RELEASE(m_pSampleState);
	cBaseShader::VCleanup();
}

// ***************************************************************
Graphics::IShader * Graphics::IShader::CreateTextureShader()
{
	IShader * pShader= DEBUG_NEW cTextureShader();
	return pShader;
}