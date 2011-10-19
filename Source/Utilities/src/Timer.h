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


#include "Timer.hxx"

namespace Utilities
{
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
		TICK GetRunningTicks() const;

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
}
#endif // Timer_h__