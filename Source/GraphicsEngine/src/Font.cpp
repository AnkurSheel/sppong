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
#include "DxBase.hxx"
#include "XMLFileIO.hxx"
#include "Optional.h"
#include "vertexstruct.h"
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
	VCleanup();
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

	m_iVertexCount = MAX_FILENAME_WIDTH * 4;

	if(!CreateVertexBuffer())
		return false;

	if(!VCreateIndexBuffer())
		return false;

	if(!InitializeShader())
		return false;

	m_vPosition = cVector2(-1.0f, -1.0f);
	return true;
	
}

// ***************************************************************
void cMyFont::VRender(const ICamera * const pCamera)
{
	IDXBase::GetInstance()->VTurnOnAlphaBlending();
	cSprite::VRender(pCamera);
	IDXBase::GetInstance()->VTurnOffAlphaBlending();
}

// ***************************************************************
void cMyFont::VSetPosition(const Base::cVector2 & vPosition)
{
	cSprite::VSetPosition(vPosition);
}

// ***************************************************************
void cMyFont::VSetText(const cString & strText)
{
	m_strText = strText;
	m_bIsDirty = true;
}

// ***************************************************************
void cMyFont::VSetTextColor(const Base::cColor & colorText)
{
	cFontShader * pFontShader = static_cast<cFontShader *>(m_pShader);
	pFontShader->SetTextColor(colorText);

}

// ***************************************************************
bool cMyFont::VRecalculateVertexData()
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

	for (int i=0; i<istrLength; i++)
	{
		int val = (int)m_strText[i];
		CharDescriptorMap::const_iterator curr = m_CharDescriptorMap.find(val);
		const CharDescriptor ch = curr->second;

		left = curX + ch.XOffset;
		right = left + ch.Width;
		top = curY + ch.YOffset;
		bottom = top - ch.Height;
		u = float(ch.x)/ float (m_iTextureWidth);
		v = float(ch.y)/ float (m_iTextureHeight);
		u1 = float(ch.x + ch.Width) / float (m_iTextureWidth);
		v1 = float(ch.y + ch.Height) / float (m_iTextureHeight);

		// Create the vertex array.
		pVertices[i*4] = stTexVertex(left, bottom, 0.0f, u, v1);
		pVertices[i*4+1] = stTexVertex(left, top, 0.0f, u, v);
		pVertices[i*4+2] = stTexVertex(right, bottom, 0.0f, u1, v1);
		pVertices[i*4+3] = stTexVertex(right, top, 0.0f, u1, v);

		curX += ch.XAdvance;
	}
	if(!UpdateVertexBuffer(pVertices, m_iVertexCount))
	{
		SAFE_DELETE_ARRAY(pVertices);
		return false;
	}

	SAFE_DELETE_ARRAY(pVertices);
	return true;
}

// ***************************************************************
bool cMyFont::VCreateIndexBuffer()
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
	
	bool bSuccess = CreateIndexBuffer(pIndices);
	SAFE_DELETE_ARRAY(pIndices);
	return bSuccess;
}

// ***************************************************************
void cMyFont::VCleanup()
{
	cSprite::VCleanup();
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
	m_pShader = IShader::CreateFontShader();
	if (!m_pShader->VInitialize("resources\\Shaders\\Font.vsho",
		"resources\\Shaders\\Font.psho"))
	{
		return false;
	}
	return true;
}

// ***************************************************************
shared_ptr<IMyFont> IMyFont::CreateMyFont()
{
	return shared_ptr<IMyFont> (DEBUG_NEW cMyFont());
}