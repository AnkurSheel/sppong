// *****************************************************************************
//  Font   version:  1.0   Ankur Sheel  date: 05/16/2008
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "Font.h"
#include "XMLFileIO.hxx"
#include "Texture.hxx"
#include "FontShader.h"
#include "ResourceManager.hxx"
#include "ResCache.hxx"
#include "ShaderManager.hxx"
#include "TextureManager.hxx"
#include "GameDirectories.h"

using namespace Graphics;
using namespace Base;
using namespace Utilities;

// *****************************************************************************
cMyFont::cMyFont()
: m_iTextureWidth(0)
, m_iTextureHeight(0)
{
}

// *****************************************************************************
cMyFont::~cMyFont()
{
	Cleanup();
}

// *****************************************************************************
bool cMyFont::VInitialize(const Base::cString & strFontDescFilename)
{		
	ParseFontDesc(strFontDescFilename);
	Log_Write_L2(ILogger::LT_EVENT, "Loading Sprite : " + m_strFontTexPath);

	if (m_pTexture == NULL)
	{
		m_pTexture = ITextureManager::GetInstance()->VGetTexture(m_strFontTexPath);
	}

	if(!InitializeShader())
		return false;

	return true;
	
}

// *****************************************************************************
void cMyFont::VRender(const D3DXMATRIX & inMatWorld, const D3DXMATRIX & inMatView,
					  const D3DXMATRIX & inMatProjection, const cColor & textColor)
{
	if (m_pShader)
	{
		m_pShader->SetDiffuseColor(textColor);
		m_pShader->VSetTexture(m_pTexture);
		m_pShader->VRender(inMatWorld, inMatView, inMatProjection);
	}

}

// *****************************************************************************
IMyFont::stVertexData cMyFont::VGetCharVertexData(const int iCharAsciiValue)
{
	stVertexData vertexData;
	CharDescriptorMap::const_iterator curr = m_CharDescriptorMap.find(iCharAsciiValue);
	if (curr != m_CharDescriptorMap.end())
	{
		CharDescriptor ch = curr->second;
		vertexData.ch = ch;
		vertexData.fTexU = (float(ch.x)+0.5f) / float (m_iTextureWidth);
		vertexData.fTexV = (float(ch.y)+0.5f) / float (m_iTextureHeight);
		vertexData.fTexU1 = float(ch.x + ch.Width) / float (m_iTextureWidth);
		vertexData.fTexV1 = float(ch.y + ch.Height) / float (m_iTextureHeight);
	}
	else
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Could not find char descriptor for ascii value : %d", iCharAsciiValue));
	}
	return vertexData;
}

// *****************************************************************************
int cMyFont::VGetFontHeight() const
{
	return m_iFontHeight;
}

// *****************************************************************************
void cMyFont::Cleanup()
{
	m_CharDescriptorMap.clear();
}

// *****************************************************************************
void cMyFont::ParseFontDesc(const cString & strFontDescFilename)
{
	IXMLFileIO * pFile = IXMLFileIO::CreateXMLFile();

	IResource * pResource = IResource::CreateResource(cGameDirectories::GameDirectories().strFontDirectory
		+ strFontDescFilename + ".fnt");
	shared_ptr<IResHandle> fontDesc = IResourceManager::GetInstance()->VGetResourceCache()->GetHandle(*pResource);
	pFile->VParse(fontDesc->GetBuffer(), fontDesc->GetSize());

	m_strFontTexPath = cGameDirectories::GameDirectories().strFontDirectory + pFile->VGetNodeAttribute("page0", "file");
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

// *****************************************************************************
bool cMyFont::InitializeShader()
{
	shared_ptr<IShader> pShader = shared_ptr<IShader>(IShader::CreateFontShader());
	bool bSuccess = IShaderManager::GetInstance()->VGetShader(pShader, "Font");
	m_pShader = dynamic_pointer_cast<cFontShader>(pShader);
	return bSuccess;
}

// *****************************************************************************
IMyFont * IMyFont::CreateMyFont()
{
	return DEBUG_NEW cMyFont();
}