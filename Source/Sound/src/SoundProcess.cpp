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
#include "ResourceManager.hxx"

using namespace Sound;
using namespace Base;
using namespace Utilities;

// *****************************************************************************
cSoundProcess::cSoundProcess(const unsigned long ulType, 
							 shared_ptr<ISoundResHandle> pSoundResource,
							 const int iVolume, const bool bLooping)
: ISoundProcess(ulType)
, m_pSoundHandle(pSoundResource)
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
	m_pAudioBuffer->VSetVolume(m_iVolume);
	Play();
}

// *****************************************************************************
void cSoundProcess::VUpdate(const int iDeltaMilliSeconds)
{
	cProcess::VUpdate(iDeltaMilliSeconds);
	if (!IsPlaying())
	{
		if(m_bLooping)
		{
			Play();
		}
		else
		{
			VKill();
		}
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
void cSoundProcess::Play()
{
	if (m_pAudioBuffer == NULL)
	{
		return;
	}
	m_pAudioBuffer->VPlay();
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
void cSoundProcess::VTogglePause()
{
	if (m_pAudioBuffer)
	{
		m_pAudioBuffer->VTogglePause();
	}
	cProcess::VTogglePause();
}

// *****************************************************************************
shared_ptr<ISoundProcess> ISoundProcess::CreateSoundProcess(const unsigned long ulType,
															const cString & strSoundFile,
															const int iVolume,
															const bool bLooping)
{
	shared_ptr<cSoundResource> pResource(DEBUG_NEW cSoundResource(strSoundFile));
	shared_ptr<ISoundResHandle> pHandle = static_pointer_cast<ISoundResHandle>(IResourceManager::GetInstance()->VGetResourceCache()->GetHandle(*pResource));
	return shared_ptr<ISoundProcess>(DEBUG_NEW cSoundProcess(ulType, pHandle, iVolume, bLooping));
}