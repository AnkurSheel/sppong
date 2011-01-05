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
// ***************************************************************
// Constructor
// ***************************************************************

class cTimer
	: public ITimer
{
private:
	cTimer(const cTimer&){}
	cTimer operator =(const cTimer&){}

public:
	cTimer();
	~cTimer();
	void Start();
	void Stop();
	void Update(); 

	bool IsStopped() const;
	float GetFPS() const;
	float GetRunningTime() const;
	float GetElapsedTime() const; 

private:
	INT64		m_iTicksPerSecond;
	INT64		m_iCurrentTime;
	INT64		m_iLastTime;
	INT64		m_iLastFPSUpdate;
	INT64		m_iFPSUpdateInterval;
	UINT		m_iNumFrames;
	float		m_fRunningTime;
	float		m_fTimeElapsed;
	float		m_fFPS;
	bool		m_bTimerStopped;
};

#include "Timer.inl"

static cTimer * s_pTimer = NULL;

cTimer::cTimer()
: m_iCurrentTime(0)
, m_iLastTime(0)
, m_iLastFPSUpdate(0)
, m_iNumFrames(0)
, m_fFPS(0.0f)
, m_fRunningTime(0.0f)
, m_fTimeElapsed(0.0f)
, m_bTimerStopped(true)
{
	QueryPerformanceFrequency( (LARGE_INTEGER *)&m_iTicksPerSecond );

	m_iFPSUpdateInterval = m_iTicksPerSecond >> 1;
}
// ***************************************************************

// ***************************************************************
// Destructor
// ***************************************************************
cTimer::~cTimer()
{
}
// ***************************************************************

// ***************************************************************
// Starts the timer
// ***************************************************************
void cTimer::Start()
{
	if ( !m_bTimerStopped )
	{
		// Already started
		return;
	}
	QueryPerformanceCounter( (LARGE_INTEGER *)&m_iLastTime );
	m_bTimerStopped = false; 
}
// ***************************************************************

// ***************************************************************
// Stops the timer
// ***************************************************************
void cTimer::Stop()
{
	if ( m_bTimerStopped )
	{
		// Already stopped
		return;
	}
	INT64 iStopTime = 0;
	QueryPerformanceCounter( (LARGE_INTEGER *)&iStopTime );
	m_fRunningTime += (float)(iStopTime - m_iLastTime) / (float)m_iTicksPerSecond;
	m_bTimerStopped = true; 
}
// ***************************************************************

// ***************************************************************
// Updates the timer. Calculates the time elapsed since the last
// update call. Updates the FPS and total running time
// ***************************************************************
void cTimer::Update()
{
	if ( m_bTimerStopped )
	{
		return;
	}

	// Get the current time
	QueryPerformanceCounter( (LARGE_INTEGER *)&m_iCurrentTime );

	m_fTimeElapsed = (float)(m_iCurrentTime - m_iLastTime) / (float)m_iTicksPerSecond;
	m_fRunningTime += m_fTimeElapsed;

	// Update FPS
	m_iNumFrames++;
	if ( m_iCurrentTime - m_iLastFPSUpdate >= m_iFPSUpdateInterval )
	{
		float fCurrentTime = (float)m_iCurrentTime / (float)m_iTicksPerSecond;
		float fLastTime = (float)m_iLastFPSUpdate / (float)m_iTicksPerSecond;
		m_fFPS = (float)m_iNumFrames / (fCurrentTime - fLastTime);

		m_iLastFPSUpdate = m_iCurrentTime;
		m_iNumFrames = 0;
	}
	m_iLastTime = m_iCurrentTime;
}
// ***************************************************************

// ***************************************************************
// Creates a timer
// ***************************************************************
ITimer * ITimer::CreateTimer()
{
	return s_pTimer = DEBUG_NEW cTimer();
}
// ***************************************************************
