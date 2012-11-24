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
#include "BoundingBox.hxx"

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
, m_fBoundingSphereRadius(0)
, m_pAABB(NULL)
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

	CreateAABB(def);
	/*	float distX = (vMaxAABB.m_dX - m_vAABBMin.m_dX) / 2.0f;
	float distY = (vMaxAABB.m_dY - m_vAABBMin.m_dY) / 2.0f;
	float distZ = (vMaxAABB.m_dZ - m_vAABBMin.m_dZ) / 2.0f;

	m_vBoundingSphereCentre = cVector3(vMaxAABB.m_dX - distX, m_vAABBMax.m_dY - distY, m_vAABBMax.m_dZ - distZ);
	m_fBoundingSphereRadius = (distX * distX + distY * distY + distZ * distZ) / 2.0f;
*/
	VSetScale(cVector3(1.0f, 1.0f, 1.0f));

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

	if(m_bIsDirty)
	{
		ReCalculateTransformMatrix();
		m_bIsDirty = false;
	}
	const cCamera * pCam = static_cast<const cCamera *>(pCamera);

	for (int i=0; i<m_vSubsets.size(); i++)
	{
		if (m_pShader)
		{
			m_pShader->SetTextColor(m_vSubsets[i].m_diffuseColor);
			m_pShader->VSetTexture(m_vSubsets[i].m_pTexture);
			m_pShader->VRender(m_matTransform, pCam->GetViewMatrix(), 
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
		m_vRotation.m_dX = ClampToTwoPi(vRadians.m_dX);
		m_vRotation.m_dY = ClampToTwoPi(vRadians.m_dY);
		m_vRotation.m_dZ = ClampToTwoPi(vRadians.m_dZ);
	}
}

// *************************************************************************
cVector3 cModel::VGetRotation() const
{
	return m_vRotation;
}

// *************************************************************************
void cModel::VSetPosition(const Base::cVector3 & vPosition)
{
	if(m_vPosition != vPosition)
	{
		m_bIsDirty = true;
		m_vPosition = vPosition;
	}
}

// *************************************************************************
cVector3 cModel::VGetPosition() const
{
	return m_vPosition;
}

// *************************************************************************
void cModel::VSetScale(const Base::cVector3 & vScale)
{
	if(m_vScale!= vScale)
	{
		m_bIsDirty = true;
		m_vScale= vScale;
	}
}

// *************************************************************************
cVector3 cModel::VGetScale() const
{
	return m_vScale;
}

// ***************************************************************
void cModel::VCleanup()
{
	SAFE_DELETE(m_pAABB);
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

void cModel::ReCalculateTransformMatrix()
{
	D3DXMATRIX matRotation;
	D3DXMatrixRotationYawPitchRoll(&matRotation, m_vRotation.m_dY, m_vRotation.m_dX,
		m_vRotation.m_dZ);

	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, m_vScale.m_dX, m_vScale.m_dY, m_vScale.m_dZ);

	D3DXMATRIX matPosition;
	D3DXMatrixTranslation(&matPosition, m_vPosition.m_dX, m_vPosition.m_dY, m_vPosition.m_dZ);

	D3DXMatrixIdentity(&m_matTransform);
	m_matTransform = matScale * matRotation * matPosition;
	
	m_pAABB->VTransform(m_matTransform);
}

// *************************************************************************
void cModel::CreateAABB(const stModelDef & def)
{
	cVector3 vMinAABB(MaxFloat, MaxFloat, MaxFloat);
	cVector3 vMaxAABB(-MaxFloat, -MaxFloat, -MaxFloat);

	for (int i=0; i<m_iVertexCount; i++)
	{
		vMinAABB.m_dX = min(vMinAABB.m_dX, def.pVertices[i].m_fX);
		vMinAABB.m_dY = min(vMinAABB.m_dY, def.pVertices[i].m_fY);
		vMinAABB.m_dZ = min(vMinAABB.m_dZ, def.pVertices[i].m_fZ);

		//Get the largest vertex 
		vMaxAABB.m_dX = max(vMaxAABB.m_dX, def.pVertices[i].m_fX);
		vMaxAABB.m_dY = max(vMaxAABB.m_dY, def.pVertices[i].m_fY);
		vMaxAABB.m_dZ = max(vMaxAABB.m_dZ, def.pVertices[i].m_fZ);
	}

	m_pAABB = IBoundingBox::CreateBoundingBox(vMinAABB, vMaxAABB);
}


// ***************************************************************
IModel * IModel::CreateModel()
{
	IModel * pModel= DEBUG_NEW cModel();
	return pModel;
}