
// ***************************************************************
// Returns the scaled height of the image
// ***************************************************************
inline UINT cSprite::GetScaledHeight() const
{
	return (UINT)(m_dwHeight * m_vScale.y);
}

// ***************************************************************
// Returns the scaled width of the image
// ***************************************************************
inline UINT cSprite::GetScaledWidth() const
{
	return (UINT)(m_dwWidth * m_vScale.x);
}

// ***************************************************************
// get the current position of the sprite
// ***************************************************************
inline D3DXVECTOR3 cSprite::GetPosition() const
{
	return m_vPosition;
}
// ***************************************************************

inline void Graphics::cSprite::SetTexture( ITexture * const pTexture )
{
	m_pTexture = pTexture;
}
// ***************************************************************
