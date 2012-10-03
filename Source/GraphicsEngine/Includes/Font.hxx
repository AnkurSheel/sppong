// ***************************************************************
//  Font   version:  1.0   Ankur Sheel  date: 2011/02/16
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Font_hxx__
#define Font_hxx__

#include "GraphicEngineDefines.h"

namespace Base
{
	class cString;
}

namespace Graphics
{
	class IMyFont
	{
	public:
		virtual ~IMyFont(){}
		virtual void VInitialize(const Base::cString & strFontDescFilename) = 0;
		//virtual void InitFont(const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName) = 0;
		virtual void VSetText(const Base::cString & strText) = 0;
		//virtual void SetRect(const RECT & boundingRect) = 0;
		//virtual void CalculateAndSetRect() = 0;
		//virtual const RECT & GetRect() const = 0;
		//virtual const RECT GetRect(const Base::cString & strText) const = 0;
		//virtual void SetFormat(const DWORD dwFormat) = 0;
		//virtual void SetTextColor(const D3DCOLOR & color) = 0;
		GRAPHIC_API static shared_ptr<IMyFont> CreateMyFont();
	} ;
}
#endif // Font_h__
