// ***************************************************************
// Returns the bounding Rectangle
// ***************************************************************
inline Graphics::IPolygon& cGameElement::GetBoundingRectangle()
{
	return *m_pBoundingPolygon;
}
// ***************************************************************

// ***************************************************************
// returns the position of the element
// ***************************************************************
inline const D3DXVECTOR3& cGameElement::GetPosition()
{
	return m_vPosition;
}
// ***************************************************************

inline void cGameElement::SetSprite(Graphics::ISprite * const sprite )
{
	m_pSprite = sprite;
}

inline const Graphics::ISprite * cGameElement::GetSprite() const
{
	return m_pSprite;
}

