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

#include "Input.hxx"

namespace Graphics
{
	const int iNoOfKeys = 256;

	class cInput
		: public IInput
	{
	public:
		cInput();
		~cInput();
		void Init(const HINSTANCE hInst, const HWND hWnd, const UINT iTableWidth = 0 , const UINT iTableHeight= 0);
		bool CheckForJoyStick(HWND hWnd);
		void DetectKeys();
		void DetectMouseMovement();
		const bool* const GetPressedKeys() const;
		const bool* const GetPressedButtons() const;
		long GetX() const;
		long GetY() const;
		long GetMouseXDelta() const;
		long GetMouseYDelta() const;
		long GetMouseZDelta() const;
		void LockKey(const DWORD dwKey);
		void Cleanup();
	
	private:
		cInput(const cInput&){}
		cInput operator = (const cInput&){}
		void CreateKeyboard();
		void CreateMouse();
		void ConstrainMouseCursor();
	private:
		LPDIRECTINPUT8			m_pdInput;				// the input object
		LPDIRECTINPUTDEVICE8	m_pdInputKeyboard;		// the keyboard device
		LPDIRECTINPUTDEVICE8	m_pdInputMouse;			// the mouse device
		BYTE					m_cKeyState[iNoOfKeys];		// stores the pressed keys on the keyboard
		bool					m_bPressedKeys[iNoOfKeys];	// array of pressed keys on the keyboard
		bool					m_bLockedKeys[iNoOfKeys];		// array of locked keys on the keyboard
		bool					m_bPressedButtons[4];	// stores the pressed buttons on the mouse
		HWND					m_hWnd;					// handle to the window
		DIMOUSESTATE			m_MouseState;			// stores the mouse state
		long					m_lPosX;
		long					m_lPosY;
		UINT					m_iHeight;
		UINT					m_iWidth;
	};

#include "Input.inl"
}
#endif // Input_h__
