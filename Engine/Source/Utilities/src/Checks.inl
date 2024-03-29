inline unsigned int cResourceChecker::GetTotalPhysicalMemory() const
{
	return m_TotalPhysicalMemory;
}

inline unsigned int cResourceChecker::GetAvailablePhysicalMemory() const
{
	return m_AvailablePhysicalMemory;
}

inline unsigned int cResourceChecker::GetTotalVirtualMemory() const
{
	return m_TotalVirtualMemory;
}

inline unsigned int cResourceChecker::GetAvailableVirtualMemory() const
{
	return m_AvailableVirtualMemory;
}

inline unsigned int cResourceChecker::GetTotalHardDiskSpace() const
{
	return m_TotalHardDiskSpace;
}

inline unsigned int cResourceChecker::GetAvailableHardDiskSpace() const
{
	return m_AvailableHardDiskSpace;
}

inline unsigned int cResourceChecker::GetCPUSpeed() const
{
	return m_CPUSpeed;
}

inline Base::cString cResourceChecker::GetCPUBrand() 
{
	if(m_strCPUBrand.IsEmpty())
	{
		CalcCPUBrand();
	}
	return m_strCPUBrand;
}


inline Base::cString cResourceChecker::GetOSVersion()
{
	if(m_strOsVersion.IsEmpty())
	{
		CalcOSVersion();
	}
	return m_strOsVersion;
}
