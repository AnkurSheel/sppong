#include "stdafx.h"
#include "Checks.h"
#include <direct.h>
#include <math.h>
#include <time.h>
#include <mmsystem.h>
#include <intrin.h>

using namespace Base;
using namespace Utilities;

cResourceChecker::cResourceChecker()
: m_TotalPhysicalMemory(0)
, m_AvailablePhysicalMemory(0)
, m_TotalVirtualMemory(0)
, m_AvailableVirtualMemory(0)
, m_AvailableHardDiskSpace(0)
, m_TotalHardDiskSpace(0)
, m_CPUSpeed(0)
{
}

bool cResourceChecker::IsOnlyInstance(const cString & gameTitle) 
{ 
	// Find the window. If active, set and return false 
	// Only one game instance may have this mutex at a time... 
	HANDLE handle = CreateMutex(NULL, TRUE, gameTitle.GetData()); 
	
	if (GetLastError() != ERROR_SUCCESS) 
	{ 
		HWND hWnd = FindWindow(NULL, gameTitle.GetData()); 
		if (hWnd) 
		{ 
			// An instance of your game is already running. 
			ShowWindow(hWnd, SW_SHOWNORMAL); 
			SetFocus(hWnd); 
			SetForegroundWindow(hWnd); 
			SetActiveWindow(hWnd);
			Log_Write_L1(ILogger::LT_ERROR, "An instance is already running");
			return false; 
		} 
	} 
	return true; 
}

