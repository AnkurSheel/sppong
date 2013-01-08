#include "AudioBuffer.h"
// *****************************************************************************
//  DirectSoundAudioBuffer   version:  1.0   Ankur Sheel  date: 2013/01/07
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef DirectSoundAudioBuffer_h__
#define DirectSoundAudioBuffer_h__

#include <dsound.h>

namespace Sound
{	
	class cSoundResHandle;
}

namespace Sound
{
	class cDirectSoundAudioBuffer
		: public cAudioBuffer
	{
	public:
		cDirectSoundAudioBuffer(LPDIRECTSOUNDBUFFER pSound, shared_ptr<cSoundResHandle> pResource);

	private:
		bool VPlay(const unsigned int uiVolume, const bool bLooping);
		bool VStop();
		bool VResume();
		bool VTogglePause();
		bool VPause();
		bool VIsPlaying();
		bool VRestore();
		void VSetVolume(const unsigned int uiVolume);
		float VGetProgress();
		LPDIRECTSOUNDBUFFER GetSoundBuffer();
		bool RestoreBuffer();
		bool FillBufferWithSound();

	private:
		LPDIRECTSOUNDBUFFER		m_pSample;


	};
}
#endif // DirectSoundAudioBuffer_h__