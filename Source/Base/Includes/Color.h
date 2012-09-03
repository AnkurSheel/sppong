// ***************************************************************
//  Color   version:  1.0   Ankur Sheel  date: 2012/09/03
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Color_h__
#define Color_h__

namespace Base
{
	class cColor
	{
	public:
		cColor();
		cColor(const float fRed, const float fGreen, const float fBlue, const float fAlpha);
		DWORD GetColor() const;
		
	private:
		void CalculateColorFromComponents();

	public:
			BASE_API static const cColor BLACK;
			BASE_API static const cColor WHITE;
			BASE_API static const cColor RED;
			BASE_API static const cColor BLUE;
			BASE_API static const cColor GREEN;
			BASE_API static const cColor GRAY;
			BASE_API static const cColor TURQUOISE;
			BASE_API static const cColor YELLOW;
			BASE_API static const cColor TAN;
			BASE_API static const cColor ORANGE;
			BASE_API static const cColor VIOLET;

	private:
		float m_fRed;
		float m_fGreen;
		float m_fBlue;
		float m_fAlpha;
		DWORD m_dwColor;
	};
#include "Color.inl"
}
#endif // Color_cpp__