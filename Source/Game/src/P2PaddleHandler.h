// ***************************************************************
//  P2PaddleHandler   version:  1.0   Ankur Sheel  date: 2012/04/21
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef P2PaddleHandler_h__
#define P2PaddleHandler_h__

#include "KeyboardHandler.hxx"
namespace Graphics
{
	struct AppMsg;
}

class P2PaddleHandler 
	: public Graphics::IKeyBoardHandler
{
public:
	P2PaddleHandler();
	~P2PaddleHandler();
	bool VOnKeyDown(const Graphics::AppMsg & msg);
	bool VOnKeyUp(const Graphics::AppMsg& msg);
	void VLockKey(const BYTE c, const bool bLock);
	void OnUpdate();
	void RegisterCallBack(function <void (bool)> callback);;
	void UnregisterCallBack();
private:
	BYTE					m_bKey[KEYBOARD_KEYS];			// Which keys are up and down
	function<void (bool)>	m_pfnCallBack;
};

#endif // P2PaddleHandler_h__