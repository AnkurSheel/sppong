// ***************************************************************
//  Timer   version:  1.0   Ankur Sheel  date: 05/01/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Timer_h__
#define Timer_h__

#include "UtilitiesDefines.h"

class cTimer
{
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

	cTimer(const cTimer&){}
	cTimer operator =(const cTimer&){}

public:
	UTILITIES_API cTimer();
	UTILITIES_API ~cTimer();
	UTILITIES_API void Start();
	UTILITIES_API void Stop();
	UTILITIES_API void Update(); 

	UTILITIES_API bool IsStopped();
	UTILITIES_API float GetFPS();
	UTILITIES_API float GetRunningTime();
	UTILITIES_API float GetElapsedTime(); 

};

#include "Timer.inl"

#endif // Timer_h__