#include "stdafx.h"
#include "Sound.h"
#include "FModex\fmod.hpp"
#include "FModex\fmod_errors.h"

using namespace std;
using namespace FMOD;
using namespace Utilities;
using namespace MySound;
using namespace Base;

stSounds::stSounds() 
: pSound(NULL)
, pChannel(NULL)
{
}

cSound::cSound()
: m_pSystem(NULL)
, bValid(true)
{
}
// ***************************************************************

cSound::~cSound()
{
	Shutdown();
}
// ***************************************************************

void cSound::Init()
{
	FMOD_RESULT			result;

	UINT				iVersion;
	FMOD_CAPS			caps;
	FMOD_SPEAKERMODE	speakerMode;

	m_pSystem = NULL;
	m_apSounds.clear();

	result = System_Create(&m_pSystem);
	if(!CheckError(result))
	{
		bValid = false;
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Could not create system. FMOD error! (%d) %s\n", result, FMOD_ErrorString(result)));
		return;
	}

	result= m_pSystem->getVersion(&iVersion);
	if(!CheckError(result))
	{
		bValid = false;
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Could not get version. FMOD error! (%d) %s\n", result, FMOD_ErrorString(result)));

		return;
	}

	if (iVersion < FMOD_VERSION)
	{
		bValid = false;
		Log_Write_L1(ILogger::LT_ERROR, "FMOD Version mismatch.");

		return;	}

	result = m_pSystem->getDriverCaps(0, &caps, 0, 0, &speakerMode);
	if(!CheckError(result))
	{
		bValid = false;
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Could not get driver caps. FMOD error! (%d) %s\n", result, FMOD_ErrorString(result)));
		return;
	}

	result = m_pSystem->setSpeakerMode(speakerMode);
	if(!CheckError(result))
	{
		bValid = false;
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Could not set speaker mode. FMOD error! (%d) %s\n", result, FMOD_ErrorString(result)));
		return;
	}

	if(caps & FMOD_CAPS_HARDWARE_EMULATED)
	{
		result = m_pSystem->setDSPBufferSize(1024,10);
		if(!CheckError(result))
		{
			bValid = false;
			Log_Write_L1(ILogger::LT_ERROR, cString(100, "Could not set dsp buffer size. FMOD error! (%d) %s\n", result, FMOD_ErrorString(result)));
			return;
		}
	}
	result = m_pSystem->init(32, FMOD_INIT_NORMAL, 0);
	if(!CheckError(result))
	{
		bValid = false;
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Could not init system. FMOD error! (%d) %s\n", result, FMOD_ErrorString(result)));
		return;
	}
}
// ***************************************************************

void cSound::Shutdown()
{
	FMOD_RESULT	result; 
	TSoundMap::iterator iterSound;
	char strFileName[MAX_FILENAME_WIDTH];

	for (iterSound = m_apSounds.begin(); iterSound != m_apSounds.end(); iterSound++)
	{
		iterSound->second->pSound->getName(strFileName, 100);
		Log_Write_L2(ILogger::LT_EVENT, cString(100, "Releasing Sound : %s\n", strFileName));

		iterSound->second->pSound->release();
		SAFE_DELETE((iterSound->second));
		//CheckError(result);
	}
	m_apSounds.clear();

	if(m_pSystem)
	{
		result = m_pSystem->release();
		//CheckError(result);
	}
}
// ***************************************************************

ISound * ISound::CreateSound()
{
	cSound * pSound = DEBUG_NEW cSound();
	return pSound;
}
// ***************************************************************

void cSound::CreateSound( int index, const cString & strFilename )
{
	if (!bValid)
	{
		return;
	}

	FMOD_RESULT	result;
	Sound *		pSound;
	stSounds	* pSounds = DEBUG_NEW stSounds;

	result = m_pSystem->createSound(strFilename.GetData(), FMOD_HARDWARE|FMOD_CREATESAMPLE, 0, &pSound);
	if(!CheckError(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Could not create sound %s. FMOD error! (%d) %s\n", strFilename, result, FMOD_ErrorString(result)));
		return;
	}
	pSounds->pSound = pSound;

	m_apSounds.insert(TSoundPair(index, pSounds));
	Log_Write_L2(ILogger::LT_EVENT, cString(100, "Loading sound : %s\n", strFilename.GetData()));
}
// ***************************************************************

void cSound::PlaySound( int iSoundIndex )
{
	if (!bValid)
	{
		return;
	}
	FMOD_RESULT	result;
	Sound *		pSound = NULL;
	Channel *	pChannel = NULL;
	TSoundMap::iterator iterSound;

	iterSound = m_apSounds.find(iSoundIndex);
	if (iterSound == m_apSounds.end())
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Could not Find Sound in PlaySound. iSoundIndex = %d\n", iSoundIndex));
		return;
	}
	pSound = iterSound->second->pSound;
	result = m_pSystem->playSound(FMOD_CHANNEL_REUSE, pSound, false, &pChannel);
	iterSound->second->pChannel = pChannel;
	if(!CheckError(result))
	{
		char strFileName[MAX_FILENAME_WIDTH];
		pSound->getName(strFileName, MAX_FILENAME_WIDTH);
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Could not play sound : %s. FMOD error! (%d) %s\n", strFileName, result, FMOD_ErrorString(result)));

		return;
	}
}
// ***************************************************************

