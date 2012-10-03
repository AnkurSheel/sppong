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

namespace tinyxml2
{
	class XMLElement;
	class XMLDocument;
}

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
		void AddAttribute(const Base::cString & strId, const Base::cString & strAttributeNode, const int iValue );
		void AddAttribute(const Base::cString & strId, const Base::cString & strAttributeNode, const Base::cString & strValue );
		void Save(const Base::cString & strFilePath);
		Base::cString GetNodeName(const Base::cString & strParent, const int iIndex) ;
		Base::cString GetNodeValue(const Base::cString & strNode);

	private:
		void VInitializeForSave(const Base::cString & strRootName,
			const Base::cString & strStyleSheetPath);
		void VLoad(const Base::cString & strFilePath);
		void VLoad(const Base::cString & strFilePath, Base::cString & strRootName);
		void VAddComment(const Base::cString & strParentElementID,
			const Base::cString & strComment);
		Base::cString VAddElement( const Base::cString & strParentName, 
			const Base::cString & strElementName, const Base::cString & strElementAttribID,
			const Base::cString & strElementValue );
		void VGetAllChildrenNames(const Base::cString & strParentID,
			std::vector<Base::cString> & vElements );
		void VGetNodeAttribute(const Base::cString & strElementID,
			const Base::cString & strAttributeName, Base::cString & strAttributeValue);
		/********************************************//**
		 * @param[in] pParent The parent element
		 *
		 * Adds all the child elements for the parent element
		 ***********************************************/
		void AddChildElements(tinyxml2::XMLElement * const pParent);
		void GetUniqueNameForMap(const tinyxml2::XMLElement * const pElement, Base::cString & strName);
	
	private:
		typedef std::multimap<Base::cString , const tinyxml2::XMLElement*> ElementMap;

		tinyxml2::XMLDocument*	m_pDoc;  
		ElementMap				m_ElementMap;
		tinyxml2::XMLElement *	m_pRoot;
	};
}
#endif // XMLFileIO_h__