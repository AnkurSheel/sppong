// ***************************************************************
//  XMLFileIO   version:  1.0   Ankur Sheel  date: 2011/02/01
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "XMLFileIO.h"
#include "tinyxml.h"

using namespace Base;
using namespace Utilities;

// ***************************************************************
// Constructor
// ***************************************************************
cXMLFileIO::cXMLFileIO()
: m_pDoc(NULL)
, m_pRoot(NULL)
{
}
// ***************************************************************

// ***************************************************************
// Destructor
// ***************************************************************
cXMLFileIO::~cXMLFileIO()
{
	if (m_pDoc)
	{
		m_pDoc->Clear();
	}
	SAFE_DELETE(m_pDoc);
	m_ElementMap.clear();
}

// ***************************************************************
// Init : Initialises the xml file with the root as the rootname
// ***************************************************************
void cXMLFileIO::Init( const cString & strRootId, const cString & strRootName, const cString & strStyleSheetPath /*= ""*/ )
{
	SAFE_DELETE(m_pDoc);
	m_pDoc = DEBUG_NEW TiXmlDocument();

	TiXmlDeclaration* decl = DEBUG_NEW TiXmlDeclaration( "1.0", "", "" );  
	m_pDoc->LinkEndChild( decl ); 

	if (!strStyleSheetPath.IsEmpty())
	{
		TiXmlStylesheetReference *pRef = DEBUG_NEW TiXmlStylesheetReference("text/xsl", strStyleSheetPath.GetData());
		m_pDoc->LinkEndChild(pRef);
	}
	TiXmlElement * root = DEBUG_NEW TiXmlElement(strRootName.GetData());  
	m_pDoc->LinkEndChild( root );  

	m_ElementMap.insert(std::make_pair(strRootId.GetData(), root));
}
// ***************************************************************

// ***************************************************************
// Init : Initialises the xml file with the root as the rootname
// ***************************************************************
void cXMLFileIO::AddComment( const cString & strParentId, const cString & strComment )
{
	TiXmlComment*	comment;

	comment = DEBUG_NEW TiXmlComment();
	comment->SetValue(strComment.GetData()); 
	ElementMap::iterator  curr = m_ElementMap.find(strParentId.GetData());
	const_cast<TiXmlElement*> (curr->second)->LinkEndChild(comment);
}
// ***************************************************************

// ***************************************************************
// AddNode : Adds a node to the xml document
// ***************************************************************
void cXMLFileIO::AddNode( const cString & strParentId, const cString & strId, const cString & strNode, const cString & strNodeValue )
{
	TiXmlElement *element = DEBUG_NEW TiXmlElement(strNode.GetData());
	element->LinkEndChild(DEBUG_NEW TiXmlText(strNodeValue.GetData()));
	ElementMap::iterator  curr = m_ElementMap.find(strParentId.GetData());
	const_cast<TiXmlElement*> (curr->second)->LinkEndChild(element);
	m_ElementMap.insert(std::make_pair(strId.GetData(), element));
}
// ***************************************************************

// ***************************************************************
// AddNode : Adds a node to the xml document
// ***************************************************************
void cXMLFileIO::AddAttribute(const cString & strId, const cString & strAttributeNode, const int iValue )
{
	ElementMap::iterator  curr = m_ElementMap.find(strId.GetData());
	const_cast<TiXmlElement*> (curr->second)->SetAttribute(strAttributeNode.GetData(), iValue);
}
// ***************************************************************

// ***************************************************************
// AddNode : Adds a node to the xml document
// ***************************************************************
void cXMLFileIO::AddAttribute( const cString & strId, const cString & strAttributeNode, const cString & strValue )
{
	ElementMap::iterator  curr = m_ElementMap.find(strId.GetData());
	const_cast<TiXmlElement*> (curr->second)->SetAttribute(strAttributeNode.GetData(), strValue.GetData());

}
// ***************************************************************

// ***************************************************************
// AddNode : Adds a node to the xml document
// ***************************************************************
void cXMLFileIO::Save( const cString & strFilePath )
{
	m_pDoc->SaveFile(strFilePath.GetData());
}
// ***************************************************************

// ***************************************************************
// AddNode : Adds a node to the xml document
// ***************************************************************
cString cXMLFileIO::Load( const cString & strFilePath )
{
	SAFE_DELETE(m_pDoc);
	m_pDoc = DEBUG_NEW TiXmlDocument(strFilePath.GetData());
	if (!m_pDoc->LoadFile(strFilePath.GetData()))
	{
		return NULL;
	}

	TiXmlHandle hDoc(m_pDoc);
	m_pRoot = hDoc.FirstChildElement().ToElement();
	m_ElementMap.insert(std::make_pair(m_pRoot->Value(), m_pRoot));
	return(m_pRoot->Value());
}
// ***************************************************************

// ***************************************************************
// AddNode : Adds a node to the xml document
// ***************************************************************
cString cXMLFileIO::GetNodeName( const cString & strParent, const int iIndex )
{
	TiXmlElement *pElem;

	ElementMap::iterator  curr = m_ElementMap.find(strParent.GetData());
	TiXmlElement *pParent =const_cast<TiXmlElement*> (curr->second);
	pElem = pParent->FirstChildElement();
	for(int i=0;i<iIndex;i++)
	{
		pElem = pElem->NextSiblingElement();
	}
	//m_ElementMap.insert(std::make_pair(pElem->Value(), pElem));
	return(pElem->Value());
}
// ***************************************************************

// ***************************************************************
// AddNode : Adds a node to the xml document
// ***************************************************************
cString cXMLFileIO::GetNodeValue( const cString & strNode )
{
	TiXmlElement *pElem;

	ElementMap::iterator  curr = m_ElementMap.find(strNode.GetData());
	pElem =const_cast<TiXmlElement*> (curr->second);
	//pElem = pParent->FirstChildElement()->ToElement();
	return(pElem->GetText());
}
// ***************************************************************

IXMLFileIO * IXMLFileIO::CreateXMLFile()
{
	cXMLFileIO* pXMLFile= DEBUG_NEW cXMLFileIO();
	return pXMLFile;
}
// ***************************************************************

