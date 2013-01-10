// *****************************************************************************
//  DirectSoundAudioBuffer   version:  1.0   Ankur Sheel  date: 2013/01/07
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "DirectSoundAudioBuffer.h"
#include "AudioBuffer.h"
#include "SoundResource.h"
#include <DxErr.h>

#pragma comment(lib, "dxerr.lib")
using namespace Sound;
using namespace Utilities;
using namespace Base;

// *****************************************************************************
cDirectSoundAudioBuffer::cDirectSoundAudioBuffer(LPDIRECTSOUNDBUFFER pSound,
												 shared_ptr<ISoundResHandle> pResource)
: cAudioBuffer(pResource)
{
	m_pSample = pSound;
	FillBufferWithSound();
}

// *****************************************************************************
bool cDirectSoundAudioBuffer::VPlay()
{
	VStop();

	LPDIRECTSOUNDBUFFER pDSBuffer = GetSoundBuffer();
	if (pDSBuffer == NULL)
	{
		return false;
	}

	return (S_OK == pDSBuffer->Play(0, 0, 0));
}

// *****************************************************************************
bool cDirectSoundAudioBuffer::VStop()
{
	LPDIRECTSOUNDBUFFER pDSBuffer = GetSoundBuffer();
	if (pDSBuffer == NULL)
	{
		return false;
	}
	m_bIsPaused = true;
	pDSBuffer->Stop();
	return true;
}

// *****************************************************************************
bool cDirectSoundAudioBuffer::VResume()
{
	m_bIsPaused = false;
	return VPlay();
}

// *****************************************************************************
bool cDirectSoundAudioBuffer::VTogglePause()
{
	if (m_bIsPaused)
	{
		VResume();
	}
	else
	{
		VPause();
	}
	return true;
}

// *****************************************************************************
bool cDirectSoundAudioBuffer::VPause()
{
	return VStop();
}

// *****************************************************************************
bool cDirectSoundAudioBuffer::VIsPlaying()
{
	LPDIRECTSOUNDBUFFER pDSBuffer = GetSoundBuffer();
	if (pDSBuffer == NULL)
	{
		return false;
	}
	unsigned long ulStatus = 0L;
	pDSBuffer->GetStatus(&ulStatus);
	return ((ulStatus & DSBSTATUS_PLAYING) != 0);
}

// *****************************************************************************
bool cDirectSoundAudioBuffer::VRestore()
{
	if(!RestoreBuffer())
		return false;

	return FillBufferWithSound();
}

// *****************************************************************************
void cDirectSoundAudioBuffer::VSetVolume(const unsigned int uiVolume)
{
	if (uiVolume <0 || uiVolume > 100)
	{
		Log_Write_L1(ILogger::LT_ERROR, "Volume must be between 0 and 100");
		return;
	}

	LPDIRECTSOUNDBUFFER pDSBuffer = GetSoundBuffer();
	if (pDSBuffer == NULL)
	{
		return;
	}

	float fCcoeff = (float)uiVolume/ 100.0f;
	float fLogarithmicProportion = fCcoeff > 0.1f ? 1+log10(fCcoeff) : 0;
	float fRange = (DSBVOLUME_MAX - DSBVOLUME_MIN);
	float fvolume = (fRange * fLogarithmicProportion ) + DSBVOLUME_MIN; 
	m_uiVolume = static_cast<unsigned int>(fvolume);
	
	pDSBuffer->SetVolume(m_uiVolume);
}

// *****************************************************************************
float cDirectSoundAudioBuffer::VGetProgress()
{
	LPDIRECTSOUNDBUFFER pDSBuffer = GetSoundBuffer();
	if (pDSBuffer == NULL)
	{
		return 0.0f;
	}
	unsigned long ulProgress = 0L;
	pDSBuffer->GetCurrentPosition(&ulProgress, NULL);
	float fLength = (float)m_pResource->VGetPCMBufferSize();
	return (float)ulProgress / fLength;
}

// *****************************************************************************
LPDIRECTSOUNDBUFFER cDirectSoundAudioBuffer::GetSoundBuffer()
{
	if (!VRestore())
	{
		return NULL;
	}
	return m_pSample;
}

// *****************************************************************************
bool cDirectSoundAudioBuffer::RestoreBuffer()
{
	if (m_pSample == NULL)
	{
		return false;
	}

	unsigned long ulStatus = 0L;
	m_pSample->GetStatus(&ulStatus);
	int iCount = 0;
	if (ulStatus && DSBSTATUS_BUFFERLOST)
	{
		HRESULT result;
		do 
		{
			result = m_pSample->Restore();
			if (result == DSERR_BUFFERLOST)
			{
				Sleep(10);
			}
		} 
		while ((result = m_pSample->Restore()) == DSERR_BUFFERLOST && ++iCount < 100);
	}
	return(iCount < 100 );
}

// *****************************************************************************
bool cDirectSoundAudioBuffer::FillBufferWithSound()
{
	if (m_pSample == NULL)
	{
		return false;
	}
	HRESULT result;
	if (!RestoreBuffer())
	{
		return false;
	}
	void * pDSLockedBuffer = NULL;
	unsigned long ulLockedBufferSize = 0L;

	int iPCMBufferSize = m_pResource->VGetPCMBufferSize();
	result = m_pSample->Lock(0, iPCMBufferSize, &pDSLockedBuffer, &ulLockedBufferSize,
		NULL, NULL, NULL);
	if (FAILED(result))
	{
		Log_Write_L1(ILogger::LT_ERROR, cString("Could not lock sound buffer ")
			+ DXGetErrorString(result) + " : " + DXGetErrorDescription(result))
		return false;
	}
	
	shared_ptr<cSoundResHandle> pHandle = dynamic_pointer_cast<cSoundResHandle>(m_pResource);

	if (iPCMBufferSize == 0)
	{
		FillMemory((unsigned char *) pDSLockedBuffer, ulLockedBufferSize,
			(unsigned char)pHandle->GetFormat()->wBitsPerSample == 8 ? 128 : 0);
	}
	else
	{
		CopyMemory(pDSLockedBuffer, m_pResource->VGetPCMBuffer(), iPCMBufferSize);
		if (iPCMBufferSize < (int)ulLockedBufferSize)
		{
			FillMemory((unsigned char *) pDSLockedBuffer + iPCMBufferSize,
				ulLockedBufferSize - iPCMBufferSize, 
				(unsigned char)pHandle->GetFormat()->wBitsPerSample == 8 ? 128 : 0);
		}
	}
	m_pSample->Unlock(pDSLockedBuffer, ulLockedBufferSize, NULL, 0);
	return true;
}