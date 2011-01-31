// ***************************************************************
//  Sound   version:  1.0   Ankur Sheel  date: 12/30/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Sound_h__
#define Sound_h__

#include "SoundDefines.h"

class ISound
{
public:
	virtual ~ISound(){};
	SOUND_API virtual void Init() = 0;
	SOUND_API static ISound * CreateSound();
	SOUND_API virtual void CreateSound( int index, const char * const strFilename ) = 0;
	SOUND_API virtual void PlaySound(int iSoundIndex) = 0;
	SOUND_API virtual void Update() = 0;
	SOUND_API virtual void CreateStream( int index, const char * const strFilename ) = 0;
	SOUND_API virtual void StopSound(int iSoundIndex) = 0;
	SOUND_API virtual void ChangeMusicVolume(bool bIncreaseVolume, int iSoundIndex) = 0;
	SOUND_API virtual void RemoveSound(int iSoundIndex) = 0;
};
#endif // Sound_h__