// ***************************************************************
//  TextBoxControl   version:  1.0   Ankur Sheel  date: 2011/12/01
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef TextBoxControl_h__
#define TextBoxControl_h__

#include "BaseControl.h"

namespace Base
{
	class cString;
	struct AppMsg;
}

namespace Graphics
{
	class IMyFont;
	class ISentence;
	class ISprite;
}

namespace Utilities
{
	class ITimer;
}

namespace Graphics
{
	class cTextBoxControl
		: public cBaseControl
	{
	public:
		cTextBoxControl();
		void Init(const stTextBoxControlDef & def);
	
	private:
		~cTextBoxControl();
		void VRender(const ICamera * const pCamera);
		bool VOnKeyDown(const unsigned int iCharID);
		bool VOnCharPress(const unsigned int iCharID);
		void VSetAbsolutePosition();
		void VOnFocusChanged();
		void VCleanup();
		bool InsertText(const Base::cString & strText);
		void RemoveText(const long iQuantity);
		int	GetStringWidth();
		int	GetStringWidth(const Base::cString & strText);
		int	GetStringHeight();
		void SetText(const Base::cString & strText);
		bool SetCaratPosition(const long iPos);
		void SetCaratAbsolutePosition();

	private:
		ISentence *				m_pSentence;
		shared_ptr<ISprite>		m_pCaretSprite;
		float 					m_fCaretPos;
		float					m_fLastCaretUpdateTime;
		long					m_iCaretPos;
		bool					m_bTextBoxFull;
		float					m_fCaretUpdateTime;
		Utilities::ITimer *		m_pTimer;
		bool					m_bIsCaretVisible;
	};
}
#endif // TextBoxControl_h__s