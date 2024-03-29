// *****************************************************************************
//  ProcessManager   version:  1.0   Ankur Sheel  date: 2013/01/15
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "ProcessManager.h"
#include "Process.h"

using namespace Utilities;
using namespace Base;

// *****************************************************************************
cProcessManager::~cProcessManager()
{	
	m_pProcessList.clear();
}

// *****************************************************************************
void cProcessManager::VAttachProcess(shared_ptr<cProcess> pProcess)
{
	m_pProcessList.push_back(pProcess);
	pProcess->SetAttached(true);
}

// *****************************************************************************
bool cProcessManager::HasProcesses() const
{
	return !(m_pProcessList.empty());
}

// *****************************************************************************
void cProcessManager::UpdateProcesses(const int iDeltaMilliSeconds)
{
	shared_ptr<cProcess> pNext;

	ProcessList::const_iterator curProcess = m_pProcessList.begin();

	while(curProcess != m_pProcessList.end())
	{
		shared_ptr<cProcess> p(*curProcess);
		curProcess++;

		if(p->IsDead())
		{
			pNext = p->GetNext();
			if(pNext)
			{
				p->SetNext(shared_ptr<cProcess>((cProcess*)NULL));
				VAttachProcess(pNext);
			}
			VDetachProcess(p);
		}
		else if(p->IsActive() && !p->VIsPaused())
		{
			p->VUpdate(iDeltaMilliSeconds);
		}
	}
}

// *****************************************************************************
void cProcessManager::VDetachProcess(shared_ptr<cProcess> pProcess)
{
	m_pProcessList.remove(pProcess);
	pProcess->SetAttached(false);
}

// *****************************************************************************
void cProcessManager::VDetachProcesses(const cString & strType)
{
	ProcessList::iterator curProcess;
	unsigned long hash = cHashedString::CalculateHash(strType);
	for (curProcess = m_pProcessList.begin(); curProcess != m_pProcessList.end(); curProcess++)
	{
		shared_ptr<cProcess> p(*curProcess);
		if(p->m_strType.GetHash() == hash)
		{
			p->VKill();
		}
	}
}

// *****************************************************************************
void cProcessManager::VSetProcessesActive(const cString & strType,
										  const bool bActive)
{
	ProcessList::iterator curProcess;
	unsigned long hash = cHashedString::CalculateHash(strType);
	for (curProcess = m_pProcessList.begin(); curProcess != m_pProcessList.end(); curProcess++)
	{
		shared_ptr<cProcess> p(*curProcess);
		if(p->m_strType.GetHash() == hash)
		{
			p->VSetActive(bActive);
		}
	}
}

// *****************************************************************************
void cProcessManager::VGetProcesses(const cString & strType, ProcessList & pProcessList)
{
	ProcessList::iterator curProcess;
	unsigned long hash = cHashedString::CalculateHash(strType);
	for (curProcess = m_pProcessList.begin(); curProcess != m_pProcessList.end(); curProcess++)
	{
		shared_ptr<cProcess> p(*curProcess);
		if(p->m_strType.GetHash() == hash)
		{
			pProcessList.push_back(p);
		}
	}
	
}

// *****************************************************************************
IProcessManager * IProcessManager::CreateProcessManager()
{
	return DEBUG_NEW cProcessManager();
}