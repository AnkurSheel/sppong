// ***************************************************************
//  Input   version:  1.0   Ankur Sheel  date: 05/12/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "Input.h"

using namespace Graphics;
// ***************************************************************
// Constructor
// ***************************************************************
cInput::cInput()
: m_lPosX(0)
, m_lPosY(0)
{
}
// ***************************************************************

// ***************************************************************
// Destructor
// ***************************************************************
cInput::~cInput()
{
}
// ***************************************************************

// ***************************************************************
// Initializes the input devices
// ***************************************************************
void cInput::Init( const HINSTANCE hInst,
				  const HWND hWnd,
				  const UINT iTableWidth /*= 0 */,
				  const UINT iTableHeight/*= 0*/ )
{
	m_hWnd = hWnd;

	// create the DirectInput Interface
	DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pdInput, NULL);
	
	CreateKeyboard();
	CreateMouse();
	if (iTableHeight >0 && iTableWidth > 0)
	{
		m_iHeight = iTableHeight;
		m_iWidth = iTableWidth;
	}

}

bool cInput::CheckForJoyStick(HWND hWnd)
{
	JOYINFO joyinfo; 
	UINT wNumDevices; 
	BOOL bDevice1Attached, bDevice2Attached; 
	if((wNumDevices = joyGetNumDevs()) == 0)
	{
		return false; 
	}
	
	bDevice1Attached = joyGetPos(JOYSTICKID1,&joyinfo) != JOYERR_UNPLUGGED; 
	bDevice2Attached = joyGetPos(JOYSTICKID2,&joyinfo) != JOYERR_UNPLUGGED; 
	if(bDevice1Attached)
	{
		joySetCapture(hWnd, JOYSTICKID1, 1000/30, true); 
	}
	if (bDevice2Attached) 
	{
		joySetCapture(hWnd, JOYSTICKID2, 1000/30, true); 
	}
	return true; 
}
// ***************************************************************

// ***************************************************************
// Detects the keyboard presses
// ***************************************************************
void cInput::DetectKeys()
{
	m_pdInputKeyboard->Acquire();

	m_pdInputKeyboard->GetDeviceState(iNoOfKeys, (LPVOID)m_cKeyState);

	for (unsigned int iKey = 0; iKey < iNoOfKeys; iKey++)
	{
		if (m_cKeyState[iKey] & 0x80)
		{
			// key is pressed if it is not locked
			m_bPressedKeys[iKey] = !(m_bLockedKeys[iKey]);
		}
		else
		{
			m_bPressedKeys[iKey] = false;
			m_bLockedKeys[iKey] = false;
		}
	}

}
// ***************************************************************

// ***************************************************************
// Cleanup
// ***************************************************************
void cInput::Cleanup()
{
	m_pdInputKeyboard->Unacquire();
	m_pdInputKeyboard->Release();
	
	m_pdInputMouse->Unacquire();
	m_pdInputMouse->Release();

	m_pdInput->Release();
}
// ***************************************************************

// ***************************************************************
// Creates the keyboard device
// ***************************************************************
void cInput::CreateKeyboard()
{
	// create the keyboard device
	m_pdInput->CreateDevice(GUID_SysKeyboard,&m_pdInputKeyboard, NULL);

	// set the data format to keyboard format
	m_pdInputKeyboard->SetDataFormat(&c_dfDIKeyboard);

	// set the control over the keyboard
	m_pdInputKeyboard->SetCooperativeLevel(m_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	DetectKeys();
}
// ***************************************************************

// ***************************************************************
// Creates the mouse device
// ***************************************************************
void cInput::CreateMouse()
{
	// create the mouse device
	m_pdInput->CreateDevice(GUID_SysMouse,&m_pdInputMouse, NULL);

	// set the data format to mouse format
	m_pdInputMouse->SetDataFormat(&c_dfDIMouse);

	// set the control over the mouse
	m_pdInputMouse->SetCooperativeLevel(m_hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);

	// get the current position of the cursor
	POINT pt;
	GetCursorPos( &pt );
	ScreenToClient( m_hWnd, &pt );
	m_lPosX = pt.x;
	m_lPosY = pt.y;

	DetectMouseMovement();
}
// ***************************************************************

// ***************************************************************
// gets mouse movement
// ***************************************************************
void cInput::DetectMouseMovement()
{
	m_pdInputMouse->Acquire();
	
	m_pdInputMouse->GetDeviceState(sizeof(DIMOUSESTATE), LPVOID(&m_MouseState));

	m_lPosX += GetMouseXDelta();
	m_lPosY += GetMouseYDelta(); 

	ConstrainMouseCursor();

	// Get pressed keys
	for ( int i = 0; i < 4; i++ )
	{
		if ( m_MouseState.rgbButtons[i] & 0x80 )
		{
			m_bPressedButtons[i] = TRUE;

		}
		else
		{
			m_bPressedButtons[i] = FALSE;

		}

	} 
}
// ***************************************************************

// ***************************************************************
// constrains the mouse cursor to the window screen
// ***************************************************************
void cInput::ConstrainMouseCursor()
{
	if (m_lPosX < 0)
	{
		m_lPosX = 0;
	}
	else
	{
		if (m_lPosX > (int)m_iWidth - 16)
		{
			m_lPosX = m_iWidth - 16;
		}
	}

	if (m_lPosY < 0)
	{
		m_lPosY = 0;
	}
	else
	{
		if (m_lPosY > (int)m_iHeight - 16)
		{
			m_lPosY = m_iHeight - 16;
		}
	}
}
// ***************************************************************

IInput * IInput::CreateInputDevice()
{
	cInput* pInput= DEBUG_NEW cInput();
	return pInput;
}