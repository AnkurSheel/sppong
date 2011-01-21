#include "stdafx.h"
#include "Sound.h"
#include "Fmod/fmod.hpp"
#include "Debugging/Logger.h"
#include "Fmod/fmod_errors.h"

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


private:
		FMOD::System*		m_system;
};


cSound::cSound()
: m_system(NULL)
{
}

cSound::~cSound()
{
	Shutdown();
}

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
	if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		result = m_system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
		CheckError(result);

		result = m_system->init(100, FMOD_INIT_NORMAL, 0);
		CheckError(result);
	}
}

void cSound::CheckError( const FMOD_RESULT ciResult )
{
	if(ciResult != FMOD_OK)
	{
		ILogger::TheLogger()->Log("FMOD error! (%d) %s\n", ciResult, FMOD_ErrorString(ciResult));
		PostQuitMessage(0);
	}
}

void cSound::Shutdown()
{
	if(m_system)
	{
		FMOD_RESULT	result = m_system->release();
		CheckError(result);
	}
}

ISound * ISound::CreateSound()
{
	cSound * pSound = DEBUG_NEW cSound();
	return pSound;
}
// ***************************************************************
