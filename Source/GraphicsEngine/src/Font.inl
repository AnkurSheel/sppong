inline void cMyFont::SetText(const Base::cString & strString)
{
	m_strString = strString;
}
// ***************************************************************

inline const RECT & Graphics::cMyFont::GetRect() const
{
	return m_boundingRect;
}
// ***************************************************************

inline void cMyFont::SetRect(const RECT & boundingRect)
{
	m_boundingRect = boundingRect;
}
// ***************************************************************

inline void cMyFont::SetFormat(const DWORD dwFormat)
{
	m_dwFormat = dwFormat;
}
// ***************************************************************

inline void cMyFont::SetTextColor(const D3DCOLOR & color)
{
	m_Color = color;
}
// ***************************************************************

inline bool cMyFont::IsVisible()
{
	return m_bVisible;
}
// ***************************************************************

inline void cMyFont::SetVisible(const bool bVisible)
{
	m_bVisible = bVisible;
}
// ***************************************************************

