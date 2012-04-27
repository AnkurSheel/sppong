// ***************************************************************
//  WindowControl   version:  1.0   Ankur Sheel  date: 2011/11/21
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef WindowControl_h__
#define WindowControl_h__

#include "BaseControl.h"

namespace Graphics
{
	class cWindowControl
		: public cBaseControl
	{
	public:
		cWindowControl(WINDOWTYPE wType, bool bAllowMovingControls);
		void LoadCanvasFromFile(const Base::cString & strFileName);

	private:
		~cWindowControl();

		void VOnRender(const AppMsg & msg);
		bool VOnLeftMouseButtonUp(const int X, const int Y);
		bool VOnLeftMouseButtonDown(const int X, const int Y);
		bool VOnMouseMove(const int X, const int Y);
		void VSetAbsolutePosition();
		void Minimize(const int iWidth, const int iHeight, const int iX, const int iY);
		void Restore();

	private:
		int					m_iLastNormalPosX;
		int					m_iLastNormalPosY;
		int					m_iLastNormalWidth;
		int					m_iLastNormalHeight;
		bool				m_bIsMinimized;
		WINDOWTYPE			m_eWindowType;
	};
}

#endif // WindowControl_h__