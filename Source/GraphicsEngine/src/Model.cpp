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

// ***************************************************************
Graphics::cModel::cModel()
: m_pVertexBuffer(NULL)
, m_iVertexCount(0)
, m_iPrimitiveCount(0)
, m_iVertexSize(0)
{

}

// ***************************************************************
Graphics::cModel::~cModel()
{
	VCleanup();
}

// ***************************************************************
void Graphics::cModel::VOnInitialization(const cVertex * const pVertexData, 
									   const UINT iNumberOfVertices, 
									   const UINT iPrimitiveCount )
{
	m_iVertexSize = sizeof(cVertex);
	m_iPrimitiveCount = iPrimitiveCount;
	UINT nSizeOfData = iNumberOfVertices * m_iVertexSize; 
	HRESULT hr = IDXBase::GetInstance()->VGetDevice()->CreateVertexBuffer(nSizeOfData, 
		D3DUSAGE_WRITEONLY,
		cVertex::FVF,
		D3DPOOL_MANAGED,
		&m_pVertexBuffer,
		NULL);

	void * pData;
	hr = m_pVertexBuffer->Lock(0,0,(void**)&pData,0);
	memcpy(pData, pVertexData, nSizeOfData);
	hr = m_pVertexBuffer->Unlock();
}

// ***************************************************************
void Graphics::cModel::VRender()
{
	//IDXBase::GetInstance()->VGetDevice()->SetFVF(cVertex::FVF);
	HRESULT hr = IDXBase::GetInstance()->VGetDevice()->SetStreamSource(0, m_pVertexBuffer, 0, m_iVertexSize);
	hr = IDXBase::GetInstance()->VGetDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_iPrimitiveCount);
}

// ***************************************************************
void Graphics::cModel::VCleanup()
{
	SAFE_RELEASE(m_pVertexBuffer);
}

// ***************************************************************
int Graphics::cModel::GetVertexCount()
{
	return m_iVertexCount;
}

// ***************************************************************
Graphics::IModel * Graphics::IModel::CreateModel()
{
	IModel * pModel= DEBUG_NEW cModel();
	return pModel;
}
