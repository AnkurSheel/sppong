// ***************************************************************
//  KeyboardHandler   version:  1.0   Ankur Sheel  date: 2012/04/20
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef KeyboardHandler_hxx__
#define KeyboardHandler_hxx__
#include "GraphicEngineDefines.h"
namespace Graphics
{
	struct AppMsg;
}

namespace Graphics
{
	class IKeyBoardHandler
	{
	public:
		virtual ~IKeyBoardHandler(){}
		virtual bool VOnKeyDown(const AppMsg & msg) = 0;
		virtual bool VOnKeyUp(const AppMsg & msg) = 0;
		virtual void VLockKey(const BYTE c, const bool bLock) = 0;
	};
}

#endif // KeyboardHandler_hxx__