// ***************************************************************
//  Structures   version:  1.0   Ankur Sheel  date: 2011/11/21
//  --------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Structures_h__
#define Structures_h__

namespace Base
{
	struct AppMsg
	{
		HWND			m_hWnd;
		UINT			m_uMsg;
		unsigned int	m_wParam;
		unsigned long	m_lParam;
	};
}

#endif // Structures_h__