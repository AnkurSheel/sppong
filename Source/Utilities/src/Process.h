#pragma once

#include <memory>

namespace Utilities
{
	static const int PROCESS_FLAG_ATTACHED		= 0x00000001;

	class cProcess
	{
	public:
		cProcess(int iType, unsigned int uOrder = 0);
		virtual ~cProcess();
		
		bool IsDead() const;
		int GetType() const;
		void SetType(const int iType);
		bool IsActive() const;
		bool SetActive(const bool bActive);
		bool IsAttached() const;
		void SetAttached(const bool bAttached);
		bool IsPaused() const;
		bool IsInitialized() const;
		std::tr1::shared_ptr<cProcess> const GetNext() const;
		void SetNext(std::tr1::shared_ptr<cProcess> pNext);
		void TogglePause();
		
		virtual void OnInitialize(){}
		virtual void OnUpdate(const int iDeltaMilliSeconds);
		virtual void onKill();
		

	private:
		cProcess(const cProcess &){}
		const cProcess& operator= (const cProcess &){}
	
	protected:
		int								m_iType;
		bool							m_bKill;
		bool							m_bActive;
		bool							m_bPaused;
		bool							m_bInitialUpdate;
		std::tr1::shared_ptr<cProcess>	m_pNext;
	
	private:
		unsigned int					m_uProcessFlags;

	private:
		friend class cProcessManager;
	};
	#include "Process.inl"

}