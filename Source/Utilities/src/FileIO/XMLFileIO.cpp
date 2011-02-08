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
#include <map>

namespace Utilities
{
	class cXMLFileIO
		: public IXMLFileIO
	{
	public:
		cXMLFileIO();
		~cXMLFileIO();
		void Init(const char * const strRootId, const char * const strRootName, const char * const strStyleSheetPath = NULL);
		void AddComment(const char * const strParentId, const char * const strComment);
		void AddNode(const char * const strParentId, const char * const strId, const char * const strNode, const char * const strNodeValue);
		void AddAttribute(const char * const strId, const char * const strAttributeNode, const int iValue );
		void AddAttribute(const char * const strId, const char * const strAttributeNode, const char * const strValue );
		void Save(const char * const strFilePath);
		const char * const Load(const char * const strFilePath);
		const char * const GetNodeName(const char * const strParent, const int iIndex) ;
		const char * const GetNodeValue(const char * const strNode);

	private:
		typedef std::map<const char * const , const TiXmlElement* > ElementMap;

		TiXmlDocument*	m_pDoc;  
		ElementMap		m_ElementMap;
		TiXmlElement*	m_pRoot;

	};
}

//using namespace std;
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
void cXMLFileIO::Init( const char * const strRootId, const char * const strRootName, const char * const strStyleSheetPath /*= NULL*/ )
{
	SAFE_DELETE(m_pDoc);
	m_pDoc = DEBUG_NEW TiXmlDocument();

	TiXmlDeclaration* decl = DEBUG_NEW TiXmlDeclaration( "1.0", "", "" );  
	m_pDoc->LinkEndChild( decl ); 

	if (strStyleSheetPath)
	{
		TiXmlStylesheetReference *pRef = DEBUG_NEW TiXmlStylesheetReference("text/xsl", strStyleSheetPath);
		m_pDoc->LinkEndChild(pRef);
	}
	TiXmlElement * root = DEBUG_NEW TiXmlElement(strRootName);  
	m_pDoc->LinkEndChild( root );  

	m_ElementMap.insert(std::make_pair(strRootId, root));
}
// ***************************************************************

// ***************************************************************
// Init : Initialises the xml file with the root as the rootname
// ***************************************************************
void cXMLFileIO::AddComment( const char * const strParentId, const char * const strComment )
{
	TiXmlComment*	comment;

	comment = DEBUG_NEW TiXmlComment();
	comment->SetValue(strComment); 
	ElementMap::iterator  curr = m_ElementMap.find(strParentId);
	const_cast<TiXmlElement*> (curr->second)->LinkEndChild(comment);
}
// ***************************************************************

// ***************************************************************
// AddNode : Adds a node to the xml document
// ***************************************************************
void cXMLFileIO::AddNode( const char * const strParentId, const char * const strId, const char * const strNode, const char * const strNodeValue )
{
	TiXmlElement *element = DEBUG_NEW TiXmlElement(strNode);
	element->LinkEndChild(DEBUG_NEW TiXmlText(strNodeValue));
	ElementMap::iterator  curr = m_ElementMap.find(strParentId);
	const_cast<TiXmlElement*> (curr->second)->LinkEndChild(element);
	m_ElementMap.insert(std::make_pair(strId, element));
}
// ***************************************************************

// ***************************************************************
// AddNode : Adds a node to the xml document
// ***************************************************************
void cXMLFileIO::AddAttribute(const char * const strId
						   , const char * const strAttributeNode
						   , const int iValue )
{
	ElementMap::iterator  curr = m_ElementMap.find(strId);
	const_cast<TiXmlElement*> (curr->second)->SetAttribute(strAttributeNode, iValue);
}
// ***************************************************************

// ***************************************************************
// AddNode : Adds a node to the xml document
// ***************************************************************
void cXMLFileIO::AddAttribute( const char * const strId
						   , const char * const strAttributeNode
						   , const char * const strValue )
{
	ElementMap::iterator  curr = m_ElementMap.find(strId);
	const_cast<TiXmlElement*> (curr->second)->SetAttribute(strAttributeNode, strValue);

}
// ***************************************************************

// ***************************************************************
// AddNode : Adds a node to the xml document
// ***************************************************************
void cXMLFileIO::Save( const char * const strFilePath )
{
	m_pDoc->SaveFile(strFilePath);
}
// ***************************************************************

// ***************************************************************
// AddNode : Adds a node to the xml document
// ***************************************************************
const char * const cXMLFileIO::Load( const char * const strFilePath )
{
	SAFE_DELETE(m_pDoc);
	m_pDoc = DEBUG_NEW TiXmlDocument(strFilePath);
	if (!m_pDoc->LoadFile(strFilePath))
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
const char * const cXMLFileIO::GetNodeName( const char * const strParent, const int iIndex )
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
const char * const cXMLFileIO::GetNodeValue( const char * const strNode )
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

