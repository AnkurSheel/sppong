// *****************************************************************************
//  Vector2D   version:  1.0   Ankur Sheel  date: 2012/08/28
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef Vector2_h__
#define Vector2_h__

namespace Base
{
/********************************************//**
 * @brief Vector2 Struct.
 *
 ***********************************************/
class cVector2
	{
	public:
		cVector2();
		cVector2(const float fX, const float fY);
		
		/********************************************//**
		 * @return True if the vector is 0
		 *
		 * returns true if the vector is 0
		 ***********************************************/
		bool IsZero() const;	
		/********************************************//**
		 * @return Length of the vector
		 *
		 * Returns the length of the vector
		 ***********************************************/
		float Length() const;
		/********************************************//**
		 * @return Squared length of the vector 
		 *
		 * returns the squared length of the vector
		 ***********************************************/
		float LengthSquared() const;
		/********************************************//**
		 * 
		 *
		 * Converts the Vector into a unit vector
		 ***********************************************/
		void Normalize();
		/********************************************//**
		 * @param[in] inVec The vector with which the dot product needs to be calculated
		 * @return The dot product between this vector and the one passed as a parameter
		 *
		 * Calculates and returns the dot product
		 ***********************************************/
		float Dot(const cVector2 & inVec) const;
		/********************************************//**
		 * @return vector perpendicular to this one along the X axis.
		 *
		 * Returns the vector that is perpendicular to this one along the X axis.
		 ***********************************************/
		cVector2  PerpendicularAboutXAxis() const;
		/********************************************//**
		 * @return vector perpendicular to this one along the Y axis.
		 *
		 * Returns the vector that is perpendicular to this one along the Y axis.
		 ***********************************************/
		cVector2  PerpendicularAboutYAxis() const;
		/********************************************//**
		 * @param[in] dMax The maximum length of the vector
		 *
		 * Adjusts x and y so that the length of the vector does not exceed dMax
		 ***********************************************/
		void Truncate(const float fMax);
		/********************************************//**
		 * @param[in] inVec The vector with which the distance needs to be calculated
		 * @return Euclidean distance 
		 *
		 * returns the distance between this vector and the one passed as a parameter
		 ***********************************************/
		float Distance(const cVector2 & inVec) const;
		/********************************************//**
		  * @param[in] inVec The vector with which the distance needs to be calculated
		  * @return Squared euclidean distance 
		  *
		  * returns the squared distance between this vector and the one passed as a parameter
		 ***********************************************/
		float DistanceSquared(const cVector2 & inVec) const;
		/********************************************//**
		 * @param[in] const cVector2 & norm
		 * @return 
		 *
		 * Reflects the normalized vector it is operating upon.
		 ***********************************************/
		void Reflect(const cVector2 & norm);
		/********************************************//**
		 * @return Reverse of this vector
		 *
		 * returns the vector that is the reverse of this vector
		 ***********************************************/
		cVector2  GetReverse() const;
		/********************************************//**
		  *
		  * Sets the components to their absolute values
		 ***********************************************/
		void AbsTo();
		/********************************************//**
		  * @return The largest coordinate and return a signed, unit vector containing only the largest coordinate
		  *
		  * Get the largest coordinate and return a signed, unit vector
		  * containing only that coordinate
		 ***********************************************/
		cVector2 MajorAxis() const;
		/********************************************//**
		  *
		  * Changes the sign of the components
		 ***********************************************/
		void NegTo();

		const cVector2 & operator+=(const cVector2 & inVec);
		const cVector2 & operator-=(const cVector2 & inVec);
		const cVector2 & operator*=(const cVector2 & inVec);
		const cVector2 & operator*=(const float fVal);
		const cVector2 & operator/=(const float fVal);
		bool operator==(const cVector2 & inVec) const;
		bool operator!=(const cVector2 & inVec) const;
		float & operator[](const unsigned int i);
		const float operator[](const unsigned int i) const;

		static cVector2 Zero();
	public:
		float	x;	/*!< X component of Vector2 */
		float	y;	/*!< Y component of Vector2 */
	};

inline cVector2 operator*(const cVector2 & inVec1, const float fVal);
inline cVector2 operator*(const float fVal, const cVector2 & inVec1);
inline cVector2 operator/(const cVector2 & inVec1, const float fVal);
inline cVector2 operator-(const cVector2 & inVec1, const cVector2 & inVec2);
inline cVector2 operator+(const cVector2 & inVec1, const cVector2 & inVec2);
inline cVector2 operator*(const cVector2 & inVec1, const cVector2 & inVec2);

#include "Vector2.inl"
}
#endif // Vector2_h__