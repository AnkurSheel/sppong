inline bool cProcess::IsDead() const
{
	return m_bKill;
}

inline int cProcess::GetType() const
{
	return m_iType;
}

inline void cProcess::SetType(const int iType)
{
	m_iType = iType;
}

inline bool cProcess::IsActive() const
{
	return m_bActive;
}

inline bool cProcess::SetActive(const bool bActive)
{
	m_bActive = bActive;
}

inline bool cProcess::IsPaused() const
{
	return m_bPaused;
}

inline bool cProcess::IsInitialized() const
{
	return !m_bInitialUpdate;
}

inline shared_ptr<cProcess> const cProcess::GetNext() const
{
	return m_pNext;
}

inline void cProcess::SetNext(shared_ptr<cProcess> pNext)
{
	m_pNext = pNext;
}

inline void cProcess::TogglePause()
{
	m_bPaused = !m_bPaused;
}

inline bool cProcess::IsAttached() const
{
	if(m_uProcessFlags & PROCESS_FLAG_ATTACHED) 
		return true;
		
	return false;
}