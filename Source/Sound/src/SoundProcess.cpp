// *****************************************************************************
//  SoundProcess   version:  1.0   Ankur Sheel  date: 2013/01/08
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "SoundProcess.h"
#include "Audio.hxx"
#include "SoundResource.h"
#include "AudioBuffer.hxx"

using namespace Sound;

// *****************************************************************************
cSoundProcess::cSoundProcess(shared_ptr<ISoundResHandle> pSoundResource,
							 const int iVolume, const bool bLooping)
: m_pSoundHandle(pSoundResource)
, m_iVolume(iVolume)
, m_bLooping(bLooping)
{

}

// *****************************************************************************
cSoundProcess::~cSoundProcess()
{
	if (m_pAudioBuffer)
	{
		IAudio::GetInstance()->VReleaseAudioBuffer(m_pAudioBuffer.get());
	}
}
// *****************************************************************************
void cSoundProcess::VInitialize()
{
	cProcess::VInitialize();
	if (m_pSoundHandle == NULL)
	{
		return;
	}
	m_pSoundHandle->VInitialize();
	IAudioBuffer * pAudioBuffer = IAudio::GetInstance()->VInitializeAudioBuffer(m_pSoundHandle);
	if (pAudioBuffer == NULL)
	{
		VKill();
		return;
	}
	m_pAudioBuffer.reset(pAudioBuffer);
	Play(m_iVolume, m_bLooping);
}

// *****************************************************************************
void cSoundProcess::VUpdate(const int iDeltaMilliSeconds)
{
	cProcess::VUpdate(iDeltaMilliSeconds);
	if (!m_bInitialUpdate && !IsPlaying())
	{
		VKill();
	}
	if (IsDead() && m_bLooping)
	{
		Play(m_iVolume, m_bLooping);
	}
}

// *****************************************************************************
void cSoundProcess::VKill()
{
	if (IsPlaying())
	{
		Stop();
	}
	cProcess::VKill();
}

// *****************************************************************************
void cSoundProcess::Play(const int iVolume, const bool bLooping)
{
	if (m_pAudioBuffer == NULL)
	{
		return;
	}
	m_pAudioBuffer->VPlay(iVolume, bLooping);
}

// *****************************************************************************
void cSoundProcess::Stop()
{
	if (m_pAudioBuffer)
	{
		m_pAudioBuffer->VStop();
	}
}

// *****************************************************************************
bool cSoundProcess::IsPlaying() 
{
	if (m_pSoundHandle == NULL || m_pAudioBuffer == NULL)
	{
		return false;
	}
	return m_pAudioBuffer->VIsPlaying();
}

// *****************************************************************************
shared_ptr<ISoundProcess> ISoundProcess::CreateSoundProcess(shared_ptr<ISoundResHandle> pSoundResource,
			const int iVolume, const bool bLooping)
{
	return shared_ptr<ISoundProcess>(DEBUG_NEW cSoundProcess(pSoundResource, iVolume, bLooping));
}