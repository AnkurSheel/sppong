// *************************************************************************
//  Sentence   version:  1.0   Ankur Sheel  date: 2012/10/10
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************
// ***************************************************************
//  Font   version:  1.0   Ankur Sheel  date: 05/16/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "Sentence.h"
#include "DxBase.hxx"
#include "vertexstruct.h"
#include "Font.h"
#include "Camera.h"

using namespace Graphics;
using namespace Base;
using namespace Utilities;

// ***************************************************************
cSentence::cSentence()
: m_pVertexBuffer(NULL)
, m_pIndexBuffer(NULL)
, m_TextColor(1.0f, 1.0f, 1.0f, 1.0f)
, m_iVertexCount(0)
, m_iIndexCount(0)
, m_vPosition(cVector2::Zero())
, m_bIsDirty(true)
{
}

// ***************************************************************
cSentence::~cSentence()
{
	Cleanup();
}

// ***************************************************************
void cSentence::VRender(const ICamera * const pCamera)
{
	IDXBase::GetInstance()->VTurnOnAlphaBlending();
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
	const cCamera * pCam = static_cast<const cCamera *>(pCamera);
	m_pFont->Render(IDXBase::GetInstance()->VGetWorldMatrix(),
		pCam->GetViewMatrix(), IDXBase::GetInstance()->VGetOrthoMatrix(), m_TextColor);
	IDXBase::GetInstance()->VGetDeviceContext()->DrawIndexed(m_iIndexCount, 0, 0);
	IDXBase::GetInstance()->VTurnOffAlphaBlending();
}

// ***************************************************************
void cSentence::VSetPosition(const Base::cVector2 & vPosition)
{
	m_vPosition = vPosition;
	m_bIsDirty = true;
}

// ***************************************************************
void cSentence::VSetText(const cString & strText)
{
	m_strText = strText;
	m_bIsDirty = true;
}

// ***************************************************************
void cSentence::VSetTextColor(const Base::cColor & colorText)
{
	float fRed, fBlue, fGreen, fAlpha;
	colorText.GetColorComponentsInFloat(fRed, fBlue, fGreen, fAlpha);
	m_TextColor = D3DXVECTOR4(fRed, fBlue, fGreen, fAlpha);
}

// ***************************************************************
bool cSentence::RecalculateVertexData()
{
	int istrLength = m_strText.GetLength();
	m_iIndexCount = istrLength * 6;

	m_iVertexCount = istrLength * 4;
	stTexVertex * pVertices = DEBUG_NEW stTexVertex[m_iVertexCount];

	float curX = -(float)IDXBase::GetInstance()->VGetScreenWidth()/2.0f + m_vPosition.m_dX;
	float curY = (float)IDXBase::GetInstance()->VGetScreenHeight()/2.0f - m_vPosition.m_dY;
	float left;
	float right;
	float top;
	float bottom;
	float u;
	float v;
	float u1;
	float v1;

	CharDescriptor ch;
	for (int i=0; i<istrLength; i++)
	{
		int val = (int)m_strText[i];
		m_pFont->GetCharVertexData(val, ch, u, v, u1, v1);

		left = curX + ch.XOffset;
		right = left + ch.Width;
		top = curY + ch.YOffset;
		bottom = top - ch.Height;

		// Create the vertex array.
		pVertices[i*4] = stTexVertex(left, bottom, 0.0f, u, v1);
		pVertices[i*4+1] = stTexVertex(left, top, 0.0f, u, v);
		pVertices[i*4+2] = stTexVertex(right, bottom, 0.0f, u1, v1);
		pVertices[i*4+3] = stTexVertex(right, top, 0.0f, u1, v);

		curX += ch.XAdvance;
	}

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
	memcpy(verticesPtr, (void*)pVertices, (sizeof(stTexVertex) * m_iVertexCount));

	// Unlock the vertex buffer.
	IDXBase::GetInstance()->VGetDeviceContext()->Unmap(m_pVertexBuffer, 0);
	SAFE_DELETE_ARRAY(pVertices);
	return true;

	SAFE_DELETE_ARRAY(pVertices);
	return true;
}

// ***************************************************************
bool cSentence::CreateIndexBuffer()
{
	m_iIndexCount = MAX_FILENAME_WIDTH * 6;
	unsigned long * pIndices= DEBUG_NEW unsigned long[m_iIndexCount];
	for (int i=0;i<MAX_FILENAME_WIDTH;i=i++)
	{
		pIndices[i*6] = i*4;
		pIndices[i*6+1] = i*4+1;
		pIndices[i*6+2] = i*4+2;
		pIndices[i*6+3] = i*4+1;
		pIndices[i*6+4] = i*4+3;
		pIndices[i*6+5] = i*4+2;
	}

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

	bool bSuccess;
	if(FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Could not create Index Buffer ")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
		bSuccess = false;
	}
	else
	{
		bSuccess = true;
	}

	SAFE_DELETE_ARRAY(pIndices);
	return bSuccess;
}

// ***************************************************************
void cSentence::Cleanup()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
}

// *************************************************************************
bool cSentence::VInitialize(shared_ptr<Graphics::IMyFont> pFont,
							const Base::cString & strText,
							const Base::cColor & textColor)
{
	m_pFont = static_pointer_cast<cMyFont>(pFont);

	m_iVertexCount = MAX_FILENAME_WIDTH * 4;

	if(!CreateVertexBuffer())
		return false;

	if(!CreateIndexBuffer())
		return false;

	m_vPosition = cVector2(-1.0f, -1.0f);
	VSetText(strText);
	VSetTextColor(textColor);
	m_bIsDirty = true;
	return true;
}

// *************************************************************************
bool cSentence::CreateVertexBuffer()
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
ISentence * ISentence::CreateSentence()
{
	return DEBUG_NEW cSentence();
}
