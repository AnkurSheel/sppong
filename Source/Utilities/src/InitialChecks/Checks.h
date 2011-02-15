#include "Checks.hxx"

namespace Utilities
{
	class cResourceChecker
		: public IResourceChecker
	{
	private:
		int StartTimingCPU();
		void UpdateCPUTime(); 
		int CalcCPUSpeed(); 
	public:
		cResourceChecker();
		bool IsOnlyInstance(LPCTSTR gameTitle);
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
		static void CreateResourceChecker();
	private:
		unsigned int m_TotalPhysicalMemory;
		unsigned int m_AvailablePhysicalMemory;
		unsigned int m_TotalVirtualMemory;
		unsigned int m_AvailableVirtualMemory;
		unsigned int m_AvailableHardDiskSpace;
		unsigned int m_TotalHardDiskSpace;
		unsigned int m_CPUSpeed;
	};

	static cResourceChecker * s_pResourceChecker = NULL;
}
