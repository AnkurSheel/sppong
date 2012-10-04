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
#include "Shader.hxx"
#include "ResourceManager.hxx"
#include "ResCache.hxx"

using namespace Graphics;
using namespace Base;
using namespace Utilities;

// ***************************************************************
// Constructor
// ***************************************************************
cMyFont::cMyFont()
: m_iTextureWidth(0)
, m_iTextureHeight(0)
//: m_pFont(NULL)
//, m_Color(cColor::BLACK.GetColor())
//, m_bVisible(true)
//, m_iSpaceWidth(0)
{
	//m_boundingRect.top = 0;
	//m_boundingRect.bottom = 0;
	//m_boundingRect.left = 0;
	//m_boundingRect.right = 0;
}
// ***************************************************************

// ***************************************************************
// Constructor
// ***************************************************************
cMyFont::~cMyFont()
{
	VCleanup();
}
// ***************************************************************
//
//// ***************************************************************
//// Initializes the font
//// ***************************************************************
//void cMyFont::InitFont(const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const cString & strFaceName )
//{
//	ZeroMemory(&m_fonttype, sizeof(D3DXFONT_DESC)) ;
//	m_fonttype.Height		= iHeight ;
//	m_fonttype.Width		= iWidth ;
//	m_fonttype.Weight		= iWeight ;
//	m_fonttype.Italic		= bItalic ;
//	m_fonttype.CharSet		= charset ;
//	strcpy_s(m_fonttype.FaceName, LF_FACESIZE, strFaceName.GetData()) ;
//
//	D3DXCreateFontIndirect(IDXBase::GetInstance()->VGetDevice(), &m_fonttype, &m_pFont) ;
//
//	RECT rctA = {0,0,0,0};
//	m_pFont->DrawText(NULL, "_", -1, &rctA, DT_CALCRECT, cColor::BLACK.GetColor());
//
//	m_iSpaceWidth = rctA.right - rctA.left;
//}
//// ***************************************************************
//
//// ***************************************************************
//// Displays the text
//// ***************************************************************
//void cMyFont::VOnRender(const Graphics::AppMsg & msg)
//{	
//	m_pFont->DrawText(NULL, m_strString.GetData(), -1, &m_boundingRect, m_dwFormat, m_Color) ;
//}
//// ***************************************************************
//
//void cMyFont::VOnLostDevice()
//{
//	Cleanup();
//}
//// ***************************************************************
//
//HRESULT cMyFont::VOnResetDevice()
//{
//	return D3DXCreateFontIndirect(IDXBase::GetInstance()->VGetDevice(), &m_fonttype, &m_pFont);
//}
//// ***************************************************************

