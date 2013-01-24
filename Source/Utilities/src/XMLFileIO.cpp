// *****************************************************************************
//  XMLFileIO   version:  1.0   Ankur Sheel  date: 2011/02/01
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "XMLFileIO.h"
#include "TinyXml\tinyxml2.h"

using namespace tinyxml2;
using namespace Base;
using namespace Utilities;

// *****************************************************************************
cXMLFileIO::cXMLFileIO()
: m_pDoc(NULL)
{
}

// *****************************************************************************
cXMLFileIO::~cXMLFileIO()
{
	SAFE_DELETE(m_pDoc);
	m_ElementMap.clear();
}

// *****************************************************************************
void cXMLFileIO::VInitializeForSave(const Base::cString & strRootName, 
									const Base::cString & strStyleSheetPath)
{
	SAFE_DELETE(m_pDoc);
	m_pDoc = DEBUG_NEW XMLDocument();

	m_pDoc->InsertEndChild(m_pDoc->NewDeclaration(NULL));
	
	if (!strStyleSheetPath.IsEmpty())
	{
		cString str = "xml-stylesheet type=\"text/xsl\" href=\"" + strStyleSheetPath + "\"";
		m_pDoc->InsertEndChild(m_pDoc->NewDeclaration(str.GetData()));
	}
	XMLElement * pRoot = m_pDoc->NewElement(strRootName.GetData());  
	m_pDoc->InsertEndChild(pRoot);

	m_ElementMap.insert(std::make_pair(strRootName.GetData(), pRoot));
}

// *****************************************************************************
void cXMLFileIO::VLoad( const cString & strFilePath, cString & strRootName )
{
	VLoad(strFilePath);
	strRootName = m_pDoc->RootElement()->Value();
}

// *****************************************************************************
bool cXMLFileIO::VLoad( const cString & strFilePath)
{
	Log_Write_L1(ILogger::LT_DEBUG, "loading XML file " + strFilePath);
	SAFE_DELETE(m_pDoc);
	m_pDoc = DEBUG_NEW XMLDocument();
	if (m_pDoc->LoadFile(strFilePath.GetData()) != XML_NO_ERROR)
	{
		Log_Write_L1(ILogger::LT_ERROR, "Could not load XML file " + strFilePath);
		return false;
	}

	XMLElement * pRoot = m_pDoc->FirstChildElement();
	m_ElementMap.insert(std::make_pair(pRoot->Name(), pRoot));

	AddChildElements(pRoot);
	return true;
}

// *****************************************************************************
void cXMLFileIO::VParse(const cString & strXML, const unsigned int size)
{
	Log_Write_L1(ILogger::LT_DEBUG, "Parsing XML file ");
	SAFE_DELETE(m_pDoc);
	m_pDoc = DEBUG_NEW XMLDocument();
	
	if (m_pDoc->Parse(strXML.GetData(), size) != XML_NO_ERROR)
	{
		Log_Write_L1(ILogger::LT_ERROR, "Could not parse XML file");
		return;
	}

	XMLElement * pRoot = m_pDoc->FirstChildElement();
	m_ElementMap.insert(std::make_pair(pRoot->Name(), pRoot));

	AddChildElements(pRoot);
}

// *****************************************************************************
void cXMLFileIO::VSave(const cString & strFilePath)
{
	m_pDoc->SaveFile(strFilePath.GetData());
}

// *****************************************************************************
cString cXMLFileIO::VAddElement( const cString & strParentName, const cString & strElementName,
							 const cString & strElementAttribID, const cString & strElementValue )
{
	XMLElement * pElement = m_pDoc->NewElement(strElementName.GetData());
	if (!strElementAttribID.IsEmpty())
	{
		pElement->SetAttribute("id", strElementAttribID.GetData());
	}
	
	if (!strElementValue.IsEmpty())
	{
		XMLText * pText = m_pDoc->NewText(strElementValue.GetData());
		pElement->InsertEndChild(pText);
	}

	ElementMap::const_iterator  curr = m_ElementMap.find(strParentName);
	XMLElement * pParentElement = const_cast<XMLElement*> (curr->second);
	pParentElement->LinkEndChild(pElement);

	cString strID;
	GetUniqueNameForMap(pElement, strID);
	m_ElementMap.insert(std::make_pair(strID, pElement));
	return strID;
}
// *****************************************************************************
void cXMLFileIO::VAddAttribute(const cString & strElementName,
							   const cString & strAttributeName,
							   const cString & strAttributeValue)
{
	ElementMap::const_iterator  curr = m_ElementMap.find(strElementName);
	const_cast<XMLElement*> (curr->second)->SetAttribute(strAttributeName.GetData(), strAttributeValue.GetData());

}

// *****************************************************************************
void cXMLFileIO::VAddAttribute(const cString & strElementName,
							   const cString & strAttributeName,
							   const int iAttributeValue)
{
	ElementMap::const_iterator  curr = m_ElementMap.find(strElementName);
	const_cast<XMLElement*> (curr->second)->SetAttribute(strAttributeName.GetData(), iAttributeValue);
}

