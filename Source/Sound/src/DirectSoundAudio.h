// *****************************************************************************
//  DirectSoundAudio   version:  1.0   Ankur Sheel  date: 2013/01/03
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef DirectSoundAudio_h__
#define DirectSoundAudio_h__

#include <dsound.h>
#include "Audio.h"

namespace Sound
{
	class cSoundResHandle;
}

namespace Sound
{
	class cDirectSoundAudio
		: public cAudio
	{
	public:
		cDirectSoundAudio();
		~cDirectSoundAudio();
		bool Initialize(const HWND & hwnd);
		void VCleanup();
		IAudioBuffer * InitAudioBuffer(shared_ptr<cSoundResHandle> pSoundResource);

	private:
		bool SetPrimaryBufferFormat(const unsigned short usPrimaryChannels,
			const unsigned long ulPrimaryFreq, const unsigned short usPrimaryBitRate);
		
	protected:
		IDirectSound8 *	m_pDS;
	};
}
#endif // DirectSoundAudio_h__