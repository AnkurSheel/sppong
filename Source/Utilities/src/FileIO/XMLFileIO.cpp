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

using namespace std;
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
void cXMLFileIO::Init( const string strRootName )
{
	SAFE_DELETE(m_pDoc);
	m_pDoc = DEBUG_NEW TiXmlDocument();

	TiXmlDeclaration* decl = DEBUG_NEW TiXmlDeclaration( "1.0", "", "" );  
	m_pDoc->LinkEndChild( decl ); 

	TiXmlElement * root = DEBUG_NEW TiXmlElement(strRootName.c_str());  
	m_pDoc->LinkEndChild( root );  

	m_ElementMap.insert(std::make_pair(strRootName, root));
}
// ***************************************************************

// ***************************************************************
// Init : Initialises the xml file with the root as the rootname
// ***************************************************************
void cXMLFileIO::AddComment(const string strParent, const string strComment )
{
	TiXmlComment*	comment;

	comment = DEBUG_NEW TiXmlComment();
	comment->SetValue(strComment.c_str()); 
	ElementMap::iterator  curr = m_ElementMap.find(strParent);
	const_cast<TiXmlElement*> (curr->second)->LinkEndChild(comment);
}
// ***************************************************************

// ***************************************************************
// AddNode : Adds a node to the xml document
// ***************************************************************
void cXMLFileIO::AddNode(const string strParent,  const string strNode
					  , const string strNodeValue )
{
	TiXmlElement *element = DEBUG_NEW TiXmlElement(strNode.c_str());
	element->LinkEndChild(DEBUG_NEW TiXmlText(strNodeValue.c_str()));
	ElementMap::iterator  curr = m_ElementMap.find(strParent);
	const_cast<TiXmlElement*> (curr->second)->LinkEndChild(element);
	m_ElementMap.insert(std::make_pair(strNode, element));
}
// ***************************************************************

// ***************************************************************
// AddNode : Adds a node to the xml document
// ***************************************************************
void cXMLFileIO::AddAttribute(const string strNode
						   , const string strAttributeNode
						   , const int iValue )
{
	ElementMap::iterator  curr = m_ElementMap.find(strNode);
	const_cast<TiXmlElement*> (curr->second)->SetAttribute(strAttributeNode.c_str(), iValue);
}
// ***************************************************************

// ***************************************************************
// AddNode : Adds a node to the xml document
// ***************************************************************
void cXMLFileIO::AddAttribute( const string strNode
						   , const string strAttributeNode
						   , const string strValue )
{
	ElementMap::iterator  curr = m_ElementMap.find(strNode);
	const_cast<TiXmlElement*> (curr->second)->SetAttribute(strAttributeNode.c_str(), strValue.c_str());

}
// ***************************************************************

// ***************************************************************
// AddNode : Adds a node to the xml document
// ***************************************************************
void cXMLFileIO::Save( const string strFilePath )
{
	m_pDoc->SaveFile(strFilePath.c_str());
}
// ***************************************************************

// ***************************************************************
// AddNode : Adds a node to the xml document
// ***************************************************************
string cXMLFileIO::Load( const string strFilePath )
{
	SAFE_DELETE(m_pDoc);
	m_pDoc = DEBUG_NEW TiXmlDocument(strFilePath.c_str());
	if (!m_pDoc->LoadFile(strFilePath.c_str()))
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
string cXMLFileIO::GetNodeName( const string strParent, const int iIndex )
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
string cXMLFileIO::GetNodeValue( const string strNode )
{
	TiXmlElement *pElem;

	ElementMap::iterator  curr = m_ElementMap.find(strNode);
	pElem =const_cast<TiXmlElement*> (curr->second);
	//pElem = pParent->FirstChildElement()->ToElement();
	return(pElem->GetText());
}
// ***************************************************************