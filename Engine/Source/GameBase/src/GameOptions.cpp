// *****************************************************************************
//  GameOptions   version:  1.0   Ankur Sheel  date: 2013/01/23
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "GameOptions.h"
#include "XMLFileIO.hxx"

using namespace GameBase;
using namespace Base;
using namespace Utilities;

static cGameOptions gameOptions;

// *****************************************************************************
cGameOptions & cGameOptions::GameOptions()
{
	return gameOptions;
}

// *****************************************************************************
void cGameOptions::InitializeGameOptions(const cString & strPlayerOptionsFile)
{
	IXMLFileIO	* pXml = IXMLFileIO::CreateXMLFile();
	if(pXml->VLoad(strPlayerOptionsFile))
	{
		gameOptions.bFullScreen = pXml->VGetNodeAttributeAsBool("Graphics", "fullscreen");
		gameOptions.iWidth = pXml->VGetNodeAttributeAsInt("Graphics", "width");
		if (gameOptions.iWidth < 800) 
		{
			gameOptions.iWidth = 800;
			Log_Write_L1(ILogger::LT_ERROR, "Default width of 800 applied");
		}
		gameOptions.iHeight = pXml->VGetNodeAttributeAsInt("Graphics", "height");
		if (gameOptions.iHeight < 600) 
		{
			gameOptions.iWidth = 600;
			Log_Write_L1(ILogger::LT_ERROR, "Default height of 600 applied");
		}
		gameOptions.bPlayMusic = pXml->VGetNodeAttributeAsBool("Sound", "PlayMusic");
		gameOptions.iMusicVolume = pXml->VGetNodeAttributeAsInt("Sound", "musicVolume");
		gameOptions.bPlaySfx = pXml->VGetNodeAttributeAsBool("Sound", "PlaySFX");
		gameOptions.iSFXVolume = pXml->VGetNodeAttributeAsInt("Sound", "sfxVolume");
	}
	SAFE_DELETE(pXml);
}

// *****************************************************************************
GAMEBASE_API void cGameOptions::SaveGameOptions(const cString & strPlayerOptionsFile)
{
	IXMLFileIO	* pXml = IXMLFileIO::CreateXMLFile();
	pXml->VInitializeForSave("PlayerOptions", "");

	pXml->VAddElement("PlayerOptions", "Graphics", "", "");
	pXml->VAddAttribute("Graphics", "fullscreen", gameOptions.bFullScreen);
	pXml->VAddAttribute("Graphics", "width", gameOptions.iWidth);
	pXml->VAddAttribute("Graphics", "height", gameOptions.iHeight);

	pXml->VAddElement("PlayerOptions", "Sound", "", "");
	pXml->VAddAttribute("Sound", "PlayMusic", gameOptions.bPlayMusic);
	pXml->VAddAttribute("Sound", "musicVolume", gameOptions.iMusicVolume);
	pXml->VAddAttribute("Sound", "PlaySFX", gameOptions.bPlaySfx);
	pXml->VAddAttribute("Sound", "sfxVolume", gameOptions.iSFXVolume);

	pXml->VSave(strPlayerOptionsFile);
	SAFE_DELETE(pXml);
}