// ***************************************************************
//  Timer   version:  1.0   Ankur Sheel  date: 05/01/2008
//  -------------------------------------------------------------
//
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
//
// ***************************************************************

#include "stdafx.h"
#include "Timer.h"

using namespace Utilities;

// ***************************************************************
Utilities::cTimer::cTimer()
: m_iCurrentTime(0)
, m_iLastUpdateTime(0)
, m_iLastFPSUpdateTime(0)
, m_iNumFrames(0)
, m_iTotalsFrames(0)
, m_fFPS(0.0f)
, m_fRunningTime(0.0f)
, m_fDeltaTime(0.0f)
, m_bTimerStopped(true)
{
    // Check how many times per second the system counter fires
	if(!QueryPerformanceFrequency( (LARGE_INTEGER *)&m_iTicksPerSecond ))
	{
		Log_Write_L2(ILogger::LT_ERROR, "No support for the high performance counter");
	    PostQuitMessage(0);
	}

    // update every half second
	m_iFPSUpdateInterval = m_iTicksPerSecond >> 1;
}
// ***************************************************************

// ***************************************************************
// Destructor
// ***************************************************************
Utilities::cTimer::~cTimer()
{
}

// ***************************************************************
cTimer * Utilities::cTimer::Create()
{
	return DEBUG_NEW cTimer();
}

// ***************************************************************
// Starts the timer
// ***************************************************************
void Utilities::cTimer::VStartTimer()
{
	if (m_bTimerStopped )
	{
		// Get the current value of the high-resolution performance counter.
		QueryPerformanceCounter( (LARGE_INTEGER *)&m_iLastUpdateTime );
		m_bTimerStopped = false;
	}
}

// ***************************************************************
// Stops the timer
// ***************************************************************
void Utilities::cTimer::VStopTimer()
{
	if (!m_bTimerStopped )
	{
		INT64 iStopTime = 0;

		// Get the current value of the high-resolution performance counter.
		QueryPerformanceCounter( (LARGE_INTEGER *)&iStopTime );

		m_fRunningTime += (float)(iStopTime - m_iLastUpdateTime) / (float)m_iTicksPerSecond;
		m_bTimerStopped = true;
	}
}

// ***************************************************************
// Updates the timer. Calculates the time elapsed since the last
// update call. Updates the FPS and total running time
// ***************************************************************
void Utilities::cTimer::VOnUpdate()
{
	if (!m_bTimerStopped )
	{
		// Get the current value of the high-resolution performance counter.
		QueryPerformanceCounter( (LARGE_INTEGER *)&m_iCurrentTime );

		m_fDeltaTime = (float)(m_iCurrentTime - m_iLastUpdateTime) / (float)m_iTicksPerSecond;
		m_fRunningTime += m_fDeltaTime;

		m_iNumFrames++;
		m_iTotalsFrames++;

		if ( m_iCurrentTime - m_iLastFPSUpdateTime >= m_iFPSUpdateInterval )
		{
			// Calculate FPS
			float fCurrentTime = (float)m_iCurrentTime / (float)m_iTicksPerSecond;
			float fLastTime = (float)m_iLastFPSUpdateTime / (float)m_iTicksPerSecond;
			m_fFPS = (float)m_iNumFrames / (fCurrentTime - fLastTime);

			m_iLastFPSUpdateTime = m_iCurrentTime;
			m_iNumFrames = 0;
		}
		m_iLastUpdateTime = m_iCurrentTime;
	}
}

// ***************************************************************
// Creates a timer
// ***************************************************************
ITimer * ITimer::CreateTimer()
{
	return cTimer::Create();
}
