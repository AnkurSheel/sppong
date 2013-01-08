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

#include "Process.h"

namespace Sound
{
	class cSoundResHandle;
	class IAudioBuffer;
}
namespace Sound
{
	class cSoundProcess
		: public Utilities::cProcess
	{
	public:
		cSoundProcess(shared_ptr<cSoundResHandle> pSoundResource, const int iVolume,
			const bool bLooping);
		~cSoundProcess();
		void VInitialize();
		void VUpdate(const int iDeltaMilliSeconds);
		void VKill();
		void Play(const int iVolume, const bool bLooping);
		void Stop();
		bool IsPlaying();

	private:
		shared_ptr<cSoundResHandle>		m_pSoundHandle;
		shared_ptr<IAudioBuffer>		m_pAudioBuffer;
		int								m_iVolume;
		bool							m_bLooping;
	};
}
#endif // SoundProcess_h__