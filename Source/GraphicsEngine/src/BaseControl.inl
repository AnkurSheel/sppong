inline cBaseControl * cBaseControl::GetFirstChild() const
{
	return m_pChildControls;
}
// ***************************************************************

inline cBaseControl * cBaseControl::GetNextSibling() const
{
	return m_pNextSibling;
}
// ***************************************************************

inline cBaseControl * Graphics::cBaseControl::GetParentControl()
{
	return m_pParentControl;
}
// ***************************************************************

inline void cBaseControl::SetParentControl( cBaseControl * pParentControl )
{
	m_pParentControl = pParentControl;
}
// ***************************************************************

inline ISprite * cBaseControl::GetSprite() const
{
	return m_pCanvasSprite;
}
// ***************************************************************

inline void cBaseControl::SetSprite( ISprite * pSprite )
{
	m_pCanvasSprite = pSprite;
}
// ***************************************************************

inline void cBaseControl::SetNextSibling( cBaseControl * pControl )
{
	m_pNextSibling = pControl;
}
// ***************************************************************

inline cBaseControl * cBaseControl::GetPreviousSibling() const
{
	return m_pPreviousSibling;
}
// ***************************************************************

inline int cBaseControl::GetNoOfChildren() const
{
	return m_iNoOfChildren;
}
// ***************************************************************

inline void cBaseControl::SetPreviousSibling( cBaseControl * pControl )
{
	m_pPreviousSibling = pControl;
}
// ***************************************************************

inline DWORD Graphics::cBaseControl::GetHeight() const
{
	return m_dwHeight;
}
// ***************************************************************

inline DWORD Graphics::cBaseControl::GetWidth() const
{
	return m_dwWidth;
}
// ***************************************************************

inline cBaseControl * Graphics::cBaseControl::GetFocusControl()
{
	return m_pFocusControl;
}
// ***************************************************************

inline bool Graphics::cBaseControl::GetVisible() const
{
	return m_bVisible;
}
// ***************************************************************

inline void Graphics::cBaseControl::SetVisible( bool bIsVisible )
{
	m_bVisible = bIsVisible;
}
// ***************************************************************

inline D3DXVECTOR3 Graphics::cBaseControl::GetPosition() const
{
	return m_vPosition;
}
// ***************************************************************

inline void Graphics::cBaseControl::SetPosition( const D3DXVECTOR3 & vPosition )
{
	m_vPosition = vPosition;
}
// ***************************************************************