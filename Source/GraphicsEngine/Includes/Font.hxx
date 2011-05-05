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
#include "ScreenElement.hxx"

namespace Base
{
	class cString;
}

namespace Graphics
{
	class IFont
		: public IScreenElement
	{
	public:
		virtual ~IFont(){}
		GRAPHIC_API virtual void InitFont(IDirect3DDevice9 *pd3dDevice, const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName) = 0;
		GRAPHIC_API virtual void SetText(const Base::cString & strString) = 0;
		GRAPHIC_API virtual void SetRect(const RECT & boundingRect) = 0;
		GRAPHIC_API virtual void SetFormat(const DWORD dwFormat) = 0;
		GRAPHIC_API virtual void SetTextColor(const D3DCOLOR & color) = 0;
		GRAPHIC_API static IFont * CreateMyFont();
	} ;
}
#endif // Font_h__
