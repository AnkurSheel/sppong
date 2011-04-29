
// ***************************************************************
// Returns the scaled height of the image
// ***************************************************************
inline UINT cSprite::GetScaledHeight() const
{
	return (UINT)(m_uiHeight * m_vScale.y);
}

// ***************************************************************
// Returns the scaled width of the image
// ***************************************************************
inline UINT cSprite::GetScaledWidth() const
{
	return (UINT)(m_uiWidth * m_vScale.x);
}

// ***************************************************************
// get the current position of the sprite
// ***************************************************************
inline D3DXVECTOR3 cSprite::GetPosition() const
{
	return m_vPosition;
}
// ***************************************************************

