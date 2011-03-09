// ***************************************************************
//  Font   version:  1.0   Ankur Sheel  date: 05/16/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Font_h__
#define Font_h__

#include "Font.hxx"

namespace Base
{
	class cString;
}

namespace Base
{
	class cString;
}

namespace Graphics
{
	class cMyFont
		: public IFont
	{
	private:
		cMyFont(const cMyFont&){}
		cMyFont operator =(const cMyFont&){}

	public:
		cMyFont() ;
		~cMyFont() ;
		void InitFont(IDirect3DDevice9 *pd3dDevice, const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName) ;
		void DisplayText(IDirect3DDevice9 *pd3dDevice, const Base::cString &  strString, const LPRECT pRect, DWORD *pformat, D3DCOLOR Col) ;
	protected:
		ID3DXFont	*m_pFont ;
	} ;
}
#endif // Font_h__
