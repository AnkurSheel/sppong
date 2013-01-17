// ***************************************************************
//  ProcessManager   version:  1.0   Ankur Sheel  date: 2011/04/12
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef ProcessManager_h__
#define ProcessManager_h__

#include "ProcessManager.hxx"

namespace Utilities
{
	class cProcess;
}

namespace Utilities
{
	typedef std::list<shared_ptr<cProcess>> ProcessList;

	class cProcessManager
		: public IProcessManager
	{
	public:
		~cProcessManager();

		bool HasProcesses() const;
		void UpdateProcesses(const int iDeltaMilliSeconds);

	private:
		void VAttachProcess(shared_ptr<cProcess> pProcess);
		void VDetachProcess(shared_ptr<cProcess> pProcess);
		void VDetachProcesses(const unsigned long ulType);
		void VSetProcessesActive(const unsigned long ulType, const bool bActive);

	protected:
		ProcessList m_pProcessList;
	};
}
#endif // ProcessManager_h__