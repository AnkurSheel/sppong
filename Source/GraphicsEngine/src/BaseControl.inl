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

//inline cBaseControl * Graphics::cBaseControl::GetParentControl()
//{
//	return m_pParentControl;
//}
// ***************************************************************

inline void cBaseControl::SetParentControl( cBaseControl * pParentControl )
{
	m_pParentControl = pParentControl;
}
// ***************************************************************

//inline shared_ptr<ISprite> cBaseControl::GetSprite() const
//{
//	return m_pCanvasSprite;
//}
// ***************************************************************

//inline void cBaseControl::SetSprite(shared_ptr<ISprite> pSprite )
//{
//	m_pCanvasSprite = pSprite;
//}
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

//inline int cBaseControl::GetNoOfChildren() const
//{
//	return m_iNoOfChildren;
//}
// ***************************************************************

inline void cBaseControl::SetPreviousSibling( cBaseControl * pControl )
{
	m_pPreviousSibling = pControl;
}
// ***************************************************************

inline float Graphics::cBaseControl::VGetHeight() const
{
	return m_fHeight;
}
// ***************************************************************

inline float Graphics::cBaseControl::VGetWidth() const
{
	return m_fWidth;
}
// ***************************************************************

//inline cBaseControl * Graphics::cBaseControl::GetFocusControl()
//{
//	return m_pFocusControl;
//}
// ***************************************************************

//inline bool Graphics::cBaseControl::GetVisible() const
//{
//	return m_bVisible;
//}
// ***************************************************************

inline void Graphics::cBaseControl::SetVisible( bool bIsVisible )
{
	m_bVisible = bIsVisible;
}
// ***************************************************************

//inline D3DXVECTOR3 Graphics::cBaseControl::VGetPosition() const
//{
//	return m_vPosition;
//}
// ***************************************************************

inline bool cBaseControl::AllowMovingControl()
{
	if (m_pParentControl)
	{
		return m_pParentControl->AllowMovingControl();
	}
	return m_bAllowMovingControls;
}