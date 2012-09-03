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

using namespace Utilities;
using namespace Graphics;
using namespace Base;
// ***************************************************************
// Constructor
// ***************************************************************
cSprite::cSprite()
: m_pSprite(NULL)
, m_dwHeight(0)
, m_dwWidth(0)
, m_vScale(D3DXVECTOR3(1.0f, 1.0f, 0.0f))
, m_vPosition(cVector3(-1.0f, -1.0f, -1.0f))
, m_bIsVisible(true)
, m_dwFlags(NULL)
, m_tintColor(cColor::WHITE)
, m_pSrcRect(NULL)
{
	D3DXMatrixIdentity(&m_mScaleMatrix) ; 
	D3DXMatrixScaling(&m_mScaleMatrix, m_vScale.x, m_vScale.y, m_vScale.z);
}
// ***************************************************************

// ***************************************************************
// Destructor
// ***************************************************************
cSprite::~cSprite()
{
	Cleanup();
}
// ***************************************************************

// ***************************************************************
// Initialize the sprite
// ***************************************************************
void cSprite::Init(shared_ptr<ITexture> const pTexture)
{
	if (m_pSprite)
	{
		Cleanup();
	}
	// Create the Sprite
	if (FAILED(	D3DXCreateSprite(IDXBase::GetInstance()->VGetDevice(), &m_pSprite))) 
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Sprite Creation failed : %s", m_strFilename.GetData() ));
		PostQuitMessage(0);
	}

	if (!m_pTexture)
	{
		m_pTexture = pTexture;
	}

	m_dwHeight = m_pTexture->GetHeight();
	m_dwWidth = m_pTexture->GetWidth();
}
// ***************************************************************

// ***************************************************************
// Initialize the sprite
// ***************************************************************
void cSprite::Init(const cString & strFilename)
{

	m_strFilename = strFilename;

	Log_Write_L2(ILogger::LT_EVENT, cString(100, "Loading Sprite : %s", strFilename.GetData()));

	if (m_pTexture == NULL)
	{
		m_pTexture = ITexture::CreateTexture();
	}
	
	m_pTexture->Init(IDXBase::GetInstance()->VGetDevice(), strFilename);

	Init(m_pTexture);

}
// ***************************************************************

// ***************************************************************
// Set the scaling information of the sprite according to the 
// required size
// ***************************************************************
void cSprite::SetSize( const float fNewWidth, const float fNewHeight )
{
	if (m_dwWidth == 0 || m_dwHeight == 0)
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Sprite height or width is 0"));
	}

	m_vScale.x = (float)fNewWidth/m_dwWidth;
	m_vScale.y = (float)fNewHeight/m_dwHeight;
	m_vScale.z = 1.0f;

	// create the scale matrix
	D3DXMatrixScaling(&m_mScaleMatrix, m_vScale.x, m_vScale.y, m_vScale.z);

	if(m_pSprite)
	{
		m_pSprite->SetTransform(&m_mScaleMatrix);
	}
	MakeTransformMatrix();
}
// ***************************************************************

// ***************************************************************
// Render the sprite
// ***************************************************************
void cSprite::VOnRender(const AppMsg & msg)
{
	// draw the sprite
	m_pSprite->Begin(m_dwFlags);
	m_pSprite->Draw(m_pTexture->GetTexture(), m_pSrcRect, NULL, NULL, m_tintColor.GetColor()); 
	m_pSprite->End();
}
// ***************************************************************

void cSprite::SetPosition(const cVector3& vPosition)
{
	if(m_vPosition != vPosition)
	{
		m_vPosition = vPosition ;
		MakeTransformMatrix();
	}
}
// ***************************************************************

void cSprite::VOnLostDevice()
{
	Cleanup();
}
// ***************************************************************

HRESULT cSprite::VOnResetDevice()
{
	if (m_strFilename.IsEmpty())
	{
		Init(m_pTexture);
	}
	else
	{
		Init(m_strFilename);
	}
	MakeTransformMatrix();
	return S_OK;
}
// ***************************************************************

// ***************************************************************
// Release the texture and sprites
// ***************************************************************
void cSprite::Cleanup()
{
	Log_Write_L2(ILogger::LT_EVENT, cString(100, "Releasing Sprite : %s", m_strFilename.GetData()));

	SAFE_DELETE(m_pSrcRect)

	// release the sprite
	SAFE_RELEASE(m_pSprite);
}
// ***************************************************************

void cSprite::MakeTransformMatrix()
{
	D3DXMATRIX transMatrix;
	D3DXMatrixTranslation(&transMatrix, m_vPosition.m_dX, m_vPosition.m_dY, m_vPosition.m_dZ);
	D3DXMatrixMultiply(&transMatrix, &m_mScaleMatrix, &transMatrix);
	m_pSprite->SetTransform(&transMatrix);
}
// ***************************************************************

bool cSprite::VIsVisible() const
{
	return m_bIsVisible;
}
// ***************************************************************

void cSprite::SetFlags(const DWORD dwFlags)
{
	m_dwFlags = dwFlags;
}
// ***************************************************************

void cSprite::SetTintColor(const Base::cColor & tintColor)
{
	m_tintColor = tintColor;
}	
// ***************************************************************

void cSprite::SetSourceRect(const RECT & rectSrc)
{
	SAFE_DELETE(m_pSrcRect);
	m_pSrcRect = DEBUG_NEW RECT(rectSrc);
}
// ***************************************************************

// ***************************************************************
// Creates a Sprite
// ***************************************************************
shared_ptr<ISprite> ISprite::CreateSprite()
{
	return shared_ptr<ISprite> (DEBUG_NEW cSprite());
}
// ***************************************************************