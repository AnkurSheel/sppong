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
#include "Texture.hxx"

using namespace Graphics;
using namespace Utilities;
using namespace Base;

// ***************************************************************
Graphics::cTextureShader::cTextureShader()
: m_pSampleState(NULL)
, m_pPixelBuffer(NULL)
{

}

// ***************************************************************
Graphics::cTextureShader::~cTextureShader()
{
	VCleanup();
}

// ***************************************************************
bool Graphics::cTextureShader::VCreateLayout(const IFileInput * const pVertexShaderFile )
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
										   const Base::cString & strPixelShaderPath)
{
	if(!cBaseShader::VInitialize(strVertexShaderPath, strPixelShaderPath))
		return false;
	
	if(!CreateSampleState())
	{
		return false;
	}

	if(!CreatePixelBuffer(sizeof(stPixelBufferData)))
	{
		return false;
	}
	return true;
}

// ***************************************************************
void Graphics::cTextureShader::VSetShaderParameters( const D3DXMATRIX & inMatWorld,
													const D3DXMATRIX & inMatView,
													const D3DXMATRIX & inMatProjection)
{
	cBaseShader::VSetShaderParameters(inMatWorld, inMatView, inMatProjection);
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	bool bHasTexture = false;
	if(m_pTexture)
	{
		bHasTexture = true;
		ID3D11ShaderResourceView * pTex = m_pTexture->VGetTexture();
		IDXBase::GetInstance()->VGetDeviceContext()->PSSetShaderResources(0, 1, &pTex);
	}

	// Lock the pixel constant buffer so it can be written to.
	HRESULT result = IDXBase::GetInstance()->VGetDeviceContext()->Map(m_pPixelBuffer,
		0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Could not lock the pixel Buffer to update with the data: ") 
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		return ;
	}

	stPixelBufferData * pPixelData = (stPixelBufferData*)mappedResource.pData;
	// Copy the pixel color into the pixel constant buffer.
	pPixelData->pixelColor = m_DiffuseColor;
	pPixelData->hasTexture = bHasTexture;

	// Unlock the pixel constant buffer.
	IDXBase::GetInstance()->VGetDeviceContext()->Unmap(m_pPixelBuffer, 0);

	// Set the position of the pixel constant buffer in the pixel shader.
	unsigned int iBufferNumber = 0;

	// Now set the pixel constant buffer in the pixel shader with the updated value.
	IDXBase::GetInstance()->VGetDeviceContext()->PSSetConstantBuffers(iBufferNumber, 1, &m_pPixelBuffer);
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
	SAFE_RELEASE(m_pPixelBuffer);
	cBaseShader::VCleanup();
}
// *************************************************************************
bool Graphics::cTextureShader::CreateSampleState()
{
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
// *************************************************************************
bool Graphics::cTextureShader::CreatePixelBuffer(const unsigned int ibufferSize)
{
	D3D11_BUFFER_DESC pixelBufferDesc;
	pixelBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	pixelBufferDesc.ByteWidth = roundUp(ibufferSize, 16);
	pixelBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	pixelBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	pixelBufferDesc.MiscFlags = 0;
	pixelBufferDesc.StructureByteStride = 0;

	HRESULT result = IDXBase::GetInstance()->VGetDevice()->CreateBuffer(&pixelBufferDesc, 
		NULL, &m_pPixelBuffer);

	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Error creating pixel buffer ")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result))
			return false;
	}
	return true;
}

// *************************************************************************
void Graphics::cTextureShader::SetTextColor(const Base::cColor colorText)
{
	float fRed, fBlue, fGreen, fAlpha;
	colorText.GetColorComponentsInFloat(fRed, fBlue, fGreen, fAlpha);
	m_DiffuseColor = D3DXVECTOR4(fRed, fBlue, fGreen, fAlpha);
}

// ***************************************************************
Graphics::IShader * Graphics::IShader::CreateTextureShader()
{
	IShader * pShader= DEBUG_NEW cTextureShader();
	return pShader;
}