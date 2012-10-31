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
		void VParse(const Base::cString & strXML, const unsigned int size);
		void VAddComment(const Base::cString & strParentElementID,
			const Base::cString & strComment);
		Base::cString VAddElement( const Base::cString & strParentName, 
			const Base::cString & strElementName, const Base::cString & strElementAttribID,
			const Base::cString & strElementValue );
		void VGetAllChildrenNames(const Base::cString & strParentID,
			std::vector<Base::cString> & vElements );
		void VGetNodeAttribute(const Base::cString & strElementID,
			const Base::cString & strAttributeName, Base::cString & strAttributeValue);
		int VGetNodeAttributeAsInt(const Base::cString & strElementID,
			const Base::cString & strAttributeName);
		/********************************************//**
		 * @param[in] pParent The parent element
		 *
		 * Adds all the child elements for the parent element
		 ***********************************************/
		void AddChildElements(tinyxml2::XMLElement * const pParent);
		/********************************************//**
		 * @param[in] pElement The element for which the unique name has to be returned
		 * @param[out] strName The unique name of this element
		 *
		 * Creates a unique name by appending the id attribute value 
		 * to the element name and stores it in strName
		 ***********************************************/
		void GetUniqueNameForMap(const tinyxml2::XMLElement * const pElement, Base::cString & strName);
	
	private:
		typedef std::multimap<Base::cString , const tinyxml2::XMLElement*> ElementMap;

		tinyxml2::XMLDocument*	m_pDoc;			/*!< Pointer to the tinyxml2 Document */
		ElementMap				m_ElementMap;	/*!< The map containg all the elments in the XML file. The key is the unique name obtained from /cGetUniqueNameForMap */
	};
}
#endif // XMLFileIO_h__