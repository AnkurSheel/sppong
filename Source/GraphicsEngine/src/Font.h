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
		void Render(LPDIRECT3DDEVICE9 const pDevice) ;
		void SetText(const Base::cString & strString);
		void SetRect(const RECT & boundingRect);
		void SetFormat(const DWORD dwFormat);
		void SetTextColor(const D3DCOLOR & color);
		void OnLostDevice();
		void OnResetDevice();
		bool IsVisible();
		void Cleanup();
		void SetVisible(const bool bVisible);

	protected:
		ID3DXFont *		m_pFont ;
		D3DXFONT_DESC	m_fonttype; 
		Base::cString	m_strString;
		RECT			m_boundingRect; 
		DWORD 			m_dwFormat;
		D3DCOLOR		m_Color;
		bool			m_bVisible;
	} ;
}
#endif // Font_h__
