#ifndef Checks_h
#define Checks_h

#include "UtilitiesDefines.h"

namespace Utilities
{
	class IResourceChecker
	{
	public:
		UTILITIES_API virtual ~IResourceChecker(){}
		UTILITIES_API virtual bool IsOnlyInstance(LPCTSTR gameTitle) = 0;
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
		UTILITIES_API static IResourceChecker * TheResourceChecker();
	};
}
#endif
