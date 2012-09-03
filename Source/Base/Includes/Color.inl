 // ***************************************************************
inline cColor::cColor()
: m_fRed(0)
, m_fGreen(0)
, m_fBlue(0)
, m_fAlpha(0)
, m_dwColor(0)
{
}

// ***************************************************************
inline cColor::cColor( const float fRed, const float fGreen, const float fBlue, const float fAlpha )
: m_fRed(fRed)
, m_fGreen(fGreen)
, m_fBlue(fBlue)
, m_fAlpha(fAlpha)
{
	CalculateColorFromComponents();
}

// ***************************************************************
inline void cColor::CalculateColorFromComponents()
{
	m_dwColor = ((((DWORD)(m_fAlpha)&0xff)<<24)|(((DWORD)(m_fRed)&0xff)<<16)|(((DWORD)(m_fGreen)&0xff)<<8)|((DWORD)(m_fBlue)&0xff));
}


// ***************************************************************
inline DWORD cColor::GetColor() const
{
	return m_dwColor;
}

