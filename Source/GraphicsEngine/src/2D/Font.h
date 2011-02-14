// ***************************************************************
//  Font   version:  1.0   Ankur Sheel  date: 05/16/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "Font.hxx"

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
		void InitFont(IDirect3DDevice9 *pd3dDevice, const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const char * const szFaceName) ;
		void DisplayText(IDirect3DDevice9 *pd3dDevice, const char * const  szString, const LPRECT pRect, DWORD *pformat, D3DCOLOR Col) ;
	protected:
		ID3DXFont	*m_pFont ;
	} ;
}
