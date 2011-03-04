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
		void Init(Base::cString strRootId, Base::cString strRootName, Base::cString strStyleSheetPath);
		void AddComment(Base::cString strParentId, Base::cString strComment);
		void AddNode(Base::cString strParentId, Base::cString strId, Base::cString strNode, Base::cString strNodeValue);
		void AddAttribute(Base::cString strId, Base::cString strAttributeNode, const int iValue );
		void AddAttribute(Base::cString strId, Base::cString strAttributeNode, Base::cString strValue );
		void Save(Base::cString strFilePath);
		Base::cString Load(Base::cString strFilePath);
		Base::cString GetNodeName(Base::cString strParent, const int iIndex) ;
		Base::cString GetNodeValue(Base::cString strNode);

	private:
		typedef std::map<Base::cString , const TiXmlElement*> ElementMap;

		TiXmlDocument*	m_pDoc;  
		ElementMap		m_ElementMap;
		TiXmlElement*	m_pRoot;

	};
}
#endif // XMLFileIO_h__