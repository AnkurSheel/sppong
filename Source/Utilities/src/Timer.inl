// ***************************************************************
// returns if the timer has stopped
// ***************************************************************
inline bool cTimer::IsStopped() const
{
	return m_bTimerStopped;
}
// ***************************************************************

// ***************************************************************
// returns the FPS
// ***************************************************************
inline float cTimer::GetFPS() const
{
	return m_fFPS;
}
// ***************************************************************

// ***************************************************************
// returns the running time
// ***************************************************************
inline float cTimer::GetRunningTime() const
{
	return m_fRunningTime;
}
// ***************************************************************

inline TICK cTimer::GetRunningTicks() const
{
	return (TICK)m_fRunningTime;
}
// ***************************************************************

// ***************************************************************
// returns the elapsed time
// ***************************************************************
inline float cTimer::GetElapsedTime() const
{
	if (m_bTimerStopped)
	{
		return 0.0f ;
	}
	return m_fTimeElapsed;
}