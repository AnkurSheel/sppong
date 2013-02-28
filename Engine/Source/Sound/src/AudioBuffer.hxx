// *****************************************************************************
//  AudioBuffer   version:  1.0   Ankur Sheel  date: 2013/01/03
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef AudioBuffer_hxx__
#define AudioBuffer_hxx__

namespace Sound
{
	class IAudioBuffer
	{
	public:
		virtual ~IAudioBuffer(){};
		virtual bool VPlay() = 0;
		virtual bool VStop() = 0;
		virtual bool VResume() = 0;
		virtual bool VPause() = 0;
		virtual bool VTogglePause() = 0;
		virtual bool VIsPlaying() = 0;
		virtual bool VRestore() = 0;
		virtual void VSetVolume(const unsigned int uiVolume) = 0;
		virtual float VGetProgress() = 0;
	};
}
#endif // AudioBuffer_hxx__