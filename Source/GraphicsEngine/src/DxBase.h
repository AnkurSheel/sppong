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
    /********************************************//**
     * @brief Class Declaration for \c IDXBase
     * interface
     ***********************************************/

	class cDXBase
		: public IDXBase
		, public Base::cNonCopyable
	{
	public:
		static IDXBase * Create();

	private:
		cDXBase() ;
		~cDXBase() ;
		// ***************************************************************
		void VInitialize(const HWND hWnd, const Base::cColor & bkColor,
			const bool bFullScreen, const bool bVsyncEnabled, const int iWidth,
			const int iHeight, const float fScreenDepth, const float fScreenNear);
		void VBeginRender();
		void VEndRender();
		ID3D11Device * VGetDevice() const;
		ID3D11DeviceContext * VGetDeviceContext() const;
		const D3DMATRIX & VGetWorldMatrix() const;
		const D3DMATRIX & VGetProjectionMatrix() const;
		// ***************************************************************
		bool SetupRenderTargets( const int iWidth, const int iHeight, const HWND hWnd, const bool bFullScreen );
		bool SetupSwapChain( const int iWidth, const int iHeight, const HWND hWnd,
			const bool bFullScreen );
		bool SetupDepthStencilState();
		bool SetupRasterStates();
		void SetupViewPort( const int iWidth, const int iHeight );
		/********************************************//**
		 * @param[in] iWidth The width of the window
		 * @param[in] iHeight The height of the window
		 *
		 * Gets the monitor refresh rate
		 ***********************************************/
		bool GetMonitorRefreshRate( const int iWidth, const int iHeight, 
			unsigned int & iRefreshRateNumerator, unsigned int & iRefreshRateDenominator);
		bool AttachBackBufferToSwapChain();
		bool CreateDepthStencilBuffer( const int iWidth, const int iHeight );
		bool CreateDepthStencilView();
		void SetupProjectionMatrix( const int iWidth, const int iHeight, const float fScreenNear, const float fScreenDepth );
		void Cleanup() ;

		void GetProjectionMatrix(D3DXMATRIX & matProjection);
		void GetWorldMatrix(D3DXMATRIX & matWorld);
		void GetOrthoMatrix(D3DXMATRIX & matOrtho );

	public:
		static IDXBase * s_pDXBase;

	private:
		bool						m_bVsyncEnabled;	/*!< Pointer to a direct3d object */
		IDXGISwapChain *			m_pSwapChain;
		ID3D11Device *				m_pDevice;
		ID3D11DeviceContext *		m_pDeviceContext;
		ID3D11RenderTargetView *	m_pRenderTargetView;
		ID3D11Texture2D *			m_pDepthStencilBuffer;
		ID3D11DepthStencilState *	m_pDepthStencilState;
		ID3D11DepthStencilView *	m_pDepthStencilView;
		ID3D11RasterizerState *		m_pRasterState;
		D3DXMATRIX					m_matProjection;
		D3DXMATRIX					m_matWorld;
		D3DXMATRIX					m_matOrtho;
		float						m_afBackGroundcolor[4];
	};
#include "DxBase.inl"
}
#endif // DxBase_h__
