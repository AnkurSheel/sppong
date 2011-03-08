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
		virtual void Init(const Base::cString & strRootId, const Base::cString & strRootName, const Base::cString & strStyleSheetPath) = 0;
		virtual void AddComment(const Base::cString & strParentId, const Base::cString & strComment) = 0;
		virtual void AddNode(const Base::cString & strParentId, const Base::cString & strId, const Base::cString & strNode, const Base::cString & strNodeValue) = 0;
		virtual void AddAttribute(const Base::cString & strId, const Base::cString & strAttributeNode, const int iValue ) = 0;
		virtual void AddAttribute(const Base::cString & strId, const Base::cString & strAttributeNode, const Base::cString & strValue ) = 0;
		virtual void Save(const Base::cString & strFilePath) = 0;
		virtual Base::cString Load(const Base::cString & strFilePath) = 0;
		virtual Base::cString GetNodeName(const Base::cString & strParent, const int iIndex) = 0;
		virtual Base::cString GetNodeValue(const Base::cString & strNode) = 0;
		static IXMLFileIO * CreateXMLFile();
	};
}
#endif // XMLFileIO_h__
