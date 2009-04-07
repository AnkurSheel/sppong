// ***************************************************************
//  Input   version:  1.0   Ankur Sheel  date: 05/12/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Input_h__
#define Input_h__

class cInput
{
private:
	LPDIRECTINPUT8			m_pdInput;				// the input object
	LPDIRECTINPUTDEVICE8	m_pdInputKeyboard;		// the keyboard device
	LPDIRECTINPUTDEVICE8	m_pdInputMouse;			// the mouse device
	BYTE					m_cKeyState[256];		// stores the pressed keys on the keyboard
	bool					m_bPressedKeys[256];	// array of pressed keys on the keyboard
	bool					m_bLockedKeys[256];		// array of locked keys on the keyboard
	bool					m_bPressedButtons[4];	// stores the pressed buttons on the mouse
	HWND					m_hWnd;					// handle to the window
	DIMOUSESTATE			m_MouseState;			// stores the mouse state
	long					m_lPosX;
	long					m_lPosY;
	UINT					m_iTableHeight;
	UINT					m_iTableWidth;
	cInput(const cInput&){}
	cInput operator = (const cInput&){}
	void CreateKeyboard();
	void CreateMouse();
	void ConstrainMouseCursor();
public:
	cInput();
	~cInput();
	void Init(const HINSTANCE hInst, const HWND hWnd, const UINT iTableWidth = 0 , const UINT iTableHeight= 0);
	void DetectKeys();
	void DetectMouseMovement();
	const bool* const GetPressedKeys();
	const bool* const GetPressedButtons();
	long GetX();
	long GetY();
	const long GetMouseXDelta();
	const long GetMouseYDelta();
	const long GetMouseZDelta();
	void LockKey(const DWORD dwKey);
	void Cleanup();
};

#include "Input.inl"

#endif // Input_h__