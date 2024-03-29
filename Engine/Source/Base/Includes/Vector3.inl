// *******************************************************************************************
inline cVector3::cVector3()
: x(0)
, y(0)
, z(0)
{
}

// *******************************************************************************************
inline cVector3::cVector3( const float fX, const float fY, const float fZ )
: x(fX)
, y(fY)
, z(fZ)
{
}

// *******************************************************************************************
inline Base::cVector3 cVector3::Zero()
{
	return cVector3(0.0f, 0.0f, 0.0f);
}

// *******************************************************************************************
inline bool cVector3::IsZero() const
{
	return LengthSquared() < EpsilonFloat;
}

// *******************************************************************************************
inline float cVector3::Length() const
{
	return sqrt(LengthSquared());
}

// *******************************************************************************************
inline float cVector3::LengthSquared() const
{
	return (x * x + y * y + z * z);
}

// *******************************************************************************************
inline void cVector3::Normalize()
{
	float dLength = Length();

	if (dLength > EpsilonFloat)
	{
		x /= dLength;
		y /= dLength;
		z /= dLength;
	}
}

// *******************************************************************************************
inline float cVector3::Dot( const cVector3 & inVec ) const
{
	return x * inVec.x + y * inVec.y + z * inVec.z;
}

// *******************************************************************************************
inline Base::cVector3 cVector3::Cross( const cVector3 & inVec) const
{
	return cVector3(y * inVec.z - z * inVec.y,
					z * inVec.x - x * inVec.z,
					x * inVec.y - y * inVec.x);
}

// *******************************************************************************************
inline float cVector3::Distance( const cVector3 & inVec ) const
{
	return sqrt(DistanceSquared(inVec));
}

// *******************************************************************************************
inline float cVector3::DistanceSquared( const cVector3 & inVec ) const
{
	float xSeparation = inVec.x - x;
	float ySeparation = inVec.y - y;
	float zSeparation = inVec.z - z;

	return xSeparation * xSeparation + ySeparation * ySeparation + zSeparation * zSeparation;
}

// *******************************************************************************************
inline void cVector3::AbsTo() 
{
	x = abs(x);
	y = abs(y);
	z = abs(z);
}

// *******************************************************************************************
inline cVector3 cVector3::MajorAxis() const
{
	float absX = abs(x);
	float absY = abs(y);
	float absZ = abs(z);
	
	if(absX > absY)
	{
		if(absX > absZ)
		{
			float signX = static_cast<float>(Sign(x));
			return cVector3(signX, 0, 0);
		}
		else
		{
			float signZ = static_cast<float>(Sign(z));
			return cVector3(0,0,signZ);
		}
	}
	else
	{
		if(absY > absZ)
		{
			float signY = static_cast<float>(Sign(y));
			return cVector3(0, signY, 0);
		}
		else
		{
				float signZ = static_cast<float>(Sign(z));
				return cVector3(0, 0, signZ);
		}
	}
}

// *******************************************************************************************
inline cVector3 cVector3::MinorAxis() const
{
	float absX = abs(x);
	float absY = abs(y);
	float absZ = abs(z);
	
	if(absX < absY)
	{
		if(absX < absZ)
		{
			float signX = static_cast<float>(Sign(x));
			return cVector3(signX, 0, 0);
		}
		else
		{
			float signZ = static_cast<float>(Sign(z));
			return cVector3(0,0,signZ);
		}
	}
	else
	{
		if(absY < absZ)
		{
			float signY = static_cast<float>(Sign(y));
			return cVector3(0, signY, 0);
		}
		else
		{
				float signZ = static_cast<float>(Sign(z));
				return cVector3(0, 0, signZ);
		}
	}
}

// *******************************************************************************************
inline void cVector3::NegTo() 
{
	x = -x;
	y = -y;
	z = -z;
}

// *******************************************************************************************
inline const cVector3 & cVector3::operator+=( const cVector3 & inVec )
{
	x += inVec.x;
	y += inVec.y;
	z += inVec.z;

	return *this;
}

// *******************************************************************************************
inline const cVector3 & cVector3::operator-=( const cVector3 & inVec )
{
	x -= inVec.x;
	y -= inVec.y;
	z -= inVec.z;
	return *this;
}

// *****************************************************************************
inline const cVector3 & cVector3::operator*=(const cVector3 & inVec)
{
	x *= inVec.x;
	y *= inVec.y;
	z *= inVec.z;

	return *this;
}

// *******************************************************************************************
inline const cVector3 & cVector3::operator*=( const float & fVal )
{
	x *= fVal;
	y *= fVal;
	z *= fVal;
	return *this;
}

// *******************************************************************************************
inline const cVector3 & cVector3::operator/=( const float & fVal )
{
	x /= fVal;
	y /= fVal;
	z /= fVal;
	return *this;
}

// *******************************************************************************************
inline bool cVector3::operator==( const cVector3 & inVec ) const
{
	return (isEqual(x, inVec.x) && isEqual(y, inVec.y) && isEqual(z, inVec.z));
}

// *******************************************************************************************
inline bool cVector3::operator!=( const cVector3 & inVec ) const
{
	return (!isEqual(x, inVec.x) || !isEqual(y, inVec.y) || !isEqual(z, inVec.z));
}

// *****************************************************************************
inline float & cVector3::operator[](const unsigned int i)
{
	return *((&x) + i);
}

// *****************************************************************************
inline const float cVector3::operator[]( const unsigned int i) const
{
	return *((&x) + i);
}

// *******************************************************************************************
Base::cVector3 operator*( const cVector3 & inVec1, const float fVal )
{
	cVector3 result(inVec1);
	result *= fVal;
	return result;
}

// *******************************************************************************************
Base::cVector3 operator*( const float fVal, const cVector3 & inVec1 )
{
	cVector3 result(inVec1);
	result *= fVal;
	return result;
}

// *******************************************************************************************
Base::cVector3 operator/( const cVector3 & inVec1, const float fVal )
{
	cVector3 result(inVec1);
	result /= fVal;
	return result;
}

// *******************************************************************************************
Base::cVector3 operator-( const cVector3 & inVec1, const cVector3 & inVec2 )
{
	cVector3 result(inVec1);
	result -= inVec2;
	return result;
}

// *******************************************************************************************
Base::cVector3 operator+( const cVector3 & inVec1, const cVector3 & inVec2 )
{
	cVector3 result(inVec1);
	result += inVec2;
	return result;
}

// *******************************************************************************************
Base::cVector3 operator*(const cVector3 & inVec1, const cVector3 & inVec2)
{
	cVector3 result(inVec1);
	result *= inVec2;
	return result;
}
