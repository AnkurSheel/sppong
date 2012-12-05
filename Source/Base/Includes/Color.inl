 // ***************************************************************
inline cColor::cColor()
: m_iRed(0)
, m_iGreen(0)
, m_iBlue(0)
, m_iAlpha(0)
, m_ulColor(0)
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

// *************************************************************************
inline cColor::cColor(const float fRed, const float fGreen, const float fBlue, const float fAlpha)
: m_iRed(static_cast<int>(fRed * 255))
, m_iGreen(static_cast<int>(fGreen * 255))
, m_iBlue(static_cast<int>(fBlue * 255))
, m_iAlpha(static_cast<int>(fAlpha * 255))
{
	CalculateColorFromComponents();
}

// ***************************************************************
inline void cColor::CalculateColorFromComponents()
{
	m_ulColor = ((((unsigned long)(m_iAlpha)&0xff)<<24)|(((unsigned long)(m_iRed)&0xff)<<16)|(((unsigned long)(m_iGreen)&0xff)<<8)|((unsigned long)(m_iBlue)&0xff));
}


// ***************************************************************
inline unsigned long cColor::GetColor() const
{
	return m_ulColor;
}

