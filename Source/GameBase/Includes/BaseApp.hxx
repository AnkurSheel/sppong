// ***************************************************************
//  BaseApp   version:  1.0   Ankur Sheel  date: 04/30/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef BaseApp_hxx__
#define BaseApp_hxx__

#include "GameBaseDefines.h"

namespace Base
{
	class cString;
}

namespace Graphics
{
	struct AppMsg;
}
namespace GameBase
{
	class IBaseApp
		: public Base::cNonCopyable
	{
	public:
		virtual ~IBaseApp(){}
		virtual HWND OnInit(const HINSTANCE hInstance, const int nCmdShow, const bool bFullScreen, const int iFullScreenWidth, const int iFullScreenHeight) = 0;
		virtual Base::cString GetGameTitle() const = 0; 
		virtual  void OnMsgProc(const Graphics::AppMsg & msg) = 0;
		virtual void Run() = 0;
		virtual HRESULT OnResetDevice() = 0;
		virtual void OnLostDevice() = 0;
	};
}
#endif // BaseApp_hxx__