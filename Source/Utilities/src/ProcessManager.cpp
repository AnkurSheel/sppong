#include "stdafx.h"
#include "ProcessManager.h"
#include "Process.h"

using namespace Utilities;
using namespace std::tr1;

cProcessManager::~cProcessManager()
{	
	for(ProcessList::iterator i = m_pProcessList.begin(); i != m_pProcessList.end(); i++)
	{
		Detach(*(i));
	}
}

void cProcessManager::Attach(std::tr1::shared_ptr<cProcess> pProcess)
{
	m_pProcessList.push_back(pProcess);
	pProcess->SetAttached(true);
}

bool cProcessManager::HasProcesses() const
{
	return !(m_pProcessList.empty());
}

bool cProcessManager::IsProcessActive(const int iType) 
{
	for(ProcessList::iterator i = m_pProcessList.begin(); i != m_pProcessList.end(); i++)
	{
		if((*i)->GetType() == iType 
			&& ((*i)->IsDead() == false || ( *i )->GetNext()))
		{
			return true;
		}
	}
	return false;
}

void cProcessManager::UpdateProcesses(const int iDeltaMilliSeconds)
{
	shared_ptr<cProcess> pNext;

	ProcessList::iterator curProcess = m_pProcessList.begin();

	for(curProcess; curProcess != m_pProcessList.end(); curProcess++)
	{
		shared_ptr<cProcess> p(*curProcess);
		if(p->IsDead())
		{
			pNext = p->GetNext();
			if(pNext)
			{
				p->SetNext(shared_ptr<cProcess>((cProcess*)NULL));
				Attach(pNext);
			}
			Detach(p);
		}
		else if(p->IsActive() && !p->IsPaused())
		{
			p->OnUpdate(iDeltaMilliSeconds);
		}
	}
}

void cProcessManager::Detach(std::tr1::shared_ptr<cProcess> pProcess)
{
	m_pProcessList.remove(pProcess);
	pProcess->SetAttached(false);
}