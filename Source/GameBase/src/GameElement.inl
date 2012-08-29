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
inline const Base::cVector3& cGameElement::GetPosition()
{
	return m_vPosition;
}
// ***************************************************************

inline void cGameElement::SetSprite(shared_ptr<Graphics::ISprite> const pSprite )
{
	m_pSprite = pSprite;
}

inline const shared_ptr<Graphics::ISprite> cGameElement::GetSprite() const
{
	return m_pSprite;
}

