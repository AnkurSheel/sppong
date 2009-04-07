
// ***************************************************************
// Returns the scaled height of the image
// ***************************************************************
inline UINT cSprite::GetScaledHeight()
{
	return (UINT)(m_uiHeight * m_vScale.y);
}

// ***************************************************************
// Returns the scaled width of the image
// ***************************************************************
inline UINT cSprite::GetScaledWidth()
{
	return (UINT)(m_uiWidth * m_vScale.x);
}