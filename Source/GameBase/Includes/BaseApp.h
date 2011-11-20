// ***************************************************************
//  BaseApp   version:  1.0   Ankur Sheel  date: 2011/10/19
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef BaseApp_h__
#define BaseApp_h__

#include "BaseApp.hxx"

namespace GameBase
{
	class cBaseApp : public IBaseApp
	{
	public:
		virtual ~cBaseApp(){}
	protected:
		GAMEBASE_API virtual void OnInit(const HINSTANCE hInstance, const int nCmdShow,const bool bFullScreen, HWND & outHwnd);
	};
}

#endif // BaseApp_h__