// ***************************************************************
// returns the mouse movement in X direction
// ***************************************************************
inline const long cInput::GetMouseXDelta()
{
	return m_MouseState.lX;
}
// ***************************************************************

// ***************************************************************
// returns the mouse movement in Y direction
// ***************************************************************
inline const long cInput::GetMouseYDelta()
{
	return m_MouseState.lY;
}
// ***************************************************************

// ***************************************************************
// returns the mouse movement in Z direction
// ***************************************************************
inline const long cInput::GetMouseZDelta()
{
	return m_MouseState.lZ;
}
// ***************************************************************

// ***************************************************************
// returns the pressed keys
// ***************************************************************
inline const bool* const cInput::GetPressedKeys()
{
	return m_bPressedKeys;
}
// ***************************************************************

// ***************************************************************
// returns the pressed mouse buttons
// ***************************************************************
inline const bool* const cInput::GetPressedButtons()
{
	return m_bPressedButtons;
}
// ***************************************************************

// ***************************************************************
// returns the pressed mouse buttons
// ***************************************************************
inline long cInput::GetX()
{
	return m_lPosX;
}
// ***************************************************************

// ***************************************************************
// returns the pressed mouse buttons
// ***************************************************************
inline long cInput::GetY()
{
	return m_lPosY;
}
// ***************************************************************