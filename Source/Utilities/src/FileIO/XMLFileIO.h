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

namespace Utilities
{
	class IXMLFileIO
	{
	public:
		virtual ~IXMLFileIO(){};
		virtual void Init(const char * const strRootId, const char * const strRootName, const char * const strStyleSheetPath = NULL) = 0;
		virtual void AddComment(const char * const strParentId, const char * const strComment) = 0;
		virtual void AddNode(const char * const strParentId, const char * const strId, const char * const strNode, const char * const strNodeValue) = 0;
		virtual void AddAttribute(const char * const strId, const char * const strAttributeNode, const int iValue ) = 0;
		virtual void AddAttribute(const char * const strId, const char * const strAttributeNode, const char * const strValue ) = 0;
		virtual void Save(const char * const strFilePath) = 0;
		virtual const char * const Load(const char * const strFilePath) = 0;
		virtual const char * const GetNodeName(const char * const strParent, const int iIndex) = 0;
		virtual const char * const GetNodeValue(const char * const strNode) = 0;
		static IXMLFileIO * CreateXMLFile();
	};
}
#endif // XMLFileIO_h__
