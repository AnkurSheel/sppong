#include "stdafx.h"
#include "Sound.h"
#include "Fmod/fmod.hpp"
#include "Debugging/Logger.h"
#include "Fmod/fmod_errors.h"
#include <vector>

using namespace std;

class cSound
	: public ISound
{
private:
	void CheckError(FMOD_RESULT ciResult);

public:
	cSound();
	~cSound();
	void Init();
	void Shutdown();
	void CreateSound(const char * const strFilename);
	void PlaySound(int iSoundIndex);
	void Update();
private:
		FMOD::System *			m_system;
		vector<FMOD::Sound *>	m_Sounds;
};
// ***************************************************************

cSound::cSound()
: m_system(NULL)
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

	result = FMOD::System_Create(&m_system);
	CheckError(result);	
	
	result= m_system->getVersion(&iVersion);
	CheckError(result);	

	if (iVersion < FMOD_VERSION)
	{
		PostQuitMessage(0);
	}

	result = m_system->getDriverCaps(0, &caps, 0, 0, &speakerMode);
	CheckError(result);

	result = m_system->setSpeakerMode(speakerMode);
	CheckError(result);

	if(caps & FMOD_CAPS_HARDWARE_EMULATED)
	{
		result = m_system->setDSPBufferSize(1024,10);
		CheckError(result);
	}
	result = m_system->init(32, FMOD_INIT_NORMAL, 0);
	CheckError(result);
}
// ***************************************************************

void cSound::CheckError( const FMOD_RESULT ciResult )
{
	if(ciResult != FMOD_OK)
	{
		ILogger::TheLogger()->Log("FMOD error! (%d) %s\n", ciResult, FMOD_ErrorString(ciResult));
		PostQuitMessage(0);
	}
}
// ***************************************************************

void cSound::Shutdown()
{
	FMOD_RESULT	result; 
	vector<FMOD::Sound *>::iterator iterSound;
	for (iterSound = m_Sounds.begin(); iterSound != m_Sounds.end(); iterSound++)
	{
		(*iterSound)->release();
		//CheckError(result);
	}
	m_Sounds.clear();
	if(m_system)
	{
		result = m_system->release();
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

void cSound::CreateSound( const char * const strFilename )
{
	FMOD_RESULT			result;
	FMOD::Sound *		pSound;
	result = m_system->createSound(strFilename, FMOD_HARDWARE, 0, &pSound);
	CheckError(result);
	m_Sounds.push_back(pSound);
}
// ***************************************************************

void cSound::PlaySound( int iSoundIndex )
{
	FMOD_RESULT			result;
	FMOD::Sound *		pSound = NULL;
	FMOD::Channel *		pChannel = NULL;
	
	pSound = m_Sounds[iSoundIndex];
	result = m_system->playSound(FMOD_CHANNEL_FREE, pSound, false, &pChannel);
	CheckError(result);
}
// ***************************************************************

void cSound::Update()
{
	m_system->update();
}
// ***************************************************************
