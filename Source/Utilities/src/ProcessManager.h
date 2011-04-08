#pragma once
#include <list>

namespace Utilities
{
	class cProcess;
}
namespace Utilities
{
	typedef std::list<std::tr1::shared_ptr<cProcess>> ProcessList;

	class cProcessManager
	{
	public:
		~cProcessManager();

		void Attach(std::tr1::shared_ptr<cProcess> pProcess);
		bool HasProcesses() const;
		bool IsProcessActive(const int iType);
		void UpdateProcesses(const int iDeltaMilliSeconds);

	private:
		void Detach(std::tr1::shared_ptr<cProcess> pProcess);
	protected:
		ProcessList m_pProcessList;
	};
}