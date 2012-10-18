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

namespace Base
{
	struct AppMsg;
}

namespace Graphics
{
	class IKeyboardHandler
	{
	public:
		virtual ~IKeyboardHandler(){}
		virtual bool VOnKeyDown(const Base::AppMsg & msg) = 0;
		virtual bool VOnKeyUp(const Base::AppMsg & msg) = 0;
	};
}

#endif // KeyboardHandler_h__