#include "stdafx.h"
#include "Sound.h"
#include "Fmod/fmod.hpp"

Sound::Sound()
{

}

Sound::~Sound()
{
}

void Sound::Init()
{
	FMOD_RESULT			result;
	FMOD::System*		system;
	UINT				iVersion;
	FMOD_CAPS			caps;
	FMOD_SPEAKERMODE	speakerMode;

	result = FMOD::System_Create(&system);
	CheckError(result);	
	
	result= system->getVersion(&iVersion);
	CheckError(result);	

	if (iVersion < FMOD_VERSION)
	{
		PostQuitMessage(0);
	}

	result = system->getDriverCaps(0, &caps, 0, 0, &speakerMode);
	CheckError(result);

	result = system->setSpeakerMode(speakerMode);
	CheckError(result);

	if(caps & FMOD_CAPS_HARDWARE_EMULATED)
	{
		result = system->setDSPBufferSize(1024,10);
		CheckError(result);
	}
	result = system->init(100, FMOD_INIT_NORMAL, 0);
	if (result = FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		result = system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
		CheckError(result);

		result = system->init(100, FMOD_INIT_NORMAL, 0);
		CheckError(result);
	}
}

void Sound::CheckError( const int ciResult )
{
	if(ciResult != FMOD_OK)
	{
		//error
		PostQuitMessage(0);
	}
}