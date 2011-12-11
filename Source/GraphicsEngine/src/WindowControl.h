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
		cWindowControl(WINDOWTYPE wType);
		~cWindowControl();

		void OnMouseUp(const int iButton, const int X, const int Y);
		void OnMouseDown(const int iButton, const int X, const int Y);
		void OnMouseMove(const int X, const int Y);
		void OnKeyDown(const AppMsg & msg ){}
		void OnKeyUp(const AppMsg & msg ){}
		void OnRender(const AppMsg & msg);
		void LoadCanvasFromFile(const Base::cString & strFileName);
	
	private :
		cWindowControl(const cWindowControl&){}
		cWindowControl operator =(const cWindowControl&){}

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