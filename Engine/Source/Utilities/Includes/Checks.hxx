// ***************************************************************
//  Checks   version:  1.0   Ankur Sheel  date: 2011/02/15
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Checks_hxx__
#define Checks_hxx__

#include "UtilitiesDefines.h"

namespace Base
{
	class cString;
}

namespace Utilities
{
	class IResourceChecker
	{
	public:
		UTILITIES_API virtual ~IResourceChecker(){}
		UTILITIES_API virtual bool IsOnlyInstance(const Base::cString &  gameTitle) = 0;
		UTILITIES_API virtual bool CheckMemory( const UINT physicalRAMNeeded, const UINT virtualRAMNeeded) = 0; 
		UTILITIES_API virtual bool CheckHardDisk(const unsigned int diskSpaceNeeded) = 0; 
		UTILITIES_API virtual bool CheckCPUSpeedinMhz(const unsigned int uMinSpeedReq) = 0;
		UTILITIES_API virtual unsigned int GetTotalPhysicalMemory() const = 0;
		UTILITIES_API virtual unsigned int GetTotalVirtualMemory() const = 0;
		UTILITIES_API virtual unsigned int GetAvailablePhysicalMemory() const = 0;
		UTILITIES_API virtual unsigned int GetAvailableVirtualMemory() const = 0;
		UTILITIES_API virtual unsigned int GetTotalHardDiskSpace() const = 0;
		UTILITIES_API virtual unsigned int GetAvailableHardDiskSpace() const = 0;
		UTILITIES_API virtual unsigned int GetCPUSpeed() const = 0;
		UTILITIES_API virtual Base::cString GetCPUBrand() = 0;
		UTILITIES_API virtual Base::cString GetOSVersion() = 0;
		UTILITIES_API static void Destroy();
		UTILITIES_API static IResourceChecker * GetInstance();
	};
}
#endif // Checks_h__
