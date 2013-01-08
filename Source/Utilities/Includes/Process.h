// *****************************************************************************
//  Process   version:  1.0   Ankur Sheel  date: 2013/01/08
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef Process_h__
#define Process_h__

#include "UtilitiesDefines.h"

namespace Utilities
{
	static const int PROCESS_FLAG_ATTACHED		= 0x00000001;

	class cProcess
		: public Base::cNonCopyable
	{
	public:
		UTILITIES_API cProcess();
		UTILITIES_API virtual ~cProcess();
		
		UTILITIES_API bool IsDead() const;
		bool IsActive() const;
		void SetActive(const bool bActive);
		bool IsAttached() const;
		void SetAttached(const bool bAttached);
		bool IsPaused() const;
		bool IsInitialized() const;
		shared_ptr<cProcess> const GetNext() const;
		void SetNext(shared_ptr<cProcess> pNext);
		void TogglePause();
		
		virtual void VInitialize(){}
		UTILITIES_API virtual void VUpdate(const int iDeltaMilliSeconds);
		UTILITIES_API virtual void VKill();
		
	protected:
		bool					m_bKill;
		bool					m_bActive;
		bool					m_bPaused;
		bool					m_bInitialUpdate;
		shared_ptr<cProcess>	m_pNext;
	
	private:
		unsigned int			m_uProcessFlags;

	private:
		friend class cProcessManager;
	};
}
#endif // Process_h__