#include "stdafx.h"
#include "Sound.h"
#include "Fmod/fmod.hpp"
#include "Debugging/Logger.h"
#include "Fmod/fmod_errors.h"
#include <map>

using namespace std;
using namespace FMOD;

struct stSounds 
{
	Sound * pSound;
	Channel *pChannel;
	stSounds();

};

typedef map<int, stSounds *> TSoundMap;
typedef pair<int, stSounds *> TSoundPair;

class cSound
	: public ISound
{
private:
	bool CheckError(FMOD_RESULT ciResult);
	void Shutdown();
public:
	cSound();
	~cSound();
	void Init();
	void CreateSound(int index, const char * const strFilename);
	void PlaySound(int iSoundIndex);
	void StopSound(int iSoundIndex);
	void Update();
	void CreateStream( int index, const char * const strFilename );
	void ChangeMusicVolume(bool bIncreaseVolume, int iSoundIndex);
	void RemoveSound(int iSoundIndex);
private:
	System *			m_pSystem;
	TSoundMap			m_apSounds;
	bool				bValid;
};
// ***************************************************************

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
		ILogger::TheLogger()->Log("Could not create system. FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return;
	}
	
	result= m_pSystem->getVersion(&iVersion);
	if(!CheckError(result))
	{
		bValid = false;
		ILogger::TheLogger()->Log("Could not get version. FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return;
	}

	if (iVersion < FMOD_VERSION)
	{
		bValid = false;
		ILogger::TheLogger()->Log("FMOD Version mismatch.\n");
		return;	}

	result = m_pSystem->getDriverCaps(0, &caps, 0, 0, &speakerMode);
	if(!CheckError(result))
	{
		bValid = false;
		ILogger::TheLogger()->Log("Could not get driver caps. FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return;
	}

	result = m_pSystem->setSpeakerMode(speakerMode);
	if(!CheckError(result))
	{
		bValid = false;
		ILogger::TheLogger()->Log("Could not set speaker mode. FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return;
	}

	if(caps & FMOD_CAPS_HARDWARE_EMULATED)
	{
		result = m_pSystem->setDSPBufferSize(1024,10);
		if(!CheckError(result))
		{
			bValid = false;
			ILogger::TheLogger()->Log("Could not set dsp buffer size. FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			return;
		}
	}
	result = m_pSystem->init(32, FMOD_INIT_NORMAL, 0);
	if(!CheckError(result))
	{
		bValid = false;
		ILogger::TheLogger()->Log("Could not init system. FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return;
	}
}
// ***************************************************************

bool cSound::CheckError( FMOD_RESULT ciResult )
{
	if(ciResult != FMOD_OK)
	{
		return false;
	}
	return true;
}
// ***************************************************************

void cSound::Shutdown()
{
	FMOD_RESULT	result; 
	TSoundMap::iterator iterSound;
	for (iterSound = m_apSounds.begin(); iterSound != m_apSounds.end(); iterSound++)
	{
		(iterSound->second)->pSound->release();
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

void cSound::CreateSound( int index, const char * const strFilename )
{
	if (!bValid)
	{
		return;
	}

	FMOD_RESULT	result;
	Sound *		pSound;
	stSounds	* pSounds = DEBUG_NEW stSounds;

	result = m_pSystem->createSound(strFilename, FMOD_HARDWARE|FMOD_CREATESAMPLE, 0, &pSound);
	if(!CheckError(result))
	{
		ILogger::TheLogger()->Log("Could not create sound %s. FMOD error! (%d) %s\n", strFilename, result, FMOD_ErrorString(result));
		return;
	}
	pSounds->pSound = pSound;

	m_apSounds.insert(TSoundPair(index, pSounds));
	ILogger::TheLogger()->Log("Loading sound : %s", strFilename);
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
		ILogger::TheLogger()->Log("Could not Find Sound in PlaySound.\n");
		return;
	}
	pSound = iterSound->second->pSound;
	result = m_pSystem->playSound(FMOD_CHANNEL_REUSE, pSound, false, &pChannel);
	iterSound->second->pChannel = pChannel;
	if(!CheckError(result))
	{
		char strFileName[200];
		pSound->getName(strFileName, 200);
		ILogger::TheLogger()->Log("Could not play sound : %s. FMOD error! (%d) %s\n", strFileName, result, FMOD_ErrorString(result));
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

void cSound::CreateStream( int index, const char * const strFilename )
{
	FMOD_RESULT	result;
	stSounds	* pSounds = DEBUG_NEW stSounds;

	result = m_pSystem->createStream(strFilename, FMOD_HARDWARE|FMOD_CREATESTREAM|FMOD_LOOP_NORMAL, 0, &(pSounds->pSound));
	if(!CheckError(result))
	{
		ILogger::TheLogger()->Log("Could not create stream : %s. FMOD error! (%d) %s\n", strFilename, result, FMOD_ErrorString(result));
		return;
	}

	m_apSounds.insert(TSoundPair(index, pSounds));
	ILogger::TheLogger()->Log("Loading stream : %s", strFilename);
}

void cSound::StopSound( int iSoundIndex )
{
	FMOD_RESULT	result;
	TSoundMap::iterator iterSound;

	iterSound = m_apSounds.find(iSoundIndex);
	if (iterSound == m_apSounds.end())
	{
		ILogger::TheLogger()->Log("Could not Find Sound in StopSound.\n");
		return;
	}

	result = iterSound->second->pChannel->stop();
	if(!CheckError(result))
	{
		ILogger::TheLogger()->Log("Could not stop sound. FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
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
		ILogger::TheLogger()->Log("Could not Find Sound in ChangeMusicVolume.\n");
		return;
	}
	result = iterSound->second->pChannel->getVolume(&fVolume);
	if(!CheckError(result))
	{
		ILogger::TheLogger()->Log("Could not Change Music Volume. FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
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
	ILogger::TheLogger()->Log("New Volume : %f\n", fVolume);
}

void cSound::RemoveSound( int iSoundIndex )
{
	StopSound(iSoundIndex);
	m_apSounds.erase(iSoundIndex);
}