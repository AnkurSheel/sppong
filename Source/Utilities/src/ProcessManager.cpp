// ***************************************************************
//  ProcessManager   version:  1.0   Ankur Sheel  date: 2011/04/12
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "ProcessManager.h"
#include "Process.h"

using namespace Utilities;

cProcessManager::~cProcessManager()
{	
	ProcessList::const_iterator curProcess = m_pProcessList.begin();

	while(curProcess != m_pProcessList.end())
	{
		shared_ptr<cProcess> p(*curProcess);
		curProcess++;
		Detach(p);
	}
}

void cProcessManager::VAttachProcess(shared_ptr<cProcess> pProcess)
{
	m_pProcessList.push_back(pProcess);
	pProcess->SetAttached(true);
}

bool cProcessManager::HasProcesses() const
{
	return !(m_pProcessList.empty());
}

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
			Detach(p);
		}
		else if(p->IsActive() && !p->IsPaused())
		{
			p->VUpdate(iDeltaMilliSeconds);
		}
	}
}

void cProcessManager::Detach(shared_ptr<cProcess> pProcess)
{
	m_pProcessList.remove(pProcess);
	pProcess->SetAttached(false);
}

IProcessManager * IProcessManager::CreateProcessManager()
{
	return DEBUG_NEW cProcessManager();
}