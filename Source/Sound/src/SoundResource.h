// *****************************************************************************
//  SoundResource   version:  1.0   Ankur Sheel  date: 2012/12/29
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************

#include "Resource.h"

namespace Sound
{
	class cSoundResource
		: public Utilities::cResource
	{
	public:
		cSoundResource(const Base::cString & strName);
		~cSoundResource();
		Utilities::IResHandle * VCreateHandle(const char * pBuffer,
			unsigned int uiSize, Utilities::IResCache * pResCache) = 0;
	
	private:
		Base::cString m_strFileName;
	};

	class cSoundResHandle
		: public Utilities::cResHandle
	{
	public:
		cSoundResHandle(Utilities::cResource & resource, unsigned char * pBuffer,
			unsigned int uiSize, Utilities::IResCache * pResCache);
		~cSoundResHandle();
		bool Initialize();
		
	private:
		bool ParseWave(const char * const pWavStream, const unsigned int uiBufferLength);

	private:
		bool					m_bInitialized;
		char *					m_pPCMBuffer;
		int						m_iPCMBufferSize;
		WAVEFORMATEX			m_WaveFormatEx;
		int						m_iLengthMS;
		const Base::cString		m_strSoundFileName;
	};
}