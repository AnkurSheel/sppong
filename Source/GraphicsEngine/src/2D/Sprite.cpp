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

using namespace Utilities;
using namespace Graphics;
using namespace Base;
// ***************************************************************
// Constructor
// ***************************************************************
cSprite::cSprite()
: m_pSprite(NULL)
, m_pTexture(NULL)
, m_uiHeight(0)
, m_uiWidth(0)
, m_vScale(D3DXVECTOR3(1.0f, 1.0f, 0.0f))
, m_vPosition(D3DXVECTOR3(-1.0f, -1.0f, -1.0f))
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
void cSprite::Init( LPDIRECT3DDEVICE9 const pDevice, const cString & strFilename )
{
	Log_Write_L2(ILogger::LT_EVENT, cString(100, "Loading Sprite : %s", strFilename.GetData()));

	m_strFilename = strFilename;

	if (m_pSprite)
	{
		Cleanup();
	}
	// Create the Sprite
	if (FAILED(	D3DXCreateSprite(pDevice, &m_pSprite))) 
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Sprite Creation failed : %s", strFilename.GetData() ));
		PostQuitMessage(0);
	}

	// Create the texture associated with this sprite
	if(FAILED(D3DXCreateTextureFromFile(pDevice, strFilename.GetData(), &m_pTexture)))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Texture Creation failed : %s", strFilename.GetData() ));
		PostQuitMessage(0);
	}

	D3DXIMAGE_INFO imageInfo;	// contents of the image file	

	// get the contents of the image file
	D3DXGetImageInfoFromFile(strFilename.GetData(), &imageInfo);

	//get the image height and width
	m_uiHeight = imageInfo.Height;
	m_uiWidth = imageInfo.Width;
}
// ***************************************************************

// ***************************************************************
// Set the scaling information of the sprite according to the 
// required size
// ***************************************************************
void cSprite::SetSize( const float fNewWidth, const float fNewHeight )
{
	m_vScale.x = (float)fNewWidth/m_uiWidth;
	m_vScale.y = (float)fNewHeight/m_uiHeight;
	m_vScale.z = 1.0f;

	// create the scale matrix
	D3DXMatrixScaling(&m_mScaleMatrix, m_vScale.x, m_vScale.y, m_vScale.z);

	m_pSprite->SetTransform(&m_mScaleMatrix);

}
// ***************************************************************

// ***************************************************************
// Render the sprite
// ***************************************************************
void cSprite::DrawSprite( LPDIRECT3DDEVICE9 const pDevice, 
						 const D3DXVECTOR3& vPosition, 
						 const DWORD dwFlags /*= NULL*/, 
						 const D3DCOLOR& tint /*= WHITE*/, 
						 const RECT* pSrcRect /*= NULL*/ )
{

	// get the new position and create the transform matrix
	if (m_vPosition != vPosition)
	{
		D3DXMATRIX transMatrix;
		D3DXMatrixTranslation(&transMatrix, vPosition.x, vPosition.y, vPosition.z);
		D3DXMatrixMultiply(&transMatrix, &m_mScaleMatrix, &transMatrix);
		m_vPosition = vPosition ;
		m_pSprite->SetTransform(&transMatrix);
	}

	// draw the sprite
	m_pSprite->Begin(dwFlags);
	m_pSprite->Draw(m_pTexture, pSrcRect, NULL, NULL, tint); 
	m_pSprite->End();
}
// ***************************************************************

// ***************************************************************
// Release the texture and sprites
// ***************************************************************
void cSprite::Cleanup()
{
	m_vPosition = D3DXVECTOR3(0,0,0);

	Log_Write_L2(ILogger::LT_EVENT, cString(100, "Releasing Texture : %s", m_strFilename.GetData()));

	// release the texture
	SAFE_RELEASE(m_pTexture);

	// release the sprite
	SAFE_RELEASE(m_pSprite);
}
// ***************************************************************

// ***************************************************************
// Creates a Sprite
// ***************************************************************
ISprite * ISprite::CreateSprite()
{
	cSprite* pSprite = DEBUG_NEW cSprite();
	return pSprite;
}
// ***************************************************************
