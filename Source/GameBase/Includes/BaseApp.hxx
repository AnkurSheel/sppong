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

namespace Utilities
{
	class IParamLoader;
}

namespace GameBase
{
	class IBaseApp
	{
	public:
		virtual ~IBaseApp(){}
		virtual void VOnInitialization(const HINSTANCE hInstance, const int nCmdShow, const Base::cString & strOptionsFileName) = 0;
		virtual Base::cString VGetGameTitle() const = 0; 
		virtual bool VOnMsgProc(const Graphics::AppMsg & msg) = 0;
		virtual void VRun() = 0;
		virtual HRESULT VOnResetDevice() = 0;
		virtual void VOnLostDevice() = 0;
		static Utilities::IParamLoader * VGetParamLoader();
	};
}
#endif // BaseApp_hxx__