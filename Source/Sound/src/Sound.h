// ***************************************************************
//  Sound   version:  1.0   Ankur Sheel  date: 12/30/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Sound_h__
#define Sound_h__

#include "SoundDefines.h"

class ISound
{
public:
	virtual ~ISound(){};
	SOUND_API virtual void Init() = 0;
	SOUND_API virtual void Shutdown() = 0;
	SOUND_API static ISound * CreateSound();
};
#endif // Sound_h__