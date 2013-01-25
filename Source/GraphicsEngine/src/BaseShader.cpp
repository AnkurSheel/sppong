// *****************************************************************************
//  BaseShader   version:  1.0   Ankur Sheel  date: 2012/09/24
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************

#include "stdafx.h"
#include "BaseShader.h"
#include "DxBase.hxx"
#include "FileInput.hxx"
#include "Texture.hxx"
#include "GameDirectories.h"
#include "ResCache.hxx"
#include "ResourceManager.hxx"

using namespace Graphics;
using namespace Utilities;
using namespace Base;
using namespace std;

// *****************************************************************************
cBaseShader::cBaseShader()
: m_pVertexShader(NULL)
, m_pPixelShader(NULL)
, m_pLayout(NULL)
, m_pMatrixBuffer(NULL)
{

}

// *****************************************************************************
cBaseShader::~cBaseShader()
{
	VCleanup();
}

// *****************************************************************************
bool cBaseShader::VInitialize(const Base::cString & strShaderName)
{
	if(!CreateVertexShader(strShaderName))
		return false;

	if(!CreatePixelShader(strShaderName))
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
		Log_Write_L1(ILogger::LT_ERROR, cString("Error creating matrix buffer ")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result))
			return false;
	}

	return true;
}

// *****************************************************************************
void cBaseShader::VRender(const D3DXMATRIX & inMatWorld,
									 const D3DXMATRIX & inMatView,
									 const D3DXMATRIX & inMatProjection)
{	
	VSetShaderParameters(inMatWorld, inMatView, inMatProjection);

	VRenderShader();

}

// ***************************************************************************************
void cBaseShader::VSetTexture(shared_ptr<ITexture> pTexture)
{
	m_pTexture = pTexture;
}

// *****************************************************************************
bool cBaseShader::CreateVertexShader(const Base::cString & strShaderName)
{
	//ID3D10Blob * pVertexShaderBuffer = NULL;

	//if(!CompileShader(strVertexShaderPath, strEntry, strModel, &pVertexShaderBuffer))
	//	return false;

	cString strVertexShaderPath = cGameDirectories::GameDirectories().strShaderDirectory + strShaderName + ".vsho";
	IResource * pResource = IResource::CreateResource(strVertexShaderPath);
	shared_ptr<IResHandle> shaderHandle = IResourceManager::GetInstance()->VGetResourceCache()->GetHandle(*pResource);
	
	const void * pData = shaderHandle->GetBuffer();
	HRESULT result = IDXBase::GetInstance()->VGetDevice()->CreateVertexShader(pData, 
		shaderHandle->GetSize(), NULL, &m_pVertexShader);

	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Error creating Vertex Shader ")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result))
			return false;
	}
	bool bSuccess = VCreateLayout(shaderHandle);
	SAFE_DELETE(pResource);
	return bSuccess;
}

// *****************************************************************************
bool cBaseShader::CreatePixelShader(const Base::cString & strShaderName)
{
	cString strPixelShaderPath = cGameDirectories::GameDirectories().strShaderDirectory + strShaderName + ".psho";

	IResource * pResource = IResource::CreateResource(strPixelShaderPath);
	shared_ptr<IResHandle> shaderHandle = IResourceManager::GetInstance()->VGetResourceCache()->GetHandle(*pResource);

	const void * pData = shaderHandle->GetBuffer();
	HRESULT result = IDXBase::GetInstance()->VGetDevice()->CreatePixelShader(pData, 
		shaderHandle->GetSize(), NULL, &m_pPixelShader);

	SAFE_DELETE(pResource);
	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Error creating pixel shader ")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result))
			return false;
	}

	return true;
}

// *****************************************************************************
void cBaseShader::VSetShaderParameters( const D3DXMATRIX & inMatWorld,
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
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Could not lock the Matrix Buffer to update with the matrices data: ") 
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		return ;
	}

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
}

// *****************************************************************************
void cBaseShader::VRenderShader()
{
	IDXBase::GetInstance()->VGetDeviceContext()->IASetInputLayout(m_pLayout);

	// Set the vertex and pixel shaders that will be used to render this triangle.
	IDXBase::GetInstance()->VGetDeviceContext()->VSSetShader(m_pVertexShader, NULL, 0);
	IDXBase::GetInstance()->VGetDeviceContext()->PSSetShader(m_pPixelShader, NULL, 0);
}

// *****************************************************************************
void cBaseShader::VCleanup()
{
	SAFE_RELEASE(m_pMatrixBuffer);
	SAFE_RELEASE(m_pLayout);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pVertexShader);
}