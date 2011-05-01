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
	class IProcessManager
	{
	public:
		UTILITIES_API virtual ~IProcessManager() {}

		//UTILITIES_API virtual void Attach(std::tr1::shared_ptr<cProcess> pProcess);
		UTILITIES_API virtual bool HasProcesses() const = 0;
		UTILITIES_API virtual bool IsProcessActive(const int iType) = 0;
		UTILITIES_API virtual void UpdateProcesses(const int iDeltaMilliSeconds) = 0;

	};
}
#endif // ProcessManager_h__