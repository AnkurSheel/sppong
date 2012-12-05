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
#include "DxBase.hxx"
#include <D3DX11tex.h>

using namespace Base;
using namespace Graphics;
using namespace Utilities;

// ***************************************************************
cTexture::cTexture()
: m_pTexture(NULL)
{

}

// ***************************************************************
cTexture::~cTexture()
{
	Cleanup();
}

// ***************************************************************
bool Graphics::cTexture::Initialize( const Base::cString & strTexturePath )
{
	SAFE_RELEASE(m_pTexture);	
	shared_ptr<IResource> pResource = shared_ptr<IResource>(IResource::CreateResource(strTexturePath));
	shared_ptr<IResHandle> texture = IResourceManager::GetInstance()->VGetResourceCache()->GetHandle(*pResource);

	HRESULT result;
	if(texture.get() != NULL)
	{
		Log_Write_L1(ILogger::LT_ERROR, "Could not find in cache : " + strTexturePath);
	
		// Create the texture associated with this sprite
		result = D3DX11CreateShaderResourceViewFromMemory(IDXBase::GetInstance()->VGetDevice(), 
			texture->GetBuffer(), texture->GetSize(), NULL, NULL, &m_pTexture, NULL);
		if (FAILED(result))
		{
			result = D3DX11CreateShaderResourceViewFromFile(IDXBase::GetInstance()->VGetDevice(), 
				strTexturePath.GetData(), NULL, NULL, &m_pTexture, NULL);
			if (FAILED(result))
			{
				Log_Write_L1(ILogger::LT_ERROR, "Texture Creation failed " + strTexturePath + " " 
				+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result));
				return false;
			}
		}
		return true;
	}
	return false;
}

// ***************************************************************
ID3D11ShaderResourceView* Graphics::cTexture::VGetTexture() const
{
	return m_pTexture;
}

// ***************************************************************
void Graphics::cTexture::Cleanup()
{
	SAFE_RELEASE(m_pTexture);
}

// ***************************************************************
shared_ptr<ITexture> Graphics::ITexture::CreateTexture(const Base::cString & strTexturePath)
{
	shared_ptr<cTexture> ptr(DEBUG_NEW cTexture());
	if(!ptr->Initialize(strTexturePath))
	{
		return shared_ptr<ITexture>();
	}
	return ptr;

}