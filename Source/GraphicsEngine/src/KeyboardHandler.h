// ***************************************************************
//  KeyboardHandler   version:  1.0   Ankur Sheel  date: 2011/05/11
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef KeyboardHandler_h__
#define KeyboardHandler_h__

#include "KeyboardHandler.hxx"

namespace Graphics
{
	class cKeyboardHandler
		: public IKeyboardHandler
	{
	public:
		cKeyboardHandler();
		~cKeyboardHandler();
		const bool* const GetPressedKeys() const;
		void LockKey(const DWORD dwKey);
		bool OnKeyDown(const BYTE c);
		bool OnKeyUp(const BYTE c);
	
	private:
		cKeyboardHandler(const cKeyboardHandler&){}
		cKeyboardHandler operator = (const cKeyboardHandler&){}
	private:
		BYTE					m_cKeyState[256];		// stores the pressed keys on the keyboard
		bool					m_bPressedKeys[256];	// array of pressed keys on the keyboard
		bool					m_bLockedKeys[256];		// array of locked keys on the keyboard
		HWND					m_hWnd;					// handle to the window
	};

#include "KeyboardHandler.inl"
}
#endif // KeyboardHandler_h__
