// ***************************************************************
//  XMLFileIO   version:  1.0   Ankur Sheel  date: 2011/02/01
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef XMLFileIO_h__
#define XMLFileIO_h__

#include "tinyxml.h"
#include <string>
#include <map>

class cXMLFileIO
{
private:
	typedef std::map<const std::string, const TiXmlElement* > ElementMap;

	TiXmlDocument*	m_pDoc;  
	ElementMap		m_ElementMap;
	TiXmlElement*	m_pRoot;

public:
	cXMLFileIO();
	~cXMLFileIO();
	void Init(const char * const strRootId, const char * const strRootName, const char * const strStyleSheetPath = NULL);
	void AddComment(const char * const strParentId, const char * const strComment);
	void AddNode(const char * const strParentId, const char * const strId, const char * const strNode, const char * const strNodeValue);
	void AddAttribute(const char * const strId, const char * const strAttributeNode, const int iValue );
	void AddAttribute(const char * const strId, const char * const strAttributeNode, const char * const strValue );
	void Save(const char * const strFilePath);
	const char * const Load(const std::string strFilePath);
	const char * const GetNodeName(const char * const strParent, const int iIndex) ;
	const char * const GetNodeValue(const char * const strNode);
};
#endif // XMLFileIO_h__
