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

enum eUsage
{
	SAVEDATAFILE,
	SAVENNFILE,
	LOADNNFILE
};

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
	void Init(const std::string strRootName);
	void AddComment(const std::string strParent, const std::string strComment);
	void AddNode(const std::string strParent, const std::string strNode, const std::string strNodeValue);
	void AddAttribute(const std::string strNode, const std::string strAttributeNode, const int iValue );
	void AddAttribute(const std::string strNode, const std::string strAttributeNode, const std::string strValue );
	void Save(const std::string strFilePath);
	std::string Load(const std::string strFilePath);
	std::string GetNodeName(const std::string strParent, const int iIndex) ;
	std::string GetNodeValue(const std::string strNode);
};
#endif // XMLFileIO_h__
