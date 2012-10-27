// ***************************************************************
//  Sprite   version:  1.0   Ankur Sheel  date: 05/09/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************

#include "stdafx.h"
#include "Sprite.h"
#include "DxBase.hxx"
#include "Texture.hxx"
#include "TextureShader.h"
#include "vertexstruct.h"
#include "Camera.h"
#include "ShaderFactory.hxx"

using namespace Utilities;
using namespace Graphics;
using namespace Base;

// ***************************************************************
cSprite::cSprite()
: m_pVertexBuffer(NULL)
, m_pIndexBuffer(NULL)
, m_vSize(cVector2::Zero())
, m_vPosition(cVector2::Zero())
, m_bIsDirty(true)
, m_iIndexCount(0)
, m_iVertexCount(0)
{
}

// ***************************************************************
cSprite::~cSprite()
{
	VCleanup();
}

// ***************************************************************
bool cSprite::VInitialize( shared_ptr<ITexture> const pTexture )
{
	m_pTexture = pTexture;
	m_iVertexCount = 4;
	if(!CreateVertexBuffer())
		return false;

	if(!CreateIndexBuffer())
		return false;

	if(!InitializeShader())
		return false;

	m_vPosition = cVector2(-1.0f, -1.0f);
	
	ID3D11Resource* resource;
	ID3D11Texture2D * texResource;
	D3D11_TEXTURE2D_DESC desc;
	m_pTexture->VGetTexture()->GetResource(&resource);
	texResource = reinterpret_cast<ID3D11Texture2D*>(resource);
	texResource->GetDesc(&desc);
	
	m_vSize.m_dX = desc.Width;
	m_vSize.m_dY = desc.Height;
	m_bIsDirty = true;
	SAFE_RELEASE(resource);
	return true;
}

// ***************************************************************
bool cSprite::VInitialize( const Base::cString & strTextureFilename )
{
	Log_Write_L2(ILogger::LT_EVENT, "Loading Sprite : " + strTextureFilename);

	if (m_pTexture == NULL)
	{
		m_pTexture = ITexture::CreateTexture();
	}
	m_pTexture->VInitialize(strTextureFilename);
	
	return VInitialize(m_pTexture);
}

// ***************************************************************
void cSprite::VRender(const ICamera * const pCamera)
{
	if (!m_pTexture)
	{
		return;
	}
	if (m_bIsDirty)
	{
		RecalculateVertexData();
		m_bIsDirty = false;
	}

	unsigned int stride = sizeof(stTexVertex);
	unsigned int offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	IDXBase::GetInstance()->VGetDeviceContext()->IASetVertexBuffers(0, 1, 
		&m_pVertexBuffer, &stride, &offset);

	IDXBase::GetInstance()->VGetDeviceContext()->IASetIndexBuffer(m_pIndexBuffer,
		DXGI_FORMAT_R32_UINT, 0);

	IDXBase::GetInstance()->VGetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	IDXBase::GetInstance()->VTurnZBufferOff();
	if (m_pShader)
	{
		const cCamera * pCam = static_cast<const cCamera *>(pCamera);
		m_pShader->VRender(IDXBase::GetInstance()->VGetWorldMatrix(),
			pCam->GetViewMatrix(), IDXBase::GetInstance()->VGetOrthoMatrix(),
			m_pTexture.get());
	}
	IDXBase::GetInstance()->VGetDeviceContext()->DrawIndexed(m_iIndexCount, 0, 0);
}

// ***************************************************************
void cSprite::VSetPosition( const Base::cVector2 & vPosition )
{
	m_vPosition = vPosition;
	m_bIsDirty = true;
}

// ***************************************************************
void cSprite::VSetSize( const Base::cVector2 & vSize )
{
	m_vSize = vSize;
	m_bIsDirty = true;
}

// ***************************************************************
void cSprite::VGetSize(Base::cVector2 & vSize)
{
	vSize = m_vSize;
}

// *************************************************************************
void cSprite::VSetTexture(shared_ptr<ITexture> const pTexture)
{
	m_pTexture = pTexture;
}

// ***************************************************************
void cSprite::VCleanup()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
}

// ***************************************************************
bool cSprite::CreateVertexBuffer()
{
	stTexVertex * pVertices = DEBUG_NEW stTexVertex[m_iVertexCount];

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory( &vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(stTexVertex) * m_iVertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA vertexData;
	ZeroMemory( &vertexData, sizeof(vertexData));
	vertexData.pSysMem = pVertices;

	// Now create the vertex buffer.
	HRESULT result = IDXBase::GetInstance()->VGetDevice()->CreateBuffer(&vertexBufferDesc,
		&vertexData, &m_pVertexBuffer);

	SAFE_DELETE_ARRAY(pVertices);

	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Could not create Vertex Buffer ")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		return false;
	}
	return true;
}

// ***************************************************************
bool cSprite::CreateIndexBuffer()
{
	unsigned long aIndices[] = {0,1,2,
								1,3,2};
	m_iIndexCount = 6;
	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_iIndexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = aIndices;
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
bool cSprite::RecalculateVertexData()
{
	//center of the screen is 0,0
	float left = -(float)IDXBase::GetInstance()->VGetScreenWidth()/2.0f + m_vPosition.m_dX;
	float right = left + m_vSize.m_dX;
	float top = (float)IDXBase::GetInstance()->VGetScreenHeight()/2.0f - m_vPosition.m_dY;
	float bottom = top - m_vSize.m_dY;

	// Create the vertex array.
	stTexVertex * pVertices = DEBUG_NEW stTexVertex [4];
	pVertices[0] = stTexVertex(left, bottom, 0.0f, 0.0f, 1.0f);
	pVertices[1] = stTexVertex(left, top, 0.0f, 0.0f, 0.0f);
	pVertices[2] = stTexVertex(right, bottom, 0.0f, 1.0f, 1.0f);
	pVertices[3] = stTexVertex(right, top, 0.0f, 1.0f, 0.0f);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT result = IDXBase::GetInstance()->VGetDeviceContext()->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Could not lock the  vertex buffer to update with the vertex data: ") 
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		
		SAFE_DELETE_ARRAY(pVertices);
		return false;
	}

	// Get a pointer to the data in the vertex buffer.
	stTexVertex * verticesPtr = (stTexVertex*)mappedResource.pData;

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)pVertices, (sizeof(stTexVertex) * 4));

	// Unlock the vertex buffer.
	IDXBase::GetInstance()->VGetDeviceContext()->Unmap(m_pVertexBuffer, 0);
	SAFE_DELETE_ARRAY(pVertices);
	return true;

	SAFE_DELETE_ARRAY(pVertices);
	return true;
}

// ***************************************************************
bool cSprite::InitializeShader()
{
	m_pShader = shared_ptr<IShader>(IShader::CreateTextureShader());
	return IShaderFactory::GetInstance()->VGetShader(m_pShader, "resources\\Shaders\\Texture.vsho",
		"resources\\Shaders\\Texture.psho");
}

// ***************************************************************
shared_ptr<ISprite> ISprite::CreateSprite()
{
	return shared_ptr<ISprite> (DEBUG_NEW cSprite());
}
