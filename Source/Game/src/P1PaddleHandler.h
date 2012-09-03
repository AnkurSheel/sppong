// ***************************************************************
//  P1PaddleHandler   version:  1.0   Ankur Sheel  date: 2012/04/20
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef P1PaddleHandler_h__
#define P1PaddleHandler_h__

#include "KeyboardHandler.hxx"
namespace Graphics
{
	struct AppMsg;
}

class P1PaddleHandler 
	: public Graphics::IKeyBoardHandler
{
public:
	P1PaddleHandler();
	~P1PaddleHandler();
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
#endif // P1PaddleHandler_h__