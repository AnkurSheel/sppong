// ***************************************************************
// Returns the bounding Rectangle
// ***************************************************************
inline Graphics::cPolygon& cGameElement::GetBoundingRectangle()
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