// ***************************************************************
inline cVector2::cVector2()
: m_dX(0)
, m_dY(0)
{
}

// ***************************************************************
inline cVector2::cVector2( const double dX, const double dY )
: m_dX(dX)
, m_dY(dY)
{
}

// ***************************************************************
inline bool cVector2::IsZero() const
{
	return (m_dX * m_dX + m_dY * m_dY) < MinDouble;
}

// ***************************************************************
inline double cVector2::Length() const
{
	return sqrt(m_dX * m_dX + m_dY * m_dY);
}

// ***************************************************************
inline double cVector2::LengthSquared() const
{
	return (m_dX * m_dX + m_dY * m_dY);
}

// ***************************************************************
inline void cVector2::Normalize()
{
	double dLength = Length();

	if (dLength > std::numeric_limits<double>::epsilon())
	{
		m_dX /= dLength;
		m_dY /= dLength;
	}
}

// ***************************************************************
inline double cVector2::Dot( const cVector2 & inVec ) const
{
	return m_dX * inVec.m_dX + m_dY * inVec.m_dY;
}

// ***************************************************************
inline Base::cVector2 cVector2::Perpendicular() const
{
	return cVector2(-m_dY, m_dX);
}

// ***************************************************************
inline double cVector2::Distance( const cVector2 & inVec ) const
{
	double ySeparation = inVec.m_dY - m_dY;
	double xSeparation = inVec.m_dX - m_dX;

	return sqrt(ySeparation * ySeparation + xSeparation * xSeparation);
}

// ***************************************************************
inline double cVector2::SquareDistance( const cVector2 & inVec ) const
{
	double ySeparation = inVec.m_dY - m_dY;
	double xSeparation = inVec.m_dX - m_dX;

	return (ySeparation * ySeparation + xSeparation * xSeparation);
}

// ***************************************************************
inline void cVector2::Reflect( const cVector2 & norm )
{
	*this += 2.0 * this->Dot(norm) * norm.GetReverse();
}

// ***************************************************************
inline Base::cVector2 cVector2::GetReverse() const
{
	return cVector2(-m_dX, -m_dY);
}

// ***************************************************************
inline const cVector2 & cVector2::operator+=( const cVector2 & inVec )
{
	m_dX += inVec.m_dX;
	m_dY += inVec.m_dY;

	return *this;
}

// ***************************************************************
inline const cVector2 & cVector2::operator-=( const cVector2 & inVec )
{
	m_dX -= inVec.m_dX;
	m_dY -= inVec.m_dY;

	return *this;
}

// ***************************************************************
inline const cVector2 & cVector2::operator*=( const double & dVal )
{
	m_dX *= dVal;
	m_dY *= dVal;

	return *this;
}

// ***************************************************************
inline const cVector2 & cVector2::operator/=( const double & dVal )
{
	m_dX /= dVal;
	m_dY /= dVal;

	return *this;
}

// ***************************************************************
inline bool cVector2::operator==( const cVector2 & inVec ) const
{
	return (isEqual(m_dX, inVec.m_dX) && isEqual(m_dY,inVec.m_dY) );
}

// ***************************************************************
inline bool cVector2::operator!=( const cVector2 & inVec ) const
{
	return (!isEqual(m_dX, inVec.m_dX) || !isEqual(m_dY,inVec.m_dY) );
}

// ***************************************************************
Base::cVector2 operator*( const cVector2 & inVec1, const double dVal )
{
	cVector2 result(inVec1);
	result *= dVal;
	return result;
}

// ***************************************************************
Base::cVector2 operator*( const double dVal, const cVector2 & inVec1 )
{
	cVector2 result(inVec1);
	result *= dVal;
	return result;
}

// ***************************************************************
Base::cVector2 operator-( const cVector2 & inVec1, const cVector2 & inVec2 )
{
	cVector2 result(inVec1);
	result -= inVec2;
	return result;
}

// ***************************************************************
Base::cVector2 operator+( const cVector2 & inVec1, const cVector2 & inVec2 )
{
	cVector2 result(inVec1);
	result += inVec2;
	return result;
}

// ***************************************************************
Base::cVector2 operator/( const cVector2 & inVec1, const double dVal )
{
	cVector2 result(inVec1);
	result /= dVal;
	return result;
}
