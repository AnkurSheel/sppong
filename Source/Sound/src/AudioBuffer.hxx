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

#include "SoundDefines.h"

namespace Sound
{
	class IAudioBuffer
	{
	public:
		virtual ~IAudioBuffer(){};
		virtual bool VStop() = 0;
		virtual bool VResume() = 0;
		virtual bool VPause() = 0;
	};
}
#endif // AudioBuffer_hxx__