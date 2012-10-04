// ***************************************************************
//  FontShader   version:  1.0   Ankur Sheel  date: 2012/10/03
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "FontShader.h"
#include "DxBase.hxx"

using namespace Graphics;
using namespace Base;
using namespace Utilities;

// ***************************************************************
cFontShader::cFontShader()
: m_pPixelBuffer(NULL)
, m_pixelColor(1.0f, 1.0f, 1.0f, 1.0f)
{

}

// ***************************************************************
cFontShader::~cFontShader()
{
	VCleanup();
}

// ***************************************************************
bool cFontShader::VInitialize(const cString & strVertexShaderPath, 
							 const cString & strPixelShaderPath)
{
	if(!cTextureShader::VInitialize(strVertexShaderPath, strPixelShaderPath))
		return false;

	D3D11_BUFFER_DESC pixelBufferDesc;
	pixelBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	pixelBufferDesc.ByteWidth = sizeof(PixelBufferType);
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

// ***************************************************************
void cFontShader::VSetShaderParameters(const D3DXMATRIX & inMatWorld,
									   const D3DXMATRIX & inMatView,
									   const D3DXMATRIX & inMatProjection,
									   ID3D11ShaderResourceView * pTexture)
{
	cTextureShader::VSetShaderParameters(inMatWorld, inMatView, inMatProjection, pTexture);
	
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	// Lock the pixel constant buffer so it can be written to.
	HRESULT result = IDXBase::GetInstance()->VGetDeviceContext()->Map(m_pPixelBuffer,
		0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Could not lock the pixel Buffer to update with the matrices data: ") 
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		return ;
	}

	PixelBufferType * pPixelData = (PixelBufferType*)mappedResource.pData;

	// Copy the pixel color into the pixel constant buffer.
	pPixelData->pixelColor = m_pixelColor;

	// Unlock the pixel constant buffer.
	IDXBase::GetInstance()->VGetDeviceContext()->Unmap(m_pPixelBuffer, 0);

	// Set the position of the pixel constant buffer in the pixel shader.
	unsigned int iBufferNumber = 0;

	// Now set the pixel constant buffer in the pixel shader with the updated value.
	IDXBase::GetInstance()->VGetDeviceContext()->PSSetConstantBuffers(iBufferNumber, 1, &m_pPixelBuffer);
}

// ***************************************************************
void Graphics::cFontShader::VCleanup()
{
	cTextureShader::VCleanup();
	SAFE_RELEASE(m_pPixelBuffer);
}

// ***************************************************************
void Graphics::cFontShader::SetTextColor(const Base::cColor & colorText)
{
	float fRed, fBlue, fGreen, fAlpha;
	colorText.GetColorComponentsInFloat(fRed, fBlue, fGreen, fAlpha);
	m_pixelColor = D3DXVECTOR4(fRed, fBlue, fGreen, fAlpha);
}

// ***************************************************************
IShader * IShader::CreateFontShader()
{
	IShader * pShader= DEBUG_NEW cFontShader();
	return pShader;
}