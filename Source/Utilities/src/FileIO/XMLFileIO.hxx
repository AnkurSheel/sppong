// ***************************************************************
//  XMLFileIO   version:  1.0   Ankur Sheel  date: 2011/02/01
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef XMLFileIO_hxx__
#define XMLFileIO_hxx__

namespace Base
{
	class cString;
}

namespace Utilities
{
	class IXMLFileIO
	{
	public:
		virtual ~IXMLFileIO(){};
		virtual void Init(Base::cString strRootId, Base::cString strRootName, Base::cString strStyleSheetPath) = 0;
		virtual void AddComment(Base::cString strParentId, Base::cString strComment) = 0;
		virtual void AddNode(Base::cString strParentId, Base::cString strId, Base::cString strNode, Base::cString strNodeValue) = 0;
		virtual void AddAttribute(Base::cString strId, Base::cString strAttributeNode, const int iValue ) = 0;
		virtual void AddAttribute(Base::cString strId, Base::cString strAttributeNode, Base::cString strValue ) = 0;
		virtual void Save(Base::cString strFilePath) = 0;
		virtual Base::cString Load(Base::cString strFilePath) = 0;
		virtual Base::cString GetNodeName(Base::cString strParent, const int iIndex) = 0;
		virtual Base::cString GetNodeValue(Base::cString strNode) = 0;
		static IXMLFileIO * CreateXMLFile();
	};
}
#endif // XMLFileIO_h__
