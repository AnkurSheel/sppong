// *****************************************************************************
//  SoundProcess   version:  1.0   Ankur Sheel  date: 2013/01/08
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef SoundProcess_hxx__
#define SoundProcess_hxx__

#include "SoundDefines.h"
#include "Process.h"

namespace Sound
{
	class ISoundResHandle;
	class IAudioBuffer;
}
namespace Sound
{
	class ISoundProcess
		: public Utilities::cProcess
	{
	public:
		ISoundProcess(const unsigned long ulType)
			: Utilities::cProcess(ulType){}
		virtual ~ISoundProcess(){};
		SOUND_API static shared_ptr<ISoundProcess> CreateSoundProcess(const unsigned long ulType,
			const Base::cString & strSoundFile, const int iVolume, 
			const bool bLooping);
	};
}
#endif // SoundProcess_hxx__