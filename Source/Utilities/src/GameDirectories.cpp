// *****************************************************************************
//  GameDirectories   version:  1.0   Ankur Sheel  date: 2013/01/22
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "GameDirectories.h"
#include "ParamLoaders.hxx"
#include "XMLFileIO.hxx"
#include "ResCache.hxx"
#include "ResourceManager.hxx"

using namespace Utilities;

static cGameDirectories gameDirectories;

// *****************************************************************************
const cGameDirectories & cGameDirectories::GameDirectories()
{
	return gameDirectories;
}

// *****************************************************************************
void cGameDirectories::Initialize()
{
	IXMLFileIO * pFile = IXMLFileIO::CreateXMLFile();

	IResource * pResource = IResource::CreateResource("directories.xml");
	shared_ptr<IResHandle> directoriesXML = IResourceManager::GetInstance()->VGetResourceCache()->GetHandle(*pResource);
	
	pFile->VParse(directoriesXML->GetBuffer(), directoriesXML->GetSize());
	gameDirectories.strMediaDirectory = pFile->VGetNodeValue("MediaDirectory");
	gameDirectories.strFontDirectory = pFile->VGetNodeValue("FontDirectory");
	gameDirectories.strShaderDirectory = pFile->VGetNodeValue("ShaderDirectory");
	gameDirectories.strSpriteDirectory = pFile->VGetNodeValue("SpriteDirectory");
	gameDirectories.strSoundDirectory = pFile->VGetNodeValue("SoundDirectory");
	gameDirectories.strModelDirectory = pFile->VGetNodeValue("ModelDirectory");

	SAFE_DELETE(pResource);
	SAFE_DELETE(pFile);
}