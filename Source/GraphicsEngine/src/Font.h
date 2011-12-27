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
	public:
		cMyFont() ;
		~cMyFont() ;
		void InitFont(IDirect3DDevice9 *pd3dDevice, const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName) ;
		void OnRender(LPDIRECT3DDEVICE9 const pDevice) ;
		void SetText(const Base::cString & strString);
		const RECT & GetRect() const;
		const RECT GetRect(const Base::cString & strText) const;
		void SetRect(const RECT & boundingRect);
		void CalculateAndSetRect();
		void AddTrailingSpaceWidth(const Base::cString & strText , RECT & boundingRect) const;
		void SetFormat(const DWORD dwFormat);
		void SetTextColor(const D3DCOLOR & color);
		void OnLostDevice();
		void OnResetDevice();
		bool IsVisible();
		void Cleanup();
		void SetVisible(const bool bVisible);

	private:
		ID3DXFont *		m_pFont ;
		D3DXFONT_DESC	m_fonttype; 
		Base::cString	m_strString;
		RECT			m_boundingRect; 
		DWORD 			m_dwFormat;
		D3DCOLOR		m_Color;
		bool			m_bVisible;
		int				m_iSpaceWidth;
	} ;
#include "Font.inl"
}
#endif // Font_h__
