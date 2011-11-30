// ***************************************************************
//  Texture   version:  1.0   Ankur Sheel  date: 2011/07/21
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "Texture.h"
#include "ResourceManager.hxx"
#include "ResCache.hxx"
#include <memory>

using namespace Base;
using namespace Graphics;
using namespace Utilities;
using namespace std::tr1;

cTexture::cTexture()
: m_pTexture(NULL)
, m_dwHeight(0)
, m_dwWidth(0)
{

}

cTexture::~cTexture()
{
	Cleanup();
}

void Graphics::cTexture::Init( LPDIRECT3DDEVICE9 pDevice, const Base::cString & strFilename )
{
	SAFE_RELEASE(m_pTexture);	
	IResource * pResource = IResource::CreateResource(strFilename);
	shared_ptr<IResHandle> texture = IResourceManager::TheResourceManager()->GetResourceCache()->GetHandle(*pResource);

	if(texture.get() == NULL)
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Could not add to cache: %s", strFilename.GetData() ));
		PostQuitMessage(0);
	}
	// Create the texture associated with this sprite
	if(FAILED(D3DXCreateTextureFromFileInMemory(pDevice, texture->GetBuffer(), texture->GetSize(), &m_pTexture)))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Texture Creation failed : %s", strFilename.GetData() ));
		PostQuitMessage(0);
	}

	D3DXIMAGE_INFO imageInfo;	// contents of the image file	

	// get the contents of the image file
	D3DXGetImageInfoFromFileInMemory(texture->GetBuffer(), texture->GetSize(), &imageInfo);

	//get the image height and width
	m_dwHeight = imageInfo.Height;
	m_dwWidth = imageInfo.Width;
	SAFE_DELETE(pResource);

}

void Graphics::cTexture::Cleanup()
{
	SAFE_RELEASE(m_pTexture);
}
// ***************************************************************

std::tr1::shared_ptr<ITexture> Graphics::ITexture::CreateTexture()
{
	return std::tr1::shared_ptr<ITexture> (DEBUG_NEW cTexture());
}