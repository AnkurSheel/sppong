// *****************************************************************************
//  AudioBuffer   version:  1.0   Ankur Sheel  date: 2013/01/03
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef AudioBuffer_h__
#define AudioBuffer_h__

#include "AudioBuffer.hxx"

namespace Sound
{
	class cSoundResHandle;
}

namespace Sound
{
	class cAudioBuffer
		: public IAudioBuffer
	{
	public:
		~cAudioBuffer();

	protected:
		cAudioBuffer(shared_ptr<cSoundResHandle> pResource);

	protected:
		shared_ptr<cSoundResHandle>		m_pResource;

		bool							m_bIsPaused;
		bool							m_bIsLooping;
		unsigned int					m_uiVolume;
	};
}
#endif // AudioBuffer_h__
