 // ***************************************************************
inline cColor::cColor()
: m_iRed(0)
, m_iGreen(0)
, m_iBlue(0)
, m_iAlpha(0)
, m_dwColor(0)
{
}

// ***************************************************************
inline cColor::cColor( const int iRed, const int iGreen, const int iBlue, const int iAlpha )
: m_iRed(iRed)
, m_iGreen(iGreen)
, m_iBlue(iBlue)
, m_iAlpha(iAlpha)
{
	CalculateColorFromComponents();
}

// ***************************************************************
inline void cColor::CalculateColorFromComponents()
{
	m_dwColor = ((((DWORD)(m_iAlpha)&0xff)<<24)|(((DWORD)(m_iRed)&0xff)<<16)|(((DWORD)(m_iGreen)&0xff)<<8)|((DWORD)(m_iBlue)&0xff));
}


// ***************************************************************
inline DWORD cColor::GetColor() const
{
	return m_dwColor;
}

