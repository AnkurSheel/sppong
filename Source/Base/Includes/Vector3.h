// ***************************************************************
//  Vector3   version:  1.0   Ankur Sheel  date: 2012/08/28
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************#
#ifndef Vector3_h__
#define Vector3_h__

namespace Base
{
/********************************************//**
 * @brief Vector3 Struct.
 *
 ***********************************************/
class cVector3
	{
	public:
		cVector3();
		cVector3(const double dX, const double dY, const double dZ);
		
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
		double Length() const;
		/********************************************//**
		 * @return Squared length of the vector 
		 *
		 * returns the squared length of the vector
		 ***********************************************/
		double LengthSquared() const;
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
		double Dot(const cVector3 & inVec) const;
		/********************************************//**
		 * @param[in] inVec the vector with which the cross product needs to be calculated
		 * @return the cross product between these 2 vectors
		 *
		 * calculate and returns a vector perpendicular to these vectors
		 ***********************************************/
		cVector3 Cross( const cVector3 & inVec) const;
		/********************************************//**
		 * @param[in] dMax The maximum length of the vector
		 *
		 * Adjusts x and y so that the length of the vector does not exceed dMax
		 ***********************************************/
		void Truncate(const double dMax);
		/********************************************//**
		 * @param[in] inVec The vector with which the distance needs to be calculated
		 * @return Euclidean distance 
		 *
		 * returns the distance between this vector and the one passed as a parameter
		 ***********************************************/
		double Distance(const cVector3 & inVec) const;
		/********************************************//**
		  * @param[in] inVec The vector with which the distance needs to be calculated
		  * @return Squared euclidean distance 
		  *
		  * returns the squared distance between this vector and the one passed as a parameter
		 ***********************************************/
		double DistanceSquared(const cVector3 & inVec) const;

		const cVector3 & operator+=(const cVector3 & inVec);
		const cVector3 & operator-=(const cVector3 & inVec);
		const cVector3 & operator*=(const double & dVal);
		const cVector3 & operator/=(const double & dVal);
		bool operator==(const cVector3 & inVec) const;
		bool operator!=(const cVector3 & inVec) const;
		
		static cVector3 Zero();
	public:
		double	m_dX;	/*!< X component of Vector3 */
		double	m_dY;	/*!< Y component of Vector3 */
		double	m_dZ;	/*!< Z component of Vector3 */
	};

inline cVector3 operator*(const cVector3 & inVec1, const double dVal);
inline cVector3 operator*(const double dVal, const cVector3 & inVec1);
inline cVector3 operator-(const cVector3 & inVec1, const cVector3 & inVec2);
inline cVector3 operator+(const cVector3 & inVec1, const cVector3 & inVec2);
inline cVector3 operator/(const cVector3 & inVec1, const double dVal);

#include "Vector3.inl"
}
#endif // Vector3_h__
