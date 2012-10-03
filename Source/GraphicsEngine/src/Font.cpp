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
	Cleanup();
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

void cMyFont::Cleanup()
{
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
void cMyFont::ParseFontDesc()
{
	IXMLFileIO * pFile = IXMLFileIO::CreateXMLFile();
	pFile->VLoad(m_strFontDescFilename);
	
	pFile->VGetNodeAttribute("page0", "file", m_strFontTexFilename);

	pFile->VGetNodeAttribute("common", "scaleW", m_iTextureWidth);
	pFile->VGetNodeAttribute("common", "scaleH", m_iTextureHeight);

	std::vector<cString> vCharIDs;
	pFile->VGetAllChildrenNames("chars", vCharIDs);
	int iNoOfCharacters = vCharIDs.size();
	CharDescriptor ch;
	for (int i=0; i<iNoOfCharacters; i++)
	{
		pFile->VGetNodeAttribute(vCharIDs[i], "id", ch.id);
		pFile->VGetNodeAttribute(vCharIDs[i], "x", ch.x);
		pFile->VGetNodeAttribute(vCharIDs[i], "y", ch.y);
		pFile->VGetNodeAttribute(vCharIDs[i], "width", ch.Width);
		pFile->VGetNodeAttribute(vCharIDs[i], "height", ch.Height);
		pFile->VGetNodeAttribute(vCharIDs[i], "xoffset", ch.XOffset);
		pFile->VGetNodeAttribute(vCharIDs[i], "yoffset", ch.YOffset);
		pFile->VGetNodeAttribute(vCharIDs[i], "xadvance", ch.XAdvance);
		
		m_CharDescriptorMap.insert(std::make_pair(ch.id, ch));
	}
}
// ***************************************************************
void cMyFont::VInitialize(const Base::cString & strFontDescFilename)
{		
	m_strFontDescFilename = strFontDescFilename;
	ParseFontDesc();

	m_pTexture = ITexture::CreateTexture();
	m_pTexture->VInitialize(m_strFontTexFilename);
}
// ***************************************************************
void cMyFont::VSetText(const cString & strText)
{
	m_strText = strText;
	int istrLength = m_strText.GetLength();
	stTexVertex * pVertices = DEBUG_NEW stTexVertex[istrLength * 4];
	unsigned long * pIndices= DEBUG_NEW unsigned long[istrLength * 6];
	int curX = 0;
	for (int i=0; i<istrLength; i++)
	{
		int val = (int)m_strText[i];
		CharDescriptorMap::const_iterator curr = m_CharDescriptorMap.find(val);
		const CharDescriptor ch = curr->second;

		//lower left
		pVertices[i*4].m_fTex0 = (float) ch.x / (float) m_iTextureWidth;
		pVertices[i*4].m_fTex1 = (float) (ch.y + ch.Height) / (float) m_iTextureHeight;
		pVertices[i*4].m_fX = (float) curX + ch.XOffset;
		pVertices[i*4].m_fY = (float) ch.Height + ch.YOffset;
		pVertices[i*4+1].m_fZ = 0.0f;

		//upper left
		pVertices[i*4+1].m_fTex0 = (float) ch.x/ (float) m_iTextureWidth;
		pVertices[i*4+1].m_fTex1 = (float) ch.y / (float) m_iTextureHeight;
		pVertices[i*4+1].m_fX = (float) curX + ch.XOffset;
		pVertices[i*4+1].m_fY = (float) ch.YOffset;
		pVertices[i*4+1].m_fZ = 0.0f;

		//lower right
		pVertices[i*4+2].m_fTex0 = (float) (ch.x + ch.Width) / (float) m_iTextureWidth;
		pVertices[i*4+2].m_fTex1 = (float) (ch.y + ch.Height) / (float)m_iTextureHeight;
		pVertices[i*4+2].m_fX = (float) ch.Width + curX + ch.XOffset;
		pVertices[i*4+2].m_fY = (float) ch.Height + ch.YOffset;
		pVertices[i*4+1].m_fZ = 0.0f;

		//upper right
		pVertices[i*4+3].m_fTex0 = (float) (ch.x + ch.Width) / (float)m_iTextureWidth;
		pVertices[i*4+3].m_fTex1 = (float) ch.y / (float) m_iTextureHeight;
		pVertices[i*4+3].m_fX = (float) ch.Width + curX + ch.XOffset;
		pVertices[i*4+3].m_fY = (float) ch.YOffset;
		pVertices[i*4+1].m_fZ = 0.0f;

		pIndices[i*6] = i*6;
		pIndices[i*6+1] = i*6+1;
		pIndices[i*6+2] = i*6+2;
		pIndices[i*6+3] = i*6+1;
		pIndices[i*6+4] = i*6+3;
		pIndices[i*6+5] = i*6+2;

		curX += ch.XAdvance;
	}

	SAFE_DELETE_ARRAY(pVertices);
	SAFE_DELETE_ARRAY(pIndices);
	
}