void cSound::Update()
{
	if (!bValid)
	{
		return;
	}
	m_pSystem->update();
}
// ***************************************************************

void cSound::CreateStream( int index, const cString & strFilename )
{
	FMOD_RESULT	result;
	stSounds	* pSounds = DEBUG_NEW stSounds;

	result = m_pSystem->createStream(strFilename.GetData(), FMOD_HARDWARE|FMOD_CREATESTREAM|FMOD_LOOP_NORMAL, 0, &(pSounds->pSound));
	if(!CheckError(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Could not create stream : %s. FMOD error! (%d) %s\n", strFilename, result, FMOD_ErrorString(result)));
		return;
	}

	m_apSounds.insert(TSoundPair(index, pSounds));
	Log_Write_L2(ILogger::LT_EVENT, cString(100, "Loading stream : %s\n", strFilename.GetData()));
}

void cSound::StopSound( int iSoundIndex )
{
	FMOD_RESULT	result;
	TSoundMap::iterator iterSound;

	iterSound = m_apSounds.find(iSoundIndex);
	if (iterSound == m_apSounds.end())
	{
		Log_Write_L1(ILogger::LT_WARNING, cString(100, "Could not Find Sound in StopSound. iSoundIndex = %d.\n", iSoundIndex));
		return;
	}

	result = iterSound->second->pChannel->stop();
	if(!CheckError(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString( 100, "Could not stop sound. FMOD error! (%d) %s\n", result, FMOD_ErrorString(result)));
		return;
	}
}
// ***************************************************************

void cSound::ChangeMusicVolume(bool bIncreaseVolume, int iSoundIndex)
{
	float fVolume;
	FMOD_RESULT	result;
	TSoundMap::iterator  iterSound; 

	iterSound = m_apSounds.find(iSoundIndex);
	if (iterSound == m_apSounds.end())
	{
		Log_Write_L1(ILogger::LT_WARNING, cString(100, "Could not Find Sound in ChangeMusicVolume. iSoundIndex = %d.\n", iSoundIndex));
		return;
	}
	result = iterSound->second->pChannel->getVolume(&fVolume);
	if(!CheckError(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Could not Change Music Volume. FMOD error! (%d) %s\n", result, FMOD_ErrorString(result)));
		return;
	}

	if (bIncreaseVolume)
	{
		fVolume += 0.01f;
		if (fVolume > 1.0f)
		{
			fVolume = 1.0f;
		}
	}
	else
	{
		fVolume -= 0.01f;
		if (fVolume < 0.0f)
		{
			fVolume = 0.0f;
		}
	}
	result = iterSound->second->pChannel->setVolume(fVolume);
	CheckError(result);
	Log_Write_L2(ILogger::LT_DEBUG, cString(30, "New Volume : %f\n", fVolume));
}

void cSound::RemoveSound( int iSoundIndex )
{
	TSoundMap::iterator  iterSound; 

	StopSound(iSoundIndex);

	iterSound = m_apSounds.find(iSoundIndex);
	if(iterSound == m_apSounds.end())
	{
		Log_Write_L1(ILogger::LT_WARNING, cString(100, "Could not Find Sound in RemoveSound. iSoundIndex = %d.\n", iSoundIndex));
		return;
	}
	char strFileName[MAX_FILENAME_WIDTH];
	iterSound->second->pSound->getName(strFileName, MAX_FILENAME_WIDTH);
	Log_Write_L2(ILogger::LT_EVENT, cString(100, "Removing Sound : %s\n", strFileName));

	iterSound->second->pSound->release();
	SAFE_DELETE(iterSound->second);
	m_apSounds.erase(iSoundIndex);
}