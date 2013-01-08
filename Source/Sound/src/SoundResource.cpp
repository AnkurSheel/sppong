// *****************************************************************************
//  SoundResource   version:  1.0   Ankur Sheel  date: 2012/12/29
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "SoundResource.h"
#include "FileInput.hxx"

using namespace Utilities;
using namespace Base;
using namespace Sound;

// *****************************************************************************
cSoundResource::cSoundResource(const Base::cString & strName)
: cResource(strName)
{
	
}

// *****************************************************************************
cSoundResource::~cSoundResource()
{

}

// *****************************************************************************
IResHandle * cSoundResource::VCreateHandle(const char * pBuffer, 
										   unsigned int uiSize,
										   IResCache * pResCache)
{
	return DEBUG_NEW cSoundResHandle(*this, (unsigned char *)pBuffer, uiSize, pResCache);
}

// *****************************************************************************
ISoundResHandle::ISoundResHandle(Utilities::cResource & resource,
								 unsigned char * pBuffer, unsigned int uiSize,
								 IResCache * pResCache)
: cResHandle(resource, (char *)pBuffer, uiSize, pResCache)
{

}
// *****************************************************************************
cSoundResHandle::cSoundResHandle(Utilities::cResource & resource,
								 unsigned char * pBuffer, unsigned int uiSize,
								 IResCache * pResCache)
: ISoundResHandle(resource, pBuffer, uiSize, pResCache)
, m_bInitialized(false)
, m_pPCMBuffer(NULL)
, m_iPCMBufferSize(0)
, m_iLengthMS(0)
, m_strSoundFileName(resource.VGetFileName())
{

}
// *****************************************************************************
cSoundResHandle::~cSoundResHandle()
{
	SAFE_DELETE_ARRAY(m_pPCMBuffer);
}
// *****************************************************************************
bool cSoundResHandle::VInitialize()
{
	if (!m_bInitialized)
	{
		//TODO - find sound type
		ParseWave(m_pBuffer, m_iBufferSize);
		m_bInitialized = true;
	}
	return true;
}

// *****************************************************************************
bool cSoundResHandle::ParseWave(const char * const pWavStream,
	const unsigned int uiBufferLength)
{
	unsigned long uiFile = 0;
	unsigned long uiFileEnd = 0;
	unsigned long uiLength = 0;
	unsigned long uiType = 0;
	unsigned long uiPos = 0;

	// mmioFOURCC -- converts four chars into a 4 byte integer code.
	// The first 4 bytes of a valid .wav file is 'R','I','F','F' 
	uiType = *((unsigned long  *)(pWavStream + uiPos));
	uiPos += sizeof(unsigned long);
	if(uiType != mmioFOURCC('R', 'I', 'F', 'F'))
	{
		return false;
	}
	uiLength = *((unsigned long *)(pWavStream + uiPos));
	uiPos += sizeof(unsigned long);
	uiType = *((unsigned long *)(pWavStream + uiPos));
	uiPos +=sizeof(unsigned long);
	// 'W','A','V','E' for a legal .wav file 
	if(uiType != mmioFOURCC('W', 'A', 'V', 'E'))
	{
		//not a WAV
		return false;
	}
	uiFileEnd = uiLength - 4;
	memset(&m_WaveFormatEx, 0, sizeof(WAVEFORMATEX));
	while(uiFile < uiFileEnd)
	{
		uiType = *((unsigned long *)(pWavStream + uiPos)); 
		uiPos += sizeof(unsigned long);
		uiFile += sizeof(unsigned long);
		uiLength= *((unsigned long *)(pWavStream + uiPos));
		uiPos +=sizeof(unsigned long);
		uiFile += sizeof(unsigned long);
		switch(uiType)
		{ 
		case mmioFOURCC('f', 'a', 'c', 't'):
				Log_Write_L1(ILogger::LT_ERROR, "This wav file is compressed. We don't handle compressed wav at this time");
				break; 

		case mmioFOURCC('f', 'm', 't', ' '):
			memcpy(&m_WaveFormatEx, pWavStream + uiPos, uiLength);
			uiPos += uiLength; 
			m_WaveFormatEx.cbSize = uiLength;
			break;

		case mmioFOURCC('d', 'a', 't', 'a'):
			m_pPCMBuffer = DEBUG_NEW char[uiLength];
			m_iPCMBufferSize = uiLength;
			memcpy(m_pPCMBuffer, pWavStream + uiPos, uiLength);
			uiPos +=uiLength;
			break;
		}
		uiFile += uiLength;
		// If both blocks have been seen, we can return true.
		if( (m_pPCMBuffer != 0 ) && (m_iPCMBufferSize != 0) )
		{
			m_iLengthMS = ( m_iPCMBufferSize * 1000 ) / m_WaveFormatEx.nAvgBytesPerSec;
			return true;
		}
		// Increment the pointer past the block we just read and make sure the pointer is word aligned.
		if (uiLength & 1) 
		{
			++uiPos; 
			++uiFile;
		}
	}
	Log_Write_L1(ILogger::LT_ERROR, "This wav file didnt contain all the right pieces");
	return false;
}

// *****************************************************************************
int cSoundResHandle::VGetPCMBufferSize() const
{
	return m_iPCMBufferSize;
}

// *****************************************************************************
WAVEFORMATEX const * cSoundResHandle::GetFormat() const
{
	return &m_WaveFormatEx; 
}

// *****************************************************************************
char const * Sound::cSoundResHandle::VGetPCMBuffer() const
{
	return m_pPCMBuffer;
}