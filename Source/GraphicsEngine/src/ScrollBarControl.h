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
		static cScrollBarControl* Create();
		void Init(const Base::cString & strBackgroundImage, const Base::cString & strDefaultThumbImage, const Base::cString & strPressedThumbImage, const Base::cString & strDefaultTopRightImage, const Base::cString & strPressedTopRightImage,	const Base::cString & strDefaultLeftBottomImage, const Base::cString & strPressedLeftBottomImage, const int iLeftTopPos, const int iRightBottomPos);

	private:
		cScrollBarControl();
		~cScrollBarControl();
		bool VPostMsg(const AppMsg & msg);
		void VOnRender(const AppMsg & msg);
		void VOnLostDevice();
		HRESULT VOnResetDevice();
		bool VOnMouseMove(const int X, const int Y);
		void VSetAbsolutePosition();
		void VSetSize(const float fNewWidth, const float fNewHeight);
		void SetLeftTopPosition(const int iLeftTopPos);
		void SetRightBottomPosition(const int iRightBottomPos);
		void AutoSize();
		void SetThumbPosition(const int iNewPosition);
		void IncrementArrowPressed(bool bPressed);
		void DecrementArrowPressed(bool bPressed);
		void ThumbPressed(bool bPressed);
		void Cleanup();

	private:
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