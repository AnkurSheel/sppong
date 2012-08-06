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
#include "BaseEntity.h"

namespace GameBase
{
	class cBaseApp 
		: public IBaseApp
		, public cBaseEntity
	{
	public:
		GAMEBASE_API cBaseApp(const Base::cString strName);
		virtual ~cBaseApp(){}
	protected:
		GAMEBASE_API virtual void VOnInitialization(const HINSTANCE hInstance, const int nCmdShow,const bool bFullScreen, const int iFullScreenWidth, const int iFullScreenHeight, HWND & outHwnd);
	};
}

#endif // BaseApp_h__