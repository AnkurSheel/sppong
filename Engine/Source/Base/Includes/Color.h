// *****************************************************************************
//  Color   version:  1.0   Ankur Sheel  date: 2012/09/03
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef Color_h__
#define Color_h__

#include "BaseDefines.h"

namespace Base
{
	///////////////////////////////////////////////////////////////////////////
	/// @brief RGBA Color class 
	///
	/// 
	///////////////////////////////////////////////////////////////////////////
	class cColor
	{
	public:
		///////////////////////////////////////////////////////////////////////
		/// Default Constructor which set RGBA to be 0
		///
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API cColor();
		///////////////////////////////////////////////////////////////////////
		/// Constructor which takes in RGBA components as int values. 
		/// Clamps the values to be between 0 and 255
		///
		/// @param[in] iRed Red component of color.
		/// @param[in] iGreen Green component of color.
		/// @param[in] iBlue Blue component of color.
		/// @param[in] iAlpha Alpha component of color.
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API explicit cColor(int iRed, int iGreen, int iBlue, int iAlpha);
		///////////////////////////////////////////////////////////////////////
		/// Constructor which takes in RGBA components as float values. 
		/// Clamps the values to be between 0.0f and 1.0f
		///
		/// @param[in] fRed Red component of color.
		/// @param[in] fGreen Green component of color.
		/// @param[in] fBlue Blue component of color.
		/// @param[in] fAlpha Alpha component of color.
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API explicit cColor(float fRed, float fGreen, float fBlue,
			float fAlpha);
		BASE_API ~cColor();
		///////////////////////////////////////////////////////////////////////
		/// Calculates the components of the color as floats in the range 0 to 1.0f
		///
		/// @param[out] fRed Red component of color.
		/// @param[out] fGreen Green component of color.
		/// @param[out] fBlue Blue component of color.
		/// @param[out] fAlpha Alpha component of color.
		///
		///////////////////////////////////////////////////////////////////////
		BASE_API void GetColorComponentsInFloat(float & fRed, float & fBlue, float & fGreen,
			float & fAlpha) const;
		
	public:
			BASE_API static const cColor BLACK;	///< Black Color.
			BASE_API static const cColor WHITE;	///< White Color.
			BASE_API static const cColor RED;	///< Red Color.
			BASE_API static const cColor BLUE;	///< Blue Color.
			BASE_API static const cColor GREEN;	///< Green Color.
			BASE_API static const cColor GRAY;	///< Gray Color.
			BASE_API static const cColor TURQUOISE;	///< Turquoise Color.
			BASE_API static const cColor YELLOW;	///< Yellow Color.
			BASE_API static const cColor TAN;	///< Tan Color.
			BASE_API static const cColor ORANGE;	///< Orange Color.
			BASE_API static const cColor VIOLET;	///< Violet Color.

	public:
		int		m_iRed;	///< Red component of the color.
		int		m_iGreen;	///< Green component of the color.
		int		m_iBlue;	///< Blue component of the color.
		int		m_iAlpha;	///< Alpha component of the color.
	};
}
#endif // Color_h__
