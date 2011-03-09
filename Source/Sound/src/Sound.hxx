// ***************************************************************
//  Sound   version:  1.0   Ankur Sheel  date: 2011/02/16
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Sound_hxx__
#define Sound_hxx__

#include "SoundDefines.h"

namespace Base
{
	class cString;
}

namespace MySound
{
	class ISound
	{
	public:
		virtual ~ISound(){};
		SOUND_API virtual void Init() = 0;
		SOUND_API static ISound * CreateSound();
		SOUND_API virtual void CreateSound( int index, const Base::cString & strFilename ) = 0;
		SOUND_API virtual void PlaySound(int iSoundIndex) = 0;
		SOUND_API virtual void Update() = 0;
		SOUND_API virtual void CreateStream( int index, const Base::cString & strFilename ) = 0;
		SOUND_API virtual void StopSound(int iSoundIndex) = 0;
		SOUND_API virtual void ChangeMusicVolume(bool bIncreaseVolume, int iSoundIndex) = 0;
		SOUND_API virtual void RemoveSound(int iSoundIndex) = 0;
	};
}
#endif // Sound_h__