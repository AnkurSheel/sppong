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

#include "XMLFileIO.hxx"
#include <map>
#include <string>

class TiXmlElement;
class TiXmlDocument;

namespace Base
{
	class cString;
}

namespace Utilities
{
	class cXMLFileIO
		: public IXMLFileIO
	{
	public:
		cXMLFileIO();
		~cXMLFileIO();
		void Init(const Base::cString & strRootId, const Base::cString & strRootName, const Base::cString & strStyleSheetPath);
		void AddComment(const Base::cString & strParentId, const Base::cString & strComment);
		void AddNode(const Base::cString & strParentId, const Base::cString & strId, const Base::cString & strNode, const Base::cString & strNodeValue);
		void AddAttribute(const Base::cString & strId, const Base::cString & strAttributeNode, const int iValue );
		void AddAttribute(const Base::cString & strId, const Base::cString & strAttributeNode, const Base::cString & strValue );
		void Save(const Base::cString & strFilePath);
		Base::cString Load(const Base::cString & strFilePath);
		Base::cString GetNodeName(const Base::cString & strParent, const int iIndex) ;
		Base::cString GetNodeValue(const Base::cString & strNode);

	private:
		typedef std::map<std::string , const TiXmlElement*> ElementMap;

		TiXmlDocument*	m_pDoc;  
		ElementMap		m_ElementMap;
		TiXmlElement*	m_pRoot;

	};
}
#endif // XMLFileIO_h__