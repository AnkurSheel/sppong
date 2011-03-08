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
	class IFont
	{
	public:
		virtual ~IFont(){}
		GRAPHIC_API virtual void InitFont(IDirect3DDevice9 *pd3dDevice, const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName) = 0;
		GRAPHIC_API virtual void DisplayText(IDirect3DDevice9 *pd3dDevice, const Base::cString &  strString, const LPRECT pRect, DWORD *pformat, D3DCOLOR Col) = 0;
		GRAPHIC_API static IFont * CreateMyFont();
	} ;
}
#endif // Font_h__
