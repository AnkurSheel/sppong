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
#include "myString.h"

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
void cXMLFileIO::Init( Base::cString strRootId, Base::cString strRootName, Base::cString strStyleSheetPath /*= ""*/ )
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

	m_ElementMap.insert(std::make_pair(strRootId, root));
}
// ***************************************************************

// ***************************************************************
// Init : Initialises the xml file with the root as the rootname
// ***************************************************************
void cXMLFileIO::AddComment( Base::cString strParentId, Base::cString strComment )
{
	TiXmlComment*	comment;

	comment = DEBUG_NEW TiXmlComment();
	comment->SetValue(strComment.GetData()); 
	ElementMap::iterator  curr = m_ElementMap.find(strParentId);
	const_cast<TiXmlElement*> (curr->second)->LinkEndChild(comment);
}
// ***************************************************************

// ***************************************************************
// AddNode : Adds a node to the xml document
// ***************************************************************
void cXMLFileIO::AddNode( Base::cString strParentId, Base::cString strId, Base::cString strNode, Base::cString strNodeValue )
{
	TiXmlElement *element = DEBUG_NEW TiXmlElement(strNode.GetData());
	element->LinkEndChild(DEBUG_NEW TiXmlText(strNodeValue.GetData()));
	ElementMap::iterator  curr = m_ElementMap.find(strParentId);
	const_cast<TiXmlElement*> (curr->second)->LinkEndChild(element);
	m_ElementMap.insert(std::make_pair(strId, element));
}
// ***************************************************************

// ***************************************************************
// AddNode : Adds a node to the xml document
// ***************************************************************
void cXMLFileIO::AddAttribute(Base::cString strId
						   , Base::cString strAttributeNode
						   , const int iValue )
{
	ElementMap::iterator  curr = m_ElementMap.find(strId);
	const_cast<TiXmlElement*> (curr->second)->SetAttribute(strAttributeNode.GetData(), iValue);
}
// ***************************************************************

// ***************************************************************
// AddNode : Adds a node to the xml document
// ***************************************************************
void cXMLFileIO::AddAttribute( Base::cString strId
						   , Base::cString strAttributeNode
						   , Base::cString strValue )
{
	ElementMap::iterator  curr = m_ElementMap.find(strId);
	const_cast<TiXmlElement*> (curr->second)->SetAttribute(strAttributeNode.GetData(), strValue.GetData());

}
// ***************************************************************

// ***************************************************************
// AddNode : Adds a node to the xml document
// ***************************************************************
void cXMLFileIO::Save( Base::cString strFilePath )
{
	m_pDoc->SaveFile(strFilePath.GetData());
}
// ***************************************************************

// ***************************************************************
// AddNode : Adds a node to the xml document
// ***************************************************************
Base::cString cXMLFileIO::Load( Base::cString strFilePath )
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
Base::cString cXMLFileIO::GetNodeName( Base::cString strParent, const int iIndex )
{
	TiXmlElement *pElem;

	ElementMap::iterator  curr = m_ElementMap.find(strParent);
	TiXmlElement *pParent =const_cast<TiXmlElement*> (curr->second);
	pElem = pParent->FirstChildElement();
	for(int i=0;i<iIndex;i++)
	{
		pElem = pElem->NextSiblingElement();
	}
	m_ElementMap.insert(std::make_pair(pElem->Value(), pElem));
	return(pElem->Value());
}
// ***************************************************************

// ***************************************************************
// AddNode : Adds a node to the xml document
// ***************************************************************
Base::cString cXMLFileIO::GetNodeValue( Base::cString strNode )
{
	TiXmlElement *pElem;

	ElementMap::iterator  curr = m_ElementMap.find(strNode);
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

