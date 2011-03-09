// ***************************************************************
//  Sound   version:  1.0   Ankur Sheel  date: 2011/02/16
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Sound_h__
#define Sound_h__

#include "Sound.hxx"
#include "FMOD/fmod.h"
#include <map>

namespace Base
{
	class cString;
}

namespace FMOD
{
	class Sound;
	class Channel;
	class System;
}

namespace MySound
{
	struct stSounds 
	{
		FMOD::Sound * pSound;
		FMOD::Channel *pChannel;
		stSounds();
	};

	typedef std::map<int, stSounds *> TSoundMap;
	typedef std::pair<int, stSounds *> TSoundPair;

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
		void CreateSound(int index, const Base::cString & strFilename);
		void PlaySound(int iSoundIndex);
		void StopSound(int iSoundIndex);
		void Update();
		void CreateStream( int index, const Base::cString & strFilename );
		void ChangeMusicVolume(bool bIncreaseVolume, int iSoundIndex);
		void RemoveSound(int iSoundIndex);
	private:
		FMOD::System *		m_pSystem;
		TSoundMap			m_apSounds;
		bool				bValid;
	};

#include "Sound.inl"

}
#endif // Sound_h__