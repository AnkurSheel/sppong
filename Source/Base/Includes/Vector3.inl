// ***************************************************************
inline cVector3::cVector3()
: m_dX(0)
, m_dY(0)
, m_dZ(0)
{
}

// ***************************************************************
inline cVector3::cVector3( const double dX, const double dY, const double dZ )
: m_dX(dX)
, m_dY(dY)
, m_dZ(dZ)
{
}

// ***************************************************************
inline Base::cVector3 cVector3::Zero()
{
	return cVector3(0.0f, 0.0f, 0.0f);
}

// ***************************************************************
inline bool cVector3::IsZero() const
{
	return (m_dX * m_dX + m_dY * m_dY + m_dZ * m_dZ) < MinDouble;
}

// ***************************************************************
inline double cVector3::Length() const
{
	return sqrt(m_dX * m_dX + m_dY * m_dY + m_dZ * m_dZ);
}

// ***************************************************************
inline double cVector3::LengthSquared() const
{
	return (m_dX * m_dX + m_dY * m_dY + m_dZ * m_dZ);
}

// ***************************************************************
inline void cVector3::Normalize()
{
	double dLength = Length();

	if (dLength > std::numeric_limits<double>::epsilon())
	{
		m_dX /= dLength;
		m_dY /= dLength;
		m_dZ /= dLength;
	}
}

// ***************************************************************
inline double cVector3::Dot( const cVector3 & inVec ) const
{
	return m_dX * inVec.m_dX + m_dY * inVec.m_dY + m_dZ * inVec.m_dZ;
}

// ***************************************************************
inline Base::cVector3 cVector3::Cross( const cVector3 & inVec) const
{
	return cVector3(m_dY * inVec.m_dZ - m_dZ * inVec.m_dY,
					m_dZ * inVec.m_dX - m_dX * inVec.m_dZ,
					m_dX * inVec.m_dY - m_dY * inVec.m_dX);
}

// ***************************************************************
inline double cVector3::Distance( const cVector3 & inVec ) const
{
	double xSeparation = inVec.m_dX - m_dX;
	double ySeparation = inVec.m_dY - m_dY;
	double zSeparation = inVec.m_dZ - m_dZ;

	return sqrt(xSeparation * xSeparation + ySeparation * ySeparation + zSeparation * zSeparation);
}

// ***************************************************************
inline double cVector3::DistanceSquared( const cVector3 & inVec ) const
{
	double xSeparation = inVec.m_dX - m_dX;
	double ySeparation = inVec.m_dY - m_dY;
	double zSeparation = inVec.m_dZ - m_dZ;

	return xSeparation * xSeparation + ySeparation * ySeparation + zSeparation * zSeparation;
}

// ***************************************************************
inline const cVector3 & cVector3::operator+=( const cVector3 & inVec )
{
	m_dX += inVec.m_dX;
	m_dY += inVec.m_dY;
	m_dZ += inVec.m_dZ;

	return *this;
}

// ***************************************************************
inline const cVector3 & cVector3::operator-=( const cVector3 & inVec )
{
	m_dX -= inVec.m_dX;
	m_dY -= inVec.m_dY;
	m_dZ -= inVec.m_dZ;
	return *this;
}

// ***************************************************************
inline const cVector3 & cVector3::operator*=( const double & dVal )
{
	m_dX *= dVal;
	m_dY *= dVal;
	m_dZ *= dVal;
	return *this;
}

// ***************************************************************
inline const cVector3 & cVector3::operator/=( const double & dVal )
{
	m_dX /= dVal;
	m_dY /= dVal;
	m_dZ /= dVal;
	return *this;
}

// ***************************************************************
inline bool cVector3::operator==( const cVector3 & inVec ) const
{
	return (isEqual(m_dX, inVec.m_dX) && isEqual(m_dY, inVec.m_dY) && isEqual(m_dZ, inVec.m_dZ));
}

// ***************************************************************
inline bool cVector3::operator!=( const cVector3 & inVec ) const
{
	return (!isEqual(m_dX, inVec.m_dX) || !isEqual(m_dY, inVec.m_dY) || !isEqual(m_dZ, inVec.m_dZ));
}

// ***************************************************************
Base::cVector3 operator*( const cVector3 & inVec1, const double dVal )
{
	cVector3 result(inVec1);
	result *= dVal;
	return result;
}

// ***************************************************************
Base::cVector3 operator*( const double dVal, const cVector3 & inVec1 )
{
	cVector3 result(inVec1);
	result *= dVal;
	return result;
}

// ***************************************************************
Base::cVector3 operator-( const cVector3 & inVec1, const cVector3 & inVec2 )
{
	cVector3 result(inVec1);
	result -= inVec2;
	return result;
}

// ***************************************************************
Base::cVector3 operator+( const cVector3 & inVec1, const cVector3 & inVec2 )
{
	cVector3 result(inVec1);
	result += inVec2;
	return result;
}

// ***************************************************************
Base::cVector3 operator/( const cVector3 & inVec1, const double dVal )
{
	cVector3 result(inVec1);
	result /= dVal;
	return result;
}