void cResourceChecker::CalcOSVersion()
{ 
	OSVERSIONINFOEX osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	GetVersionEx((OSVERSIONINFO*) &osvi);

	if(osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 1 && osvi.wProductType == VER_NT_WORKSTATION)
	{
		m_strOsVersion = "Windows 7";
	}
	else if(osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 1 && osvi.wProductType != VER_NT_WORKSTATION)
	{
		m_strOsVersion = "Windows Server 2008 R2";
	}
	else if(osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0 && osvi.wProductType != VER_NT_WORKSTATION)
	{
		m_strOsVersion = "Windows Server 2008";
	}
	else if(osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0 && osvi.wProductType == VER_NT_WORKSTATION)
	{
		m_strOsVersion = "Windows Vista";
	}
	else if(osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2 && GetSystemMetrics(SM_SERVERR2) != 0)
	{
		m_strOsVersion = "Windows Server 2003 R2";
	}
	else if(osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2 && GetSystemMetrics(SM_SERVERR2) == 0)
	{
		m_strOsVersion = "Windows Server 2003";
	}
	else if(osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1)
	{
		m_strOsVersion = "Windows XP";
	}
	else if(osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
	{
		m_strOsVersion = "Windows 2000";
	}

	if(osvi.wSuiteMask && VER_SUITE_PERSONAL )
	{
		m_strOsVersion += " Home Edition";
	}
	m_strOsVersion += osvi.szCSDVersion;
}

void cResourceChecker::CalcCPUBrand() 
{ 

	char strCPUBrand[0x40];
	// Get extended ids.
    int CPUInfo[4] = {-1};
    __cpuid(CPUInfo, 0x80000000);
    unsigned int nExIds = CPUInfo[0];

    // Get the information associated with each extended ID.
    strCPUBrand[0] = '\0';
    for( unsigned int i=0x80000000; i<=nExIds; ++i)
    {
        __cpuid(CPUInfo, i);

        // Interpret CPU brand string and cache information.
        if  (i == 0x80000002)
        {
            memcpy( strCPUBrand,
            CPUInfo,
            sizeof(CPUInfo));
        }
        else if( i == 0x80000003 )
        {
            memcpy( strCPUBrand + 16,
            CPUInfo,
            sizeof(CPUInfo));
        }
        else if( i == 0x80000004 )
        {
            memcpy(strCPUBrand + 32, CPUInfo, sizeof(CPUInfo));
        }
}
	m_strCPUBrand = strCPUBrand;
}

bool cResourceChecker::CheckHardDisk(const unsigned int diskSpaceNeeded) 
{ 
	// Check for enough free disk space on the current disk. 
	const int drive = _getdrive(); 
	struct _diskfree_t diskfree; 
	_getdiskfree(drive, &diskfree); 
	m_TotalHardDiskSpace = (unsigned int)((float)diskfree.total_clusters/MEGABYTE) * diskfree.sectors_per_cluster * diskfree.bytes_per_sector;
	m_AvailableHardDiskSpace = (unsigned int)((float)diskfree.avail_clusters/MEGABYTE) * diskfree.sectors_per_cluster * diskfree.bytes_per_sector;
	if (m_AvailableHardDiskSpace < diskSpaceNeeded) 
	{ 
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Not Enough HardDisk Space - Required : %ld, Available %ld \n", diskSpaceNeeded, m_AvailableHardDiskSpace));
		return false; 
	} 
	return true;
}

bool cResourceChecker::CheckMemory( const UINT physicalRAMNeeded, const UINT virtualRAMNeeded) 
{
	MEMORYSTATUSEX status; 
	status.dwLength = sizeof (status);

	GlobalMemoryStatusEx(&status); 

	m_TotalPhysicalMemory = (unsigned int)(status.ullTotalPhys/MEGABYTE);
	m_AvailablePhysicalMemory= (unsigned int)(status.ullAvailPhys/MEGABYTE);
	m_AvailableVirtualMemory = (unsigned int)(status.ullAvailVirtual/MEGABYTE);
	m_TotalVirtualMemory= (unsigned int)(status.ullTotalVirtual/MEGABYTE);

	if (m_AvailablePhysicalMemory < (physicalRAMNeeded)) 
	{ 
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Not Enough Physical Memory - Required : %ld, Available %ld \n", physicalRAMNeeded, m_AvailablePhysicalMemory));
		return false; 
	} 
	// Check for enough free memory. 
	if (status.ullAvailVirtual < virtualRAMNeeded) 
	{ 
		Log_Write_L1(ILogger::LT_ERROR, cString(100, "Not Enough Virtual Memory - Required : %ld, Available %ld \n", virtualRAMNeeded, m_AvailableVirtualMemory));
		// Tell the player to shut down the copy of Visual Studio running in the 
		// background, or whatever seems to be sucking the memory dry. 
		return false; 
	} 
	char * buff = DEBUG_NEW char[virtualRAMNeeded]; 
	if (buff) 
	{
		SAFE_DELETE_ARRAY(buff);
	}
	else 
	{ 
		Log_Write_L1(ILogger::LT_ERROR, "Not Enough Virtual Memory");
		// The system lied to you. When you attempted to grab a block as big 
		// as you need the system failed to do so. Something else is eating 
		// memory in the background; tell them to shut down all other apps 
		// and concentrate on your game. 
		return false; 
	} 
	return true;
}

#define SLEEPTIME 0 

static int s_milliseconds; 
static __int64 s_ticks; 
static int s_milliseconds0; 
static __int64 s_ticks0; 

// Call this function to start timing the CPU. It takes the CPU tick 
// count and the current time and stores it. Then, while you do other 
// things, and the OS task switches, the counters continue to count, and 
// when you call UpdateCPUTime, the measured speed is accurate. 
int cResourceChecker::StartTimingCPU() 
{ 
	// detect ability to get info 
	// 
	__asm 
	{ 
		pushfd ; push extended flags 
		pop eax ; store eflags into eax 
		mov ebx, eax ; save EBX for testing later 
		xor eax, (1<<21) ; switch bit 21 
		push eax ; push eflags 
		popfd ; pop them again 
		pushfd ; push extended flags 
		pop eax ; store eflags into eax 
		cmp eax, ebx ; see if bit 21 has changed 
		jz no_cpuid ; make sure it's now on
	} 
	// 
	// make ourselves high priority just for the time between 
	// when we measure the time and the CPU ticks 
	// 
	DWORD dwPriorityClass = GetPriorityClass(GetCurrentProcess());
	int dwThreadPriority = GetThreadPriority(GetCurrentThread()); 
	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS); 
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL); 
	//
	// start timing 
	// 
	s_milliseconds0 = (int)timeGetTime(); 
	__asm 
	{ 
		lea ecx, s_ticks0 ; get the offset 
		mov dword ptr [ecx], 0 ; zero the memory 
		mov dword ptr [ecx+4], 0 ; 
		rdtsc ; read time-stamp counter 
		mov [ecx], eax ; store the negative 
		mov [ecx+4], edx ; in the variable 
	} 
	// 
	// restore thread priority 
	// 
	SetThreadPriority(GetCurrentThread(), dwThreadPriority); SetPriorityClass(GetCurrentProcess(), dwPriorityClass); 
	return 0; 

no_cpuid: 
	return -1; 
}

