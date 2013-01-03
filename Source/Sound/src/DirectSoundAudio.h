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
	class cDirectSoundAudio
		: public cAudio
	{
	public:
		cDirectSoundAudio();
		~cDirectSoundAudio();

	protected:
		IDirectSound *	m_pDS;
	};
}
#endif // DirectSoundAudio_h__