// ***************************************************************
//  DxBase   version:  1.0   Ankur Sheel  date: 04/29/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef DxBase_h__
#define DxBase_h__

#include "DxBase.hxx" 

namespace Graphics
{
	class cDXBase
		: public IDXBase
	{
	private:
		cDXBase(const cDXBase&){}
		cDXBase operator =(const cDXBase&){}

		void DirectxInit() ;
		void CreateDirectxDevice() ;
		void SetParameters(const BOOL bFullScreen) ;

	public:
		cDXBase() ;
		~cDXBase() ;

		void Init(const HWND hWnd, const D3DCOLOR& bkColor) ;
		HRESULT ResetDevice() ;

		void Cleanup() ;
		HRESULT BeginRender();
		void EndRender(const HRESULT hr);
		LPDIRECT3DDEVICE9 GetDevice() const;
		UINT GetDisplayHeight() const;
		UINT GetDisplayWidth() const;
		HRESULT IsAvailable() const;
		void Destroy();
		static void CreateDXBase();

	private:
		LPDIRECT3D9				m_pD3D ;				// pointer to a direct3d object
		LPDIRECT3DDEVICE9		m_pd3dDevice ;			// pointer to a direct3d device
		D3DCAPS9				m_Caps ;				// the capabilities of the direct 3d object
		D3DCOLOR				m_BkColor ;				// the background color
		HWND					m_Hwnd ;				// the window handle
		D3DPRESENT_PARAMETERS	m_d3dpp ;				// the presentation parameters
		int						m_iWidth;				// the width of the window
		int						m_iHeight ;				// the height of the window
		D3DDISPLAYMODE			m_displayMode;			// the display mode

	};
#include "DxBase.inl"

	static cDXBase * s_pDXBase= NULL;
}
#endif // DxBase_h__