// *****************************************************************************
void cXMLFileIO::VAddAttribute(const cString & strElementName, 
							   const cString & strAttributeName,
							   const bool bAttributeValue)
{
	ElementMap::const_iterator  curr = m_ElementMap.find(strElementName);
	const_cast<XMLElement*> (curr->second)->SetAttribute(strAttributeName.GetData(), bAttributeValue);
}

// *****************************************************************************
void cXMLFileIO::VAddComment( const cString & strParentElementID, 
							 const cString & strComment )
{
	ElementMap::const_iterator  curr = m_ElementMap.find(strParentElementID);
	XMLElement * pElement = const_cast<XMLElement*> (curr->second);
	pElement->InsertEndChild(m_pDoc->NewComment(strComment.GetData()));
}

// *****************************************************************************
void cXMLFileIO::VGetAllChildrenNames( const Base::cString & strParentID,
									  std::vector<cString> & vElements )
{
	ElementMap::const_iterator  curr = m_ElementMap.find(strParentID);
	const XMLElement * pParentElement = curr->second;
	const XMLElement *pElement = pParentElement->FirstChildElement();
	cString strId;
	while(pElement)
	{
		GetUniqueNameForMap(pElement, strId);
		vElements.push_back(strId);
		pElement = pElement->NextSiblingElement();
	}
}

// *****************************************************************************

// *****************************************************************************
cString cXMLFileIO::VGetNodeValue(const cString & strElementID)

{
	ElementMap::const_iterator curr = m_ElementMap.find(strElementID);
	if (curr == m_ElementMap.end())
	{
		Log_Write_L1(ILogger::LT_ERROR, "could not find element " + strElementID) ;
		return "";
	}
	XMLElement * pElem = const_cast<XMLElement*> (curr->second);
	return(pElem->GetText());
}

// *****************************************************************************
cString cXMLFileIO::VGetNodeAttribute(const cString & strElementID,
								   const cString & strAttributeName)
{
	ElementMap::const_iterator curr = m_ElementMap.find(strElementID);
	if (curr != m_ElementMap.end())
	{
		return (curr->second->Attribute(strAttributeName.GetData()));
	}
	else
	{
		Log_Write_L1(ILogger::LT_ERROR, "Could not find attribute" + strAttributeName + " for " + strElementID);
	}
	return "";
}

// *****************************************************************************
int cXMLFileIO::VGetNodeAttributeAsInt(const Base::cString & strElementID,
			const Base::cString & strAttributeName)
{
	cString strAttributeValue = VGetNodeAttribute(strElementID, strAttributeName);
	tOptional<int> val = strAttributeValue.ToInt();
	if(val.IsInvalid())
	{
		Log_Write_L1(ILogger::LT_ERROR, "Error in getting " + strAttributeName + " attribute as int in " + strElementID);
		return 0;
	}
	return *val;
}

// *****************************************************************************
bool cXMLFileIO::VGetNodeAttributeAsBool(const Base::cString & strElementID,
			const Base::cString & strAttributeName)
{
	cString strAttributeValue = VGetNodeAttribute(strElementID, strAttributeName);
	tOptional<bool> val = strAttributeValue.ToBool();
	if(val.IsInvalid())
	{
		Log_Write_L1(ILogger::LT_ERROR, "Error in getting " + strAttributeName + " attribute as int in " + strElementID);
		return false;
	}
	return *val;
}

// *****************************************************************************
cString cXMLFileIO::GetNodeName( const cString & strParent, const int iIndex )
{
	XMLElement *pElem;

	ElementMap::const_iterator  curr = m_ElementMap.find(strParent);
	XMLElement *pParent =const_cast<XMLElement*> (curr->second);
	pElem = pParent->FirstChildElement();
	for(int i=0;i<iIndex;i++)
	{
		pElem = pElem->NextSiblingElement();
	}
	return(pElem->Value());
}

// *****************************************************************************
void cXMLFileIO::AddChildElements(XMLElement * const pParent)
{
	XMLElement * pElement = pParent->FirstChildElement();
	if(pElement == NULL)
		return;

	cString strName;
	ElementMap::const_iterator itr;
	while(pElement)
	{
		strName = cString(pElement->Value()) + pElement->Attribute("id");
		
		itr = m_ElementMap.insert(std::make_pair(strName, pElement));
		if(itr == m_ElementMap.end())
		{
			Log_Write_L1(ILogger::LT_ERROR, "Duplicate element name " + strName)
		}
		AddChildElements(pElement);
		pElement = pElement->NextSiblingElement();
	}
}

// *****************************************************************************
void cXMLFileIO::GetUniqueNameForMap( const XMLElement * const pElement, cString & strName )
{
	strName = cString(pElement->Value()) + pElement->Attribute("id");
}

// *****************************************************************************
IXMLFileIO * IXMLFileIO::CreateXMLFile()
{
	cXMLFileIO* pXMLFile= DEBUG_NEW cXMLFileIO();
	return pXMLFile;
}