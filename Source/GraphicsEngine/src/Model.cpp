// ***************************************************************
//  Model   version:  1.0   Ankur Sheel  date: 2012/09/12
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "Model.h"
#include "vertexstruct.h"
#include "DxBase.hxx"
#include "Shader.hxx"
#include "Camera.h"
#include "Texture.hxx"

using namespace Utilities;
using namespace Base;

// ***************************************************************
Graphics::cModel::cModel()
: m_pVertexBuffer(NULL)
, m_pIndexBuffer(NULL)
, m_iVertexCount(0)
, m_iIndexCount(0)
, m_iPrimitiveCount(0)
, m_iVertexSize(0)
, m_pShader(NULL)
//, m_pTexture(NULL)
{

}

// ***************************************************************
Graphics::cModel::~cModel()
{
	VCleanup();
}

// ***************************************************************
bool Graphics::cModel::VOnInitialization(const stVertex * const pVertices,
										 const unsigned long * const pIndices, 
										 const UINT iNumberOfVertices, 
										 const UINT iNumberOfIndices,
										 const UINT iPrimitiveCount )
{
	m_iVertexCount = iNumberOfVertices;
	m_iIndexCount = iNumberOfIndices;
	m_iVertexSize = sizeof(stVertex);

	if(!CreateVertexBuffer(pVertices))
		return false;

	if(!CreateIndexBuffer(pIndices))
		return false;

	m_pShader = IShader::CreateColorShader();
	if (!m_pShader->VInitialize("resources\\Shaders\\colors.vsho", "resources\\Shaders\\colors.psho", 2))
	{
		return false;
	}
	return true;
}

// ***************************************************************
bool Graphics::cModel::VOnInitialization( const stTexVertex * const pVertices,
										 const unsigned long * const pIndices,
										 const UINT iNumberOfVertices, 
										 const UINT iNumberOfIndices,
										 const UINT iPrimitiveCount,
										 const Base::cString & strTextureFilename )
{
	m_iVertexCount = iNumberOfVertices;
	m_iIndexCount = iNumberOfIndices;
	m_iVertexSize = sizeof(stTexVertex);

	if(!CreateVertexBuffer(pVertices))
		return false;

	if(!CreateIndexBuffer(pIndices))
		return false;

	m_pTexture = ITexture::CreateTexture();
	m_pTexture->VInitialize(strTextureFilename);
	
	m_pShader = IShader::CreateTextureShader();
	if (!m_pShader->VInitialize("resources\\Shaders\\Texture.vsho", "resources\\Shaders\\Texture.psho", 2))
	{
		return false;
	}
	return true;
}

// ***************************************************************
void Graphics::cModel::VRender(const ICamera * const pCamera)
{
	unsigned int stride = m_iVertexSize;
	unsigned int offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	 IDXBase::GetInstance()->VGetDeviceContext()->IASetVertexBuffers(0, 1, 
		 &m_pVertexBuffer, &stride, &offset);

	IDXBase::GetInstance()->VGetDeviceContext()->IASetIndexBuffer(m_pIndexBuffer,
		DXGI_FORMAT_R32_UINT, 0);

	IDXBase::GetInstance()->VGetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if (m_pShader)
	{
		const cCamera * pCam = static_cast<const cCamera *>(pCamera);
		m_pShader->VRender(IDXBase::GetInstance()->VGetWorldMatrix(),
			pCam->GetViewMatrix(), IDXBase::GetInstance()->VGetProjectionMatrix(), m_pTexture.get());
	}

	IDXBase::GetInstance()->VGetDeviceContext()->DrawIndexed(m_iIndexCount, 0, 0);

}

// ***************************************************************
void Graphics::cModel::VCleanup()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_DELETE(m_pShader);
	//m_pTexture.reset();
}

// ***************************************************************
bool Graphics::cModel::CreateVertexBuffer( const stVertex * const pVertices)
{
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory( &vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = m_iVertexSize * m_iVertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA vertexData;
	ZeroMemory( &vertexData, sizeof(vertexData));
	vertexData.pSysMem = pVertices;

	// Now create the vertex buffer.
	HRESULT result = IDXBase::GetInstance()->VGetDevice()->CreateBuffer(&vertexBufferDesc,
		&vertexData, &m_pVertexBuffer);
	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Could not create Vertex Buffer ")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		return false;
	}
	return true;
}

// ***************************************************************
bool Graphics::cModel::CreateVertexBuffer( const stTexVertex * const pVertices )
{
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory( &vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = m_iVertexSize * m_iVertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA vertexData;
	ZeroMemory( &vertexData, sizeof(vertexData));
	vertexData.pSysMem = pVertices;

	// Now create the vertex buffer.
	HRESULT result = IDXBase::GetInstance()->VGetDevice()->CreateBuffer(&vertexBufferDesc,
		&vertexData, &m_pVertexBuffer);
	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Could not create Vertex Buffer ")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		return false;
	}
	return true;
}

// ***************************************************************
bool Graphics::cModel::CreateIndexBuffer( const unsigned long * const pIndices )
{
	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_iIndexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = pIndices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	HRESULT result = IDXBase::GetInstance()->VGetDevice()->CreateBuffer(&indexBufferDesc,
		&indexData, &m_pIndexBuffer);
	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Could not create Index Buffer ")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		return false;
	}
	return true;
}

// ***************************************************************
Graphics::IModel * Graphics::IModel::CreateModel()
{
	IModel * pModel= DEBUG_NEW cModel();
	return pModel;
}
