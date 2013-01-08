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

IAudio * cAudio::s_pAudio = NULL;

// *****************************************************************************
cAudio::cAudio()
: m_bIsPaused(false)
, m_bInitialized(false)
{

}
// *****************************************************************************
cAudio::~cAudio()
{
	VCleanup();
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
void cAudio::VCleanup()
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
IAudio * IAudio::GetInstance()
{
	if (cAudio::s_pAudio == NULL)
	{
		cAudio::s_pAudio = cAudio::Create();
	}
	return cAudio::s_pAudio;
}
// *****************************************************************************
void IAudio::Destroy()
{
	SAFE_DELETE(cAudio::s_pAudio);
}
