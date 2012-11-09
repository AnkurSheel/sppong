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
#include "TextureShader.h"
#include "Camera.h"
#include "Texture.hxx"
#include "ShaderManager.hxx"
#include "TextureManager.hxx"
#include "ObjModelLoader.h"

using namespace Utilities;
using namespace Base;
using namespace Graphics;

// ***************************************************************
cModel::cModel()
: m_pVertexBuffer(NULL)
, m_pIndexBuffer(NULL)
, m_iVertexCount(0)
, m_iIndexCount(0)
, m_iVertexSize(0)
, m_bIsDirty(false)
{

}

// ***************************************************************
cModel::~cModel()
{
	VCleanup();
}

// ***************************************************************
bool cModel::VOnInitialization(const stModelDef & def)
{
	m_iVertexCount = def.iNumberOfVertices;
	m_iIndexCount = def.iNumberOfIndices;
	m_iVertexSize = sizeof(stTexVertex);

	if(!CreateVertexBuffer(def.pVertices))
		return false;

	if(!CreateIndexBuffer(def.pIndices))
		return false;

	for (int i=0; i<def.vSubsetsDef.size(); i++)
	{
		stObjectSubset subset;
		subset.m_iIndexCountInSubset = def.vSubsetsDef[i].iNumberOfIndicesinSubset;
		subset.m_diffuseColor = def.vSubsetsDef[i].diffuseColor;
		subset.m_iStartIndexNo = def.vSubsetsDef[i].iStartIndexNo;
		if(!def.vSubsetsDef[i].strDiffuseTextureFilename.IsEmpty())
		{
			subset.m_pTexture = ITextureManager::GetInstance()->VGetTexture(def.vSubsetsDef[i].strDiffuseTextureFilename);
		}
		
		m_vSubsets.push_back(subset);
	}



	

	shared_ptr<IShader> pShader = shared_ptr<IShader>(IShader::CreateTextureShader());
	bool bSuccess = IShaderManager::GetInstance()->VGetShader(pShader, "resources\\Shaders\\Texture.vsho",
		"resources\\Shaders\\Texture.psho");
	m_pShader = dynamic_pointer_cast<cTextureShader>(pShader);
	return bSuccess;

}

// ***************************************************************
void cModel::VRender(const ICamera * const pCamera)
{
	unsigned int stride = m_iVertexSize;
	unsigned int offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	 IDXBase::GetInstance()->VGetDeviceContext()->IASetVertexBuffers(0, 1, 
		 &m_pVertexBuffer, &stride, &offset);

	 IDXBase::GetInstance()->VGetDeviceContext()->IASetIndexBuffer(m_pIndexBuffer,
		 DXGI_FORMAT_R32_UINT, 0);

	IDXBase::GetInstance()->VGetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	IDXBase::GetInstance()->VTurnZBufferOn();

	D3DXMATRIX worldMatrix = IDXBase::GetInstance()->VGetWorldMatrix();
	D3DXMatrixRotationYawPitchRoll(&worldMatrix, m_vRotation.m_dY, m_vRotation.m_dX,
		m_vRotation.m_dZ);
	//scaling * rotation * transalation
	const cCamera * pCam = static_cast<const cCamera *>(pCamera);

	for (int i=0; i<m_vSubsets.size(); i++)
	{
		if (m_pShader)
		{
			m_pShader->SetTextColor(m_vSubsets[i].m_diffuseColor);
			m_pShader->VSetTexture(m_vSubsets[i].m_pTexture);
			m_pShader->VRender(worldMatrix, pCam->GetViewMatrix(), 
				IDXBase::GetInstance()->VGetProjectionMatrix());
		}

		IDXBase::GetInstance()->VGetDeviceContext()->DrawIndexed(m_vSubsets[i].m_iIndexCountInSubset,
			m_vSubsets[i].m_iStartIndexNo, 0);
	}

}

// *************************************************************************
void cModel::VSetRotation(const cVector3 & vRadians)
{
	/*if (fRadians>0)
		m_fRotation = fmod(fRadians + Pi, TwoPi) - Pi;
	else
		m_fRotation = fmod(fRadians - Pi, TwoPi) + Pi;
*/
	if(m_vRotation != vRadians)
	{
		m_bIsDirty = true;
		m_vRotation.m_dX = ClampToTwoPi(m_vRotation.m_dX);
		m_vRotation.m_dY = ClampToTwoPi(m_vRotation.m_dY);
		m_vRotation.m_dZ = ClampToTwoPi(m_vRotation.m_dZ);
	}
}

// *************************************************************************
cVector3 cModel::VGetRotation() const
{
	return m_vRotation;
}

// ***************************************************************
void cModel::VCleanup()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
	m_vSubsets.clear();
}

// ***************************************************************
bool cModel::CreateVertexBuffer( const stTexVertex * const pVertices )
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
bool cModel::CreateIndexBuffer(const unsigned long * const pIndices)
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
IModel * IModel::CreateModel()
{
	IModel * pModel= DEBUG_NEW cModel();
	return pModel;
}