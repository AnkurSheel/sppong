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
#include "Texture.hxx"

using namespace Graphics;
using namespace Base;
using namespace Utilities;

// ***************************************************************
cFontShader::cFontShader()
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
	if(!cBaseShader::VInitialize(strVertexShaderPath, strPixelShaderPath))
		return false;

	if(!CreateSampleState())
	{
		return false;
	}

	if(!CreatePixelBuffer(sizeof(PixelBufferType)))
	{
		return false;
	}

	return true;
}

// ***************************************************************
void cFontShader::VSetShaderParameters(const D3DXMATRIX & inMatWorld,
									   const D3DXMATRIX & inMatView,
									   const D3DXMATRIX & inMatProjection)
{
	cBaseShader::VSetShaderParameters(inMatWorld, inMatView, inMatProjection);
	if(m_pTexture)
	{
		ID3D11ShaderResourceView * pTex = m_pTexture->VGetTexture();
		IDXBase::GetInstance()->VGetDeviceContext()->PSSetShaderResources(0, 1, &pTex);
	}

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
	pPixelData->pixelColor = m_TextColor;

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

// *************************************************************************
void cFontShader::SetTextColor(const Base::cColor colorText)
{
	float fRed, fBlue, fGreen, fAlpha;
	colorText.GetColorComponentsInFloat(fRed, fBlue, fGreen, fAlpha);
	m_TextColor = D3DXVECTOR4(fRed, fBlue, fGreen, fAlpha);
}

// ***************************************************************
IShader * IShader::CreateFontShader()
{
	IShader * pShader= DEBUG_NEW cFontShader();
	return pShader;
}