//======================================================================== 
// UpdateCPUTime 
// 
// This function stops timing the CPU by adjusting the timers to account 
// for the amount of elapsed time and the number of CPU cycles taked 
// during the timing period. 
//======================================================================== 
void cResourceChecker::UpdateCPUTime() 
{ 
	// 
	// make ourselves high priority just for the time between 
	// when we measure the time and the CPU ticks 
	// 
	DWORD dwPriorityClass = GetPriorityClass(GetCurrentProcess()); 
	int dwThreadPriority = GetThreadPriority(GetCurrentThread());
	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS); SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL); 
	// 
	// get the times 
	// 
	s_milliseconds = -s_milliseconds0; 
	s_ticks = -s_ticks0; 
	s_milliseconds += (int)timeGetTime(); 
	__asm 
	{ 
		lea ecx, s_ticks ; get the offset 
		rdtsc ; read time-stamp counter 
		add [ecx], eax ; add the tick count 
		adc [ecx+4], edx ; 
	} 
	//
	// restore thread priority 
	// 
	SetThreadPriority(GetCurrentThread(), dwThreadPriority); SetPriorityClass(GetCurrentProcess(), dwPriorityClass); 
	return; 
}
//======================================================================== 
// CalcCPUSpeed 
// 
// This function takes the measured values and returns a speed that 
// represents a common possible CPU speed. 
//======================================================================== 
int cResourceChecker::CalcCPUSpeed() 
{ 
	// 
	// get the actual cpu speed in MHz, and 
	// then find the one in the CPU speed list 
	// that is closest 
	// 
	const struct tagCPUSPEEDS 
	{ 
		float fSpeed; 
		int iSpeed; 
	} 
	cpu_speeds[] = 
	{ 
		//
		// valid CPU speeds that are not integrally divisible by 
		// 16.67 MHz // 
		{ 60.00f, 60 }, 
		{ 75.00f, 75 }, 
		{ 90.00f, 90 }, 
		{ 120.00f, 120 }, 
		{ 180.00f, 180 }, 
	}; 
	// 
	// find the closest one 
	// 
	float fSpeed=((float)s_ticks)/((float)s_milliseconds*1000.0f); 
	int iSpeed=cpu_speeds[0].iSpeed; 
	float fDiff=(float)fabs(fSpeed-cpu_speeds[0].fSpeed); 
	for (int i=1 ; i<sizeof(cpu_speeds)/sizeof(cpu_speeds[0]) ; i++) 
	{ 
		float fTmpDiff = (float)fabs(fSpeed-cpu_speeds[i].fSpeed); 
		if (fTmpDiff < fDiff) 
		{ 
			iSpeed=cpu_speeds[i].iSpeed; fDiff=fTmpDiff; 
		} 
	} 
	// 
	// now, calculate the nearest multiple of fIncr 
	// speed 
	// 
	// 
	// now, if the closest one is not within one incr, calculate 
	// the nearest multiple of fIncr speed and see if that's 
	// closer 
	// 
	const float fIncr=16.66666666666666666666667f; 
	const int iIncr=4267; // fIncr << 8 
	//
	if (fDiff > fIncr) 
	{ 
		// 
		// get the number of fIncr quantums the speed is 
		// 
		int iQuantums = (int)((fSpeed / fIncr) + 0.5f); 
		float fQuantumSpeed = (float)iQuantums * fIncr; 
		float fTmpDiff = (float)fabs(fQuantumSpeed - fSpeed); 
		if (fTmpDiff < fDiff)
		{ 
			iSpeed = (iQuantums * iIncr) >> 8; fDiff=fTmpDiff; 
		} 
	} 
	return iSpeed; 
}
//======================================================================== 
// CheckCPUSpeedinMhz 
// 
// Gets the CPU speed by timing it for 1 second. 
//======================================================================== 
bool cResourceChecker::CheckCPUSpeedinMhz(const unsigned int uMinSpeedReq) 
{ 
	if(m_CPUSpeed !=0) 
	{ 
		//This will assure that the 0.5 second delay happens only once 
		return true; 
	} 
	if (StartTimingCPU()) 
		return true; 
	//This will lock the application for 1 second 
	do 
	{ 
		UpdateCPUTime(); 
		Sleep(SLEEPTIME); 
	} 
	while (s_milliseconds < 1000); 
	m_CPUSpeed = CalcCPUSpeed(); 
	if(m_CPUSpeed < uMinSpeedReq)
	{
		Log_Write_L1(ILogger::LT_ERROR, cString( 100, "CPU is too slow - Required speed: %ld, Actual Speed %ld \n", uMinSpeedReq, m_CPUSpeed));
		return false;
	}
	return true; 
}

void  cResourceChecker::Destroy()
{
	delete this;
}

void  cResourceChecker::CreateResourceChecker()
{
	s_pResourceChecker = DEBUG_NEW cResourceChecker();
}

IResourceChecker * IResourceChecker::TheResourceChecker()
{
	if(!s_pResourceChecker)
		cResourceChecker::CreateResourceChecker();
	return s_pResourceChecker;
}