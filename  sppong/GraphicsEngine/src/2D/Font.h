// ***************************************************************
//  font   version:  1.0   Ankur Sheel  date: 05/16/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef font_h__
#define font_h__

#include "GraphicEngineDefines.h"

class cMyFont
{
protected:
	ID3DXFont	*m_pFont ;
public:
	GRAPHIC_API cMyFont() ;
	GRAPHIC_API ~cMyFont() ;
	GRAPHIC_API void InitFont(IDirect3DDevice9 *pd3dDevice, const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const char * const szFaceName) ;
	GRAPHIC_API void DisplayText(IDirect3DDevice9 *pd3dDevice, const char * const  szString, const LPRECT pRect, DWORD *pformat, D3DCOLOR Col) ;
} ;

#endif // font_h__
