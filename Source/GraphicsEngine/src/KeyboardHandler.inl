// ***************************************************************
// returns the pressed keys
// ***************************************************************
inline const bool* const cKeyboardHandler::GetPressedKeys() const
{
	return m_bPressedKeys;
}
// ***************************************************************

// ***************************************************************
// locks a key on the keyboard so that it is read only once per
// key press
// ***************************************************************
inline void cKeyboardHandler::LockKey( const DWORD dwKey )
{
	m_bLockedKeys[dwKey] = true;
}
// ***************************************************************

inline bool cKeyboardHandler::OnKeyDown(const BYTE c)
{
	m_cKeyState[c] = true;
	m_bPressedKeys[c] = !(m_bLockedKeys[c]);
	return true;
}
// ***************************************************************

inline bool cKeyboardHandler::OnKeyUp(const BYTE c)
{
	m_cKeyState[c] = false;
	m_bPressedKeys[c] = false;
	return true;
}
// ***************************************************************

