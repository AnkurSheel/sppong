#include "stdafx.h"
#include "GameOptions.h"
#include "XMLFileIO.hxx"

using namespace GameBase;
using namespace Utilities;
using namespace Base;

// *****************************************************************************
cGameOptions::cGameOptions()
: m_iWidth(1024)
, m_iHeight(768)
, m_iSFXVolume(100)
, m_iMusicVolume(100)
, m_bFullScreen(false)
{
}

// *****************************************************************************
cGameOptions::~cGameOptions()
{
}

// *****************************************************************************
void cGameOptions::Init(const cString & strPlayerOptionsFile)
{
	IXMLFileIO	* pXml = IXMLFileIO::CreateXMLFile();
	if(pXml->VLoad(strPlayerOptionsFile))
	{
		m_bFullScreen = pXml->VGetNodeAttributeAsBool("Graphics", "fullscreen");
		m_iWidth = pXml->VGetNodeAttributeAsInt("Graphics", "width");
		m_iHeight = pXml->VGetNodeAttributeAsInt("Graphics", "height");
		m_iSFXVolume = pXml->VGetNodeAttributeAsInt("Sound", "sfxVolume");
		m_iMusicVolume = pXml->VGetNodeAttributeAsInt("Sound", "sfxVolume");
	}
	SAFE_DELETE(pXml);
}