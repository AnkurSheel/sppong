// ***************************************************************
//  Color   version:  1.0   Ankur Sheel  date: 2012/09/03
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Color_cpp__
#define Color_cpp__

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
			static const cColor BLACK;
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