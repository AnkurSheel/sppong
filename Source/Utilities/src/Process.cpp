#include "stdafx.h"
#include "Process.h"

using namespace Utilities;

cProcess::cProcess(int iType, unsigned int uOrder)
: m_iType(iType)
, m_bKill(false)
, m_bActive(true)
, m_uProcessFlags(0)
, m_bPaused(false)
, m_bInitialUpdate(true)
{
}

cProcess::~cProcess()
{
}
		
void cProcess::SetAttached(const bool bAttached)
{
	if(bAttached)
	{
		m_uProcessFlags |= PROCESS_FLAG_ATTACHED;
	}
	else
	{
		m_uProcessFlags &= ~PROCESS_FLAG_ATTACHED;
	}
}

void cProcess::OnUpdate(const int iDeltaMilliSeconds)
{
	if ( m_bInitialUpdate ) 
	{ 
		OnInitialize(); 
		m_bInitialUpdate = false; 
	}
}

void cProcess::onKill()
{
	m_bKill = true;
}
