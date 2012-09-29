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
		/********************************************//**
 		 * @return An Object of this class
		 *
		 * Creates an object of this class and returns it
		 ***********************************************/
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
		void VTurnZBufferOn();
		void VTurnZBufferOff();
		ID3D11Device * VGetDevice() const;
		ID3D11DeviceContext * VGetDeviceContext() const;
		const D3DMATRIX & VGetWorldMatrix() const;
		const D3DMATRIX & VGetProjectionMatrix() const;
		const D3DMATRIX & VGetOrthoMatrix() const;
		int VGetScreenWidth() const;
		int VGetScreenHeight() const;
		/********************************************//**
		 * @param[in] iWidth The width of the window
		 * @param[in] iHeight The height of the window
		 * @param[in] hWnd A handle to the current window
		 * @param[in] bFullScreen True if the application is full screen. False if Windowed
		 * @return False if there was an error
		 *
		 * Sets up the device, swap chain, depth buffer, depth stencil state. 
		 * Bind the render target view and the depth stencil buffer to the output render pipeline.
		 ***********************************************/
		bool SetupRenderTargets( const int iWidth, const int iHeight, const HWND hWnd, const bool bFullScreen );
		/********************************************//**
		 * @param[in] iWidth The width of the window
		 * @param[in] iHeight The height of the window
		 * @param[in] hWnd A handle to the current window
		 * @param[in] bFullScreen True if the application is full screen. False if Windowed
		 * @return False if there was an error
		 *
		 * Fills out the swap chain description and creates the device and swap chain
		 ***********************************************/
		bool SetupSwapChain( const int iWidth, const int iHeight, const HWND hWnd,
			const bool bFullScreen );
		/********************************************//**
		 * @return False if there was an error
		 *
		 * Creates and sets the depth stencil state.
		 ***********************************************/
		bool SetupDepthStencilStateFor3D();
		/********************************************//**
		 * @return False if there was an error
		 *
		 * Creates and sets the depth stencil state for 2D drawing.
		 ***********************************************/
		bool SetupDepthStencilStateFor2D();
		/********************************************//**
		 * @return False if there was an error
		 *
		 *  Creates a rasterizer state
		 ***********************************************/
		bool SetupRasterStates();
		/********************************************//**
		 * @param[in] iWidth The width of the window
		 * @param[in] iHeight The height of the window
		 *
		 * Sets up the viewport so that Direct3D can map clip space coordinates to the 
		 * render target space
		 ***********************************************/
		void SetupViewPort( const int iWidth, const int iHeight );
		/********************************************//**
		 * @param[in] iWidth The width of the window
		 * @param[in] iHeight The height of the window
		 * @param[out] iRefreshRateNumerator The Numerator for the refresh rate
		 * @param[out] iRefreshRateDenominator The Denomninator for the refresh rate
		 * @return False if there was an error
		 *
		 * Gets the monitor refresh rate
		 ***********************************************/
		bool GetMonitorRefreshRate( const int iWidth, const int iHeight, 
			unsigned int & iRefreshRateNumerator, unsigned int & iRefreshRateDenominator);
		/********************************************//**
		 * @return False if there was an error
		 *
		 * Gets a pointer to the back buffer and attaches it to the swap chain.
		 ***********************************************/
		bool AttachBackBufferToSwapChain();
		/********************************************//**
		 * @param[in] iWidth The width of the window
		 * @param[in] iHeight The height of the window
		 * @return False if there was an error
		 *
		 * Creates a Depth Buffer.
		 ***********************************************/
		bool CreateDepthStencilBuffer( const int iWidth, const int iHeight );
		/********************************************//**
		 * @return False if there was an error
		 *
		 * Sets the view of the depth stencil buffer so that Direct3D knows to use the depth buffer 
		 * as a depth stencil texture
		 ***********************************************/
		bool CreateDepthStencilView();
		/********************************************//**
		 * @param[in] iWidth Width of the window
		 * @param[in] iHeight Height of the window
		 * @param[in] fScreenDepth Far Depth setting for the 3D environment
		 * @param[in] fScreenNear Near Depth setting for the 3D environment
		 *
		 * Creates the projection matrix to translate the 3D scene into the 2D viewport space.
		 ***********************************************/
		void SetupProjectionMatrix( const int iWidth, const int iHeight, const float fScreenNear, const float fScreenDepth );
		/********************************************//**
		 *
		 * Releases all the pointers
		 ***********************************************/
		void Cleanup() ;

	public:
		static IDXBase * s_pDXBase;							/*!< static object of this class */

	private:
		bool						m_bVsyncEnabled;			/*!< True if we want Direct3D to render according to the users monitor refresh rate. False if want it to go as fast as possible. */
		IDXGISwapChain *			m_pSwapChain;				/*!< The swap chain is the front and back buffer to which the graphics will be drawn. */
		ID3D11Device *				m_pDevice;					/*!< Pointer to the directX device to create resources */
		ID3D11DeviceContext *		m_pDeviceContext;			/*!< Pointer to a directX device context which generates rendering commands*/
		ID3D11RenderTargetView *	m_pRenderTargetView;		/*!< The back buffer to be used as the render target */
		ID3D11Texture2D *			m_pDepthStencilBuffer;		/*!< Depth Buffer used to render polygons in 3D space */
		ID3D11DepthStencilState *	m_p3DDepthStencilState;		/*!< The depth stencil state allows us to control what type of depth test Direct3D will do for each pixel */
		ID3D11DepthStencilState *	m_p2DDepthStencilState;		/*!< The depth stencil state for 2D drawing */
		ID3D11DepthStencilView *	m_pDepthStencilView;		/*!< The depth stencil view for the render target */
		ID3D11RasterizerState *		m_pRasterState;				/*!< The rasterizer state give us control over how polygons are rendered. */
		D3DXMATRIX					m_matProjection;			/*!< The projection matrix is used to translate the 3D scene into a 2D viewport space */
		D3DXMATRIX					m_matWorld;					/*!< The world matrix is used to convert the vertices of our objects into vertices in the 3D scene. */
		D3DXMATRIX					m_matOrtho;					/*!< The orthographic projection matrix is used for rendering 2D elements on the screen allowing us to skip the 3D rendering */
		float						m_afBackGroundcolor[4];		/*!< The componnets for the back */
		int							m_iScreenWidth;				/*!< Full screen width */
		int							m_iScreenHeight;			/*!< Full screen height */
	};
}
#endif // DxBase_h__
