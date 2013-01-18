// ***************************************************************
//  ProcessManager   version:  1.0   Ankur Sheel  date: 2011/04/12
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef ProcessManager_hxx__
#define ProcessManager_hxx__

#include "UtilitiesDefines.h"

namespace Utilities
{
	class cProcess;
}
namespace Utilities
{
	class IProcessManager
	{
	public:
		UTILITIES_API virtual ~IProcessManager() {}

		UTILITIES_API virtual void VAttachProcess(shared_ptr<cProcess> pProcess) = 0;
		UTILITIES_API virtual void VDetachProcess(shared_ptr<cProcess> pProcess) = 0;
		UTILITIES_API virtual bool HasProcesses() const = 0;
		UTILITIES_API virtual void UpdateProcesses(const int iDeltaMilliSeconds) = 0;
		UTILITIES_API virtual void VDetachProcesses(const Base::cString & strType) = 0;
		UTILITIES_API virtual void VSetProcessesActive(const Base::cString & strType, const bool bActive) = 0;
		UTILITIES_API static IProcessManager * CreateProcessManager();
	};
}
#endif // ProcessManager_h__