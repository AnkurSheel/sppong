// *****************************************************************************
//  Audio   version:  1.0   Ankur Sheel  date: 2013/01/03
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef Audio_h__
#define Audio_h__

#include "Audio.hxx"

namespace Sound
{
	class IAudioBuffer;
}

namespace Sound
{
	class cAudio
		: public IAudio
	{
	private:
		typedef std::list<IAudioBuffer *> AudioBufferList;

	public:
		cAudio();
		~cAudio();
		void StopAllSounds();
		void PauseAllSounds();
		void ResumeAllSounds();
		void Cleanup();

		static bool HasSoundCard();

	protected:
		AudioBufferList		m_ActiveSoundList;
		bool				m_bIsPaused;
		bool				m_bInitialized;
	};
}
#endif // Audio_h__