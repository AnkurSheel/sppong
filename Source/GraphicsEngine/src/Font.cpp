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
#include "Font.h"
#include "XMLFileIO.hxx"
#include "Texture.hxx"
#include "FontShader.h"
#include "ResourceManager.hxx"
#include "ResCache.hxx"

using namespace Graphics;
using namespace Base;
using namespace Utilities;

// ***************************************************************
cMyFont::cMyFont()
: m_iTextureWidth(0)
, m_iTextureHeight(0)
{
}

// ***************************************************************
cMyFont::~cMyFont()
{
	Cleanup();
}

// ***************************************************************
bool cMyFont::VInitialize(const Base::cString & strFontDirPath,
						  const Base::cString & strFontDescFilename)
{		
	ParseFontDesc(strFontDirPath, strFontDescFilename);
	Log_Write_L2(ILogger::LT_EVENT, "Loading Sprite : " + m_strFontTexPath);

	if (m_pTexture == NULL)
	{
		m_pTexture = ITexture::CreateTexture();
	}
	m_pTexture->VInitialize(m_strFontTexPath);

	if(!InitializeShader())
		return false;

	return true;
	
}

// *************************************************************************
float cMyFont::GetFontHeight() const
{
	return m_iFontHeight;
}

// ***************************************************************
void cMyFont::Cleanup()
{
	SAFE_DELETE(m_pShader);
	m_CharDescriptorMap.clear();
}

// ***************************************************************
void cMyFont::ParseFontDesc(const cString & strFontDirPath,
							const cString & strFontDescFilename)
{
	IXMLFileIO * pFile = IXMLFileIO::CreateXMLFile();

	IResource * pResource = IResource::CreateResource(strFontDirPath + strFontDescFilename);
	shared_ptr<IResHandle> fontDesc = IResourceManager::GetInstance()->VGetResourceCache()->GetHandle(*pResource);
	pFile->VParse(fontDesc->GetBuffer(), fontDesc->GetSize());

	pFile->VGetNodeAttribute("page0", "file", m_strFontTexPath);
	m_strFontTexPath = strFontDirPath + m_strFontTexPath;
	m_iTextureWidth = pFile->VGetNodeAttributeAsInt("common", "scaleW");
	m_iTextureHeight = pFile->VGetNodeAttributeAsInt("common", "scaleH");
	m_iFontHeight = pFile->VGetNodeAttributeAsInt("common", "lineHeight");

 	std::vector<cString> vCharIDs;
	pFile->VGetAllChildrenNames("chars", vCharIDs);
	int iNoOfCharacters = vCharIDs.size();
	CharDescriptor ch;
	for (int i=0; i<iNoOfCharacters; i++)
	{
		ch.id = pFile->VGetNodeAttributeAsInt(vCharIDs[i], "id");
		ch.x = pFile->VGetNodeAttributeAsInt(vCharIDs[i], "x");
		ch.y = pFile->VGetNodeAttributeAsInt(vCharIDs[i], "y");
		ch.Width = pFile->VGetNodeAttributeAsInt(vCharIDs[i], "width");
		ch.Height = pFile->VGetNodeAttributeAsInt(vCharIDs[i], "height");
		ch.XOffset = pFile->VGetNodeAttributeAsInt(vCharIDs[i], "xoffset");
		ch.YOffset = pFile->VGetNodeAttributeAsInt(vCharIDs[i], "yoffset");
		ch.XAdvance = pFile->VGetNodeAttributeAsInt(vCharIDs[i], "xadvance");
		
		m_CharDescriptorMap.insert(std::make_pair(ch.id, ch));
	}
	SAFE_DELETE(pFile);
	SAFE_DELETE(pResource);

}

// ***************************************************************
bool cMyFont::InitializeShader()
{
	m_pShader = static_cast<cFontShader *>(IShader::CreateFontShader());
	if (!m_pShader->VInitialize("resources\\Shaders\\Font.vsho",
		"resources\\Shaders\\Font.psho"))
	{
		return false;
	}
	return true;
}

// ***************************************************************
void cMyFont::GetCharVertexData(const int iCharAsciiValue, CharDescriptor & ch,
								 float & fTexU, float & fTexV, float & fTexU1,
								 float & fTexV1)
{
	CharDescriptorMap::const_iterator curr = m_CharDescriptorMap.find(iCharAsciiValue);
	if (curr != m_CharDescriptorMap.end())
	{
		ch = (curr->second);
		fTexU = (float(ch.x)+0.5f) / float (m_iTextureWidth);
		fTexV = (float(ch.y)+0.5f) / float (m_iTextureHeight);
		fTexU1 = float(ch.x + ch.Width) / float (m_iTextureWidth);
		fTexV1 = float(ch.y + ch.Height) / float (m_iTextureHeight);
	}
}


// *************************************************************************
void cMyFont::GetCharVertexData(const int iCharAsciiValue, CharDescriptor & ch)
{
	CharDescriptorMap::const_iterator curr = m_CharDescriptorMap.find(iCharAsciiValue);
	if (curr != m_CharDescriptorMap.end())
	{
		ch = (curr->second);
	}
}

// *************************************************************************
void cMyFont::Render(const D3DXMATRIX & inMatWorld, const D3DXMATRIX & inMatView,
					  const D3DXMATRIX & inMatProjection, const D3DXVECTOR4 & textColor)
{
	if (m_pShader)
	{
		m_pShader->Render(inMatWorld, inMatView, inMatProjection, m_pTexture.get(), textColor);
	}

}

// ***************************************************************
IMyFont * IMyFont::CreateMyFont()
{
	return DEBUG_NEW cMyFont();
}