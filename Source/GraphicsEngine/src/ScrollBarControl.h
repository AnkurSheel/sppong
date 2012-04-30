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
		void Init(const Base::cString & strBackgroundImage, const Base::cString & strDefaultThumbImage, const Base::cString & strPressedThumbImage, const Base::cString & strDefaultTopRightImage, const Base::cString & strPressedTopRightImage, const Base::cString & strDefaultLeftBottomImage, const Base::cString & strPressedLeftBottomImage, const int iMinPos, const int iMaxPos);

	protected:
		cScrollBarControl();
		virtual ~cScrollBarControl();

	private:
		bool VOnLeftMouseButtonUp(const int X, const int Y);
		bool VOnLeftMouseButtonDown(const int X, const int Y);
		void VOnRender(const AppMsg & msg);
		void VOnLostDevice();
		HRESULT VOnResetDevice();
		virtual void VSetThumbPosition(const int iNewPosition);
		void IncrementArrowPressed(bool bPressed);
		void DecrementArrowPressed(bool bPressed);
		void ThumbPressed(bool bPressed);
		void Cleanup();

	protected:
		int						m_iMinPos;
		int						m_iMaxPos;
		int						m_iThumbPos;
		int						m_iNoOfIncrements;
		float					m_fRange;
		bool					m_bDragMode;
		IBaseControl*			m_pBtnThumb;
		IBaseControl*			m_pBtnDecrementArrow;
		IBaseControl*			m_pBtnIncrementArrow;
		function<void (bool)>	m_callbackIncrementArrowPressed;
		function<void (bool)>	m_callbackDecrementArrowPressed;
		function<void (bool)>	m_callbackThumbPressed;

	};
}

#endif // ScrollBarControl_h__