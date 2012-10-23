// ***************************************************************
//  ScrollBarControl   version:  1.0   Ankur Sheel  date: 2012/04/24
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef ScrollBarControl_h__
#define ScrollBarControl_h__

#include "BaseControl.h"

namespace Graphics
{
	class cScrollBarControl
		: public cBaseControl
	{
	public:
		void Init(const stScrollBarControlDef & def);

	protected:
		cScrollBarControl();
		virtual ~cScrollBarControl();

	private:
		bool VOnLeftMouseButtonUp(const int X, const int Y);
		bool VOnLeftMouseButtonDown(const int X, const int Y);
		void VRender(const ICamera * const pCamera);
		void VCleanup();
		virtual void VSetThumbPosition(const int iNewPosition) = 0;
		void IncrementArrowPressed(bool bPressed);
		void DecrementArrowPressed(bool bPressed);
		void ThumbPressed(bool bPressed);

	protected:
		int						m_iMinPos;
		int						m_iMaxPos;
		int						m_iThumbPos;
		int						m_iNoOfIncrements;
		float					m_fRange;
		bool					m_bDragMode;
		IBaseControl *			m_pBtnThumb;
		IBaseControl *			m_pBtnDecrementArrow;
		IBaseControl *			m_pBtnIncrementArrow;
		function<void (bool)>	m_callbackIncrementArrowPressed;
		function<void (bool)>	m_callbackDecrementArrowPressed;
		function<void (bool)>	m_callbackThumbPressed;
	};
}

#endif // ScrollBarControl_h__