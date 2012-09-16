// ***************************************************************
//  ColorShader   version:  1.0   Ankur Sheel  date: 2012/09/15
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "ColorShader.h"
#include <D3DX11async.h>
#include "DxBase.hxx"
#include "FileInput.hxx"

using namespace Graphics;
using namespace Utilities;
using namespace Base;
using namespace std;

// ***************************************************************
Graphics::cColorShader::cColorShader()
: m_pVertexShader(NULL)
, m_pPixelShader(NULL)
, m_pLayout(NULL)
, m_pMatrixBuffer(NULL)
{

}

// ***************************************************************
Graphics::cColorShader::~cColorShader()
{
	Cleanup();
}

// ***************************************************************
bool Graphics::cColorShader::Initialize(const Base::cString & strVertexShaderPath,
										const Base::cString & strPixelShader,
										const int iNumberOfLayouts)
{
	if(!CreateVertexShader(strVertexShaderPath))
		return false;

	if(!CreatePixelShader(strPixelShader))
		return false;

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	D3D11_BUFFER_DESC matrixBufferDesc;
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	HRESULT result = IDXBase::GetInstance()->VGetDevice()->CreateBuffer(&matrixBufferDesc, 
		NULL, &m_pMatrixBuffer);
	if(FAILED(result))
	{
		return false;
	}

	return true;
}

// ***************************************************************
void Graphics::cColorShader::Render(const D3DXMATRIX & inMatWorld,
									const D3DXMATRIX & inMatView,
									const D3DXMATRIX & inMatProjection)
{
	D3DXMATRIX matWorld;
	D3DXMATRIX matView;
	D3DXMATRIX matProjection;

	D3DXMatrixTranspose(&matWorld, &inMatWorld);
	D3DXMatrixTranspose(&matView, &inMatView);
	D3DXMatrixTranspose(&matProjection, &inMatProjection);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT result = IDXBase::GetInstance()->VGetDeviceContext()->Map(m_pMatrixBuffer,
		0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
		return ;

	// Get a pointer to the data in the constant buffer.
	MatrixBufferType * pMatrixData = (MatrixBufferType*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	pMatrixData->world = matWorld;
	pMatrixData->view = matView;
	pMatrixData->projection = matProjection;

	// Unlock the constant buffer.
	IDXBase::GetInstance()->VGetDeviceContext()->Unmap(m_pMatrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	unsigned int iBufferNumber = 0;

	IDXBase::GetInstance()->VGetDeviceContext()->VSSetConstantBuffers(iBufferNumber,
		1, &m_pMatrixBuffer);

	IDXBase::GetInstance()->VGetDeviceContext()->IASetInputLayout(m_pLayout);

	// Set the vertex and pixel shaders that will be used to render this triangle.
	IDXBase::GetInstance()->VGetDeviceContext()->VSSetShader(m_pVertexShader, NULL, 0);
	IDXBase::GetInstance()->VGetDeviceContext()->PSSetShader(m_pPixelShader, NULL, 0);
}


// ***************************************************************
bool Graphics::cColorShader::CreateVertexShader( const Base::cString & strVertexShaderPath)
{
	//ID3D10Blob * pVertexShaderBuffer = NULL;

	//if(!CompileShader(strVertexShaderPath, strEntry, strModel, &pVertexShaderBuffer))
	//	return false;

	IFileInput * pFile = IFileInput::CreateInputFile();
	pFile->Open(strVertexShaderPath, ios_base::in | ios_base::binary);
	pFile->ReadAll();
	const void * pData = pFile->GetBuffer();
	HRESULT result = IDXBase::GetInstance()->VGetDevice()->CreateVertexShader(pData, 
		pFile->VGetFileSize(), NULL, &m_pVertexShader);

	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Error creating Vertex Shader ")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result))
			return false;
	}

	if(!CreateLayout(2, pFile))
	{
		SAFE_DELETE(pFile);
		return false;
	}
	SAFE_DELETE(pFile);

	return true;
}

// ***************************************************************
bool Graphics::cColorShader::CreatePixelShader(const Base::cString & strPixelShaderPath)
{
	IFileInput * pFile = IFileInput::CreateInputFile();
	pFile->Open(strPixelShaderPath, ios_base::in | ios_base::binary);
	pFile->ReadAll();
	const void * pData = pFile->GetBuffer();
	HRESULT result = IDXBase::GetInstance()->VGetDevice()->CreatePixelShader(pData, 
		pFile->VGetFileSize(), NULL, &m_pPixelShader);

	SAFE_DELETE(pFile);
	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Error creating pixel shader ")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result))
			return false;
	}

	return true;
}

// ***************************************************************
bool Graphics::cColorShader::CreateLayout( const int iNumberOfLayouts,
										  const Utilities::IFileInput * const pFile)
{
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
		iNumberOfLayouts, pFile->GetBuffer(), pFile->VGetFileSize(), &m_pLayout);

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
void Graphics::cColorShader::Cleanup()
{
	SAFE_RELEASE(m_pMatrixBuffer);
	SAFE_RELEASE(m_pLayout);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pVertexShader);
}
