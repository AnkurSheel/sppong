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
	struct CharDescriptor
	{
		unsigned short id;
		unsigned short x, y;
		unsigned short Width, Height;
		unsigned short XOffset, YOffset;
		unsigned short XAdvance;

		CharDescriptor() : id(0), x( 0 ), y( 0 ), Width( 0 ), Height( 0 ),
			XOffset( 0 ), YOffset( 0 ),	XAdvance( 0 )
		{ }
	};

	class cMyFont
		: public IMyFont
		, public Base::cNonCopyable
	{
	public:
		cMyFont() ;
		~cMyFont() ;
	
	private:
		void VInitialize(const Base::cString & strFontDescFilename);
		void ParseFontDesc();
		//void InitFont(const int iHeight, const UINT iWidth, const UINT iWeight, const BOOL bItalic, const BYTE charset, const Base::cString & strFaceName) ;
		//void VOnRender(const Graphics::AppMsg & msg) ;
		void VSetText(const Base::cString & strText);
		//const RECT & GetRect() const;
		//const RECT GetRect(const Base::cString & strText) const;
		//void SetRect(const RECT & boundingRect);
		//void CalculateAndSetRect();
		//void AddTrailingSpaceWidth(const Base::cString & strText , RECT & boundingRect) const;
		//void SetFormat(const DWORD dwFormat);
		//void SetTextColor(const D3DCOLOR & color);
		//void VOnLostDevice();
		//HRESULT VOnResetDevice();
		//void VSetVisible(bool bIsVisible);
		//bool VIsVisible() const;
		void Cleanup();

	private:
		//ID3DXFont *		m_pFont ;
		//D3DXFONT_DESC	m_fonttype; 
		//Base::cString	m_strString;
		//RECT			m_boundingRect; 
		//DWORD 			m_dwFormat;
		//DWORD			m_Color;
		//bool			m_bVisible;
		//int				m_iSpaceWidth;
		typedef std::map<int, const CharDescriptor> CharDescriptorMap;

		Base::cString		m_strFontDescFilename;
		Base::cString		m_strFontTexFilename;
		int					m_iTextureWidth;
		int					m_iTextureHeight;
		CharDescriptorMap	m_CharDescriptorMap;
		Base::cString		m_strText;
	};
}
#endif // Font_h__
