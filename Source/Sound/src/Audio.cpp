// *****************************************************************************
//  Audio   version:  1.0   Ankur Sheel  date: 2013/01/03
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************

#include "stdafx.h"
#include "Audio.h"
#include "AudioBuffer.hxx"

using namespace Sound;

// *****************************************************************************
cAudio::cAudio()
{

}
// *****************************************************************************
cAudio::~cAudio()
{
	Cleanup();
}

// *****************************************************************************
void cAudio::ResumeAllSounds()
{
	IAudioBuffer * pAudioBuffer = NULL;
	AudioBufferList::iterator iter;
	for(iter = m_ActiveSoundList.begin(); iter != m_ActiveSoundList.end(); iter++)
	{
		pAudioBuffer = (*iter);
		pAudioBuffer->VResume();
	}
	m_bIsPaused = false;
}

// *****************************************************************************
void cAudio::PauseAllSounds()
{
	IAudioBuffer * pAudioBuffer = NULL;
	AudioBufferList::iterator iter;
	for(iter = m_ActiveSoundList.begin(); iter != m_ActiveSoundList.end(); iter++)
	{
		pAudioBuffer = (*iter);
		pAudioBuffer->VPause();
	}
	m_bIsPaused = true;
}

// *****************************************************************************
void cAudio::StopAllSounds()
{
	IAudioBuffer * pAudioBuffer = NULL;
	AudioBufferList::iterator iter;
	for(iter = m_ActiveSoundList.begin(); iter != m_ActiveSoundList.end(); iter++)
	{
		pAudioBuffer = (*iter);
		pAudioBuffer->VStop();
	}
	m_bIsPaused = true;
}

// *****************************************************************************
void cAudio::Cleanup()
{
	IAudioBuffer * pAudioBuffer = NULL;
	AudioBufferList::iterator iter;
	for(iter = m_ActiveSoundList.begin(); iter != m_ActiveSoundList.end(); iter++)
	{
		pAudioBuffer = (*iter);
		pAudioBuffer->VStop();
		m_ActiveSoundList.pop_front();
	}
}

// *****************************************************************************
bool cAudio::HasSoundCard()
{

}
