// ***************************************************************
//  Checks   version:  1.0   Ankur Sheel  date: 2011/02/15
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Checks_h__
#define Checks_h__

#include "Checks.hxx"

namespace Utilities
{
	class cResourceChecker
		: public IResourceChecker
		, public Base::cNonCopyable
	{
	public:
		bool IsOnlyInstance(const Base::cString &  gameTitle);
		bool CheckMemory( const UINT physicalRAMNeeded, const UINT virtualRAMNeeded); 
		bool CheckHardDisk(const unsigned int diskSpaceNeeded); 
		bool CheckCPUSpeedinMhz(const unsigned int uMinSpeedReq);
		unsigned int GetTotalPhysicalMemory() const;
		unsigned int GetTotalVirtualMemory() const;
		unsigned int GetAvailableVirtualMemory() const;
		unsigned int GetAvailablePhysicalMemory() const;
		unsigned int GetTotalHardDiskSpace() const;
		unsigned int GetAvailableHardDiskSpace() const;
		unsigned int GetCPUSpeed() const;
		Base::cString GetCPUBrand();
		Base::cString GetOSVersion();
		static void CreateResourceChecker();
		static void Destroy();
	
	private:
		cResourceChecker();
		int StartTimingCPU();
		void UpdateCPUTime(); 
		int CalcCPUSpeed(); 
		void CalcCPUBrand();
		void CalcOSVersion();
		
	private:
		unsigned int	m_TotalPhysicalMemory;
		unsigned int	m_AvailablePhysicalMemory;
		unsigned int	m_TotalVirtualMemory;
		unsigned int	m_AvailableVirtualMemory;
		unsigned int	m_AvailableHardDiskSpace;
		unsigned int	m_TotalHardDiskSpace;
		unsigned int	m_CPUSpeed;
		Base::cString	m_strCPUBrand;
		Base::cString	m_strOsVersion;
	
	public:
		static cResourceChecker * s_pResourceChecker;
	};

#include "Checks.inl"
}
#endif // Checks_h__
