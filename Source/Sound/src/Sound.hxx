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
		virtual void Init() = 0;
		virtual void CreateSound( int index, const Base::cString & strFilename ) = 0;
		virtual void PlaySound(int iSoundIndex) = 0;
		virtual void Update() = 0;
		virtual void CreateStream( int index, const Base::cString & strFilename ) = 0;
		virtual void StopSound(int iSoundIndex) = 0;
		virtual void ChangeMusicVolume(bool bIncreaseVolume, int iSoundIndex) = 0;
		virtual void RemoveSound(int iSoundIndex) = 0;
		SOUND_API static ISound * CreateSound();
	};
}
#endif // Sound_h__