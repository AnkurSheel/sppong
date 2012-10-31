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

namespace Utilities
{
	class cProcess;
}
namespace Utilities
{
	typedef std::list<shared_ptr<cProcess>> ProcessList;

	class cProcessManager
	{
	public:
		~cProcessManager();

		void Attach(shared_ptr<cProcess> pProcess);
		bool HasProcesses() const;
		bool IsProcessActive(const int iType);
		void UpdateProcesses(const int iDeltaMilliSeconds);

	private:
		void Detach(shared_ptr<cProcess> pProcess);
	protected:
		ProcessList m_pProcessList;
	};
}
#endif // ProcessManager_h__