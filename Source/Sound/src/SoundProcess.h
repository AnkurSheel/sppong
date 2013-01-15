// *****************************************************************************
//  SoundProcess   version:  1.0   Ankur Sheel  date: 2013/01/08
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef SoundProcess_h__
#define SoundProcess_h__

#include "SoundProcess.hxx"

namespace Sound
{
	class cSoundResHandle;
	class IAudioBuffer;
}
namespace Sound
{
	class cSoundProcess
		: public ISoundProcess
	{
	public:
		cSoundProcess(const unsigned long ulType, 
			shared_ptr<ISoundResHandle> pSoundResource, const int iVolume,
			const bool bLooping);
		~cSoundProcess();
		void VInitialize();
		void VUpdate(const int iDeltaMilliSeconds);
		void VKill();
		void VTogglePause();
		void Play();
		void Stop();
		bool IsPlaying();

	private:
		shared_ptr<ISoundResHandle>		m_pSoundHandle;
		shared_ptr<IAudioBuffer>		m_pAudioBuffer;
		int								m_iVolume;
		bool							m_bLooping;
	};
}
#endif // SoundProcess_h__