void cMyFont::VCleanup()
{
	cSprite::VCleanup();
	m_CharDescriptorMap.clear();
	//SAFE_DELETE_ARRAY(m_pChars);
	//SAFE_RELEASE(m_pFont);
}
// ***************************************************************
//
//void Graphics::cMyFont::CalculateAndSetRect()
//{
//	if (m_strString.IsEmpty())
//	{
//		Log_Write_L2(ILogger::LT_ERROR, "m_strString is empty");
//	}
//	if (m_pFont)
//	{
//		m_pFont->DrawText(NULL, m_strString.GetData(), -1, &m_boundingRect, DT_CALCRECT, m_Color);
//		AddTrailingSpaceWidth(m_strString, m_boundingRect);
//	}
//}
//// ***************************************************************
//
//const RECT Graphics::cMyFont::GetRect( const Base::cString & strText ) const
//{
//	if (strText.IsEmpty())
//	{
//		Log_Write_L2(ILogger::LT_ERROR, "Calculating Boundary Rectangle for Empty String");
//	}
//	RECT boundingRect;
//	boundingRect.top = 0;
//	boundingRect.bottom = 0;
//	boundingRect.left = 0;
//	boundingRect.right = 0;
//	m_pFont->DrawText(NULL, strText.GetData(), -1, &boundingRect, DT_CALCRECT, m_Color);
//	AddTrailingSpaceWidth(strText, boundingRect);
//	return boundingRect;
//}
//// ***************************************************************
//
//void Graphics::cMyFont::AddTrailingSpaceWidth( const Base::cString & strText , RECT & boundingRect ) const
//{
//	int index = strText.GetLength() - 1;
//	while(strText.GetData()[index] == ' ')
//	{
//		boundingRect.right += m_iSpaceWidth;
//		index--;
//	}
//}
// ***************************************************************
// Creates a font
// ***************************************************************
shared_ptr<IMyFont> IMyFont::CreateMyFont()
{
	return shared_ptr<IMyFont> (DEBUG_NEW cMyFont());
}
// ***************************************************************

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
void cMyFont::VSetText(const cString & strText)
{
	m_strText = strText;
	m_bIsDirty = true;
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
bool cMyFont::VRecalculateVertexData()
{
	int istrLength = m_strText.GetLength();
	m_iIndexCount = istrLength * 6;

	m_iVertexCount = istrLength * 4;
	stTexVertex * pVertices = DEBUG_NEW stTexVertex[m_iVertexCount];
	
	int curX = -(float)IDXBase::GetInstance()->VGetScreenWidth()/2.0f + m_vPosition.m_dX;
	int curY = (float)IDXBase::GetInstance()->VGetScreenHeight()/2.0f - m_vPosition.m_dY;

	for (int i=0; i<istrLength; i++)
	{
		int val = (int)m_strText[i];
		CharDescriptorMap::const_iterator curr = m_CharDescriptorMap.find(val);
		const CharDescriptor ch = curr->second;

		//lower left
		pVertices[i*4].m_fTex0 = (float) ch.x / (float) m_iTextureWidth;
		pVertices[i*4].m_fTex1 = (float) (ch.y + ch.Height) / (float) m_iTextureHeight;
		pVertices[i*4].m_fX = (float) curX + ch.XOffset;
		pVertices[i*4].m_fY = (float) curY + ch.Height + ch.YOffset;
		pVertices[i*4+1].m_fZ = 0.0f;

		//upper left
		pVertices[i*4+1].m_fTex0 = (float) ch.x/ (float) m_iTextureWidth;
		pVertices[i*4+1].m_fTex1 = (float) ch.y / (float) m_iTextureHeight;
		pVertices[i*4+1].m_fX = (float) curX + ch.XOffset;
		pVertices[i*4+1].m_fY = (float) curY + ch.YOffset;
		pVertices[i*4+1].m_fZ = 0.0f;

		//lower right
		pVertices[i*4+2].m_fTex0 = (float) (ch.x + ch.Width) / (float) m_iTextureWidth;
		pVertices[i*4+2].m_fTex1 = (float) (ch.y + ch.Height) / (float)m_iTextureHeight;
		pVertices[i*4+2].m_fX = (float) curY + ch.Width + curX + ch.XOffset;
		pVertices[i*4+2].m_fY = (float) curY + ch.Height + ch.YOffset;
		pVertices[i*4+1].m_fZ = 0.0f;

		//upper right
		pVertices[i*4+3].m_fTex0 = (float) (ch.x + ch.Width) / (float)m_iTextureWidth;
		pVertices[i*4+3].m_fTex1 = (float) ch.y / (float) m_iTextureHeight;
		pVertices[i*4+3].m_fX = (float) ch.Width + curX + ch.XOffset;
		pVertices[i*4+3].m_fY = (float) curY + ch.YOffset;
		pVertices[i*4+1].m_fZ = 0.0f;

		curX += ch.XAdvance;
	}
	if(!UpdateVertexBuffer(pVertices, m_iVertexCount))
	{
		SAFE_DELETE_ARRAY(pVertices);
		return false;
	}

	SAFE_DELETE_ARRAY(pVertices);
	return true;
	/*m_vSize = cVector2(256, 256);
	float left = -(float)IDXBase::GetInstance()->VGetScreenWidth()/2.0f + m_vPosition.m_dX;
	float right = left + m_vSize.m_dX;
	float top = (float)IDXBase::GetInstance()->VGetScreenHeight()/2.0f - m_vPosition.m_dY;
	float bottom = top - m_vSize.m_dY;

	// Create the vertex array.
	stTexVertex * pVertices = DEBUG_NEW stTexVertex [4];
	pVertices[0] = stTexVertex(left, bottom, 0.0f, 0.0f, 1.0f);
	pVertices[1] = stTexVertex(left, top, 0.0f, 0.0f, 0.0f);
	pVertices[2] = stTexVertex(right, bottom, 0.0f, 1.0f, 1.0f);
	pVertices[3] = stTexVertex(right, top, 0.0f, 1.0f, 0.0f);

	if(!UpdateVertexBuffer(pVertices, 4))
	{
		SAFE_DELETE_ARRAY(pVertices);
		return false;
	}

	SAFE_DELETE_ARRAY(pVertices);
	return true;*/
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
