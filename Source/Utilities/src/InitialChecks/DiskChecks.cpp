#include <stdafx.h>
#include <direct.h>
#include <math.h>
#include <time.h>
#include <mmsystem.h>

bool IsOnlyInstance(LPCTSTR gameTitle) 
{ 
	// Find the window. If active, set and return false 
	// Only one game instance may have this mutex at a time... 
	HANDLE handle = CreateMutex(NULL, TRUE, gameTitle); 
	
	if (GetLastError() != ERROR_SUCCESS) 
	{ 
		HWND hWnd = FindWindow(gameTitle, NULL); 
		if (hWnd) 
		{ 
			// An instance of your game is already running. 
			ShowWindow(hWnd, SW_SHOWNORMAL); 
			SetFocus(hWnd); 
			SetForegroundWindow(hWnd); 
			SetActiveWindow(hWnd); 
			return false; 
		} 
	} 
	return true; 
}

bool CheckHardDisk(const DWORDLONG diskSpaceNeeded) 
{ 
	// Check for enough free disk space on the current disk. 
	int const drive = _getdrive(); 
	struct _diskfree_t diskfree; 
	_getdiskfree(drive, &diskfree); 
	unsigned __int64 const neededClusters = diskSpaceNeeded / ( diskfree.sectors_per_cluster * diskfree.bytes_per_sector ); 
	if (diskfree.avail_clusters < neededClusters) 
	{ 
		// if you get here you don't have enough disk space! 
		return false;
	}
	return true;
}

bool CheckMemory( const UINT physicalRAMNeeded, const UINT virtualRAMNeeded) 
{
	MEMORYSTATUSEX status; 
	GlobalMemoryStatusEx(&status); 
	if (status.ullTotalPhys < (physicalRAMNeeded)) 
	{ 
		// you don't have enough physical memory. Tell the player to go get a 
		// real computer and give this one to his mother. 
		return false; 
	} 
	// Check for enough free memory. 
	if (status.ullAvailVirtual < virtualRAMNeeded) 
	{ 
		// you don't have enough virtual memory available. 
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
int StartTimingCPU() 
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
void UpdateCPUTime() 
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
int CalcCPUSpeed() 
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
// GetCPUSpeed 
// 
// Gets the CPU speed by timing it for 1 second. 
//======================================================================== 
int GetCPUSpeed() 
{ 
	static int CPU_SPEED = 0; 
	if(CPU_SPEED!=0) 
	{ 
		//This will assure that the 0.5 second delay happens only once 
		return CPU_SPEED; 
	} 
	if (StartTimingCPU()) 
		return 0; 
	//This will lock the application for 1 second 
	do 
	{ 
		UpdateCPUTime(); 
		Sleep(SLEEPTIME); 
	} 
	while (s_milliseconds < 1000); 
	CPU_SPEED = CalcCPUSpeed(); 
	return CPU_SPEED; 
}
