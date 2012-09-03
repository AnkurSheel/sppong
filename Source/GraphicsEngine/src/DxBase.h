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
         *
         * Creates an object of this class
         ***********************************************/
		static void Create();
		static void Destroy();
	
	private:
		cDXBase() ;
		~cDXBase() ;
		void VOnInitialization(const HWND hWnd, const Base::cColor & bkColor, 
			const bool bFullScreen, const int iWidth, const int iHeight);
		HRESULT VOnResetDevice() ;
		HRESULT VBeginRender();
		void VEndRender(const HRESULT hr);
		LPDIRECT3DDEVICE9 VGetDevice() const;
		HRESULT VIsAvailable() const;
		void VToggleFullScreen();
		void VCleanup() ;
		void VDrawVertexPrimitiveUP(const D3DPRIMITIVETYPE primitiveType, const UINT iPrimitiveCount, const cVertex * const pData);
		void VToggleRenderState();
		/********************************************//**
		 *
		 * Creates the Direct3D object
		 ***********************************************/
		void DirectxInit() ;
		/********************************************//**
		 *
		 * Creates the DirectX device
		 ***********************************************/
		void CreateDirectxDevice() ;
		/********************************************//**
		 *
		 * Sets the presentation parameters depending on whether
		 * the application is fullscreen or windowed
		 ***********************************************/
		void SetParameters();
	private:
		LPDIRECT3D9				m_pD3D ;				/*!< Pointer to a direct3d object */
		LPDIRECT3DDEVICE9		m_pd3dDevice ;			/*!< Pointer to a direct3d device */
		D3DCAPS9				m_Caps ;				/*!< The capabilities of the direct 3d object */
		D3DCOLOR				m_BkColor ;				/*!< The background color */
		HWND					m_Hwnd ;				/*!< The window handle */
		D3DPRESENT_PARAMETERS	m_d3dpp ;				/*!< The presentation parameters */
		int						m_iWidth;				/*!< The width of the window */
		int						m_iHeight ;				/*!< The height of the window */
		D3DDISPLAYMODE			m_displayMode;			/*!< The display mode */
		bool					m_bFullScreen;			/*!< True if in fullscreen mode */
		bool					m_bWireFrameMode;		/*!< True if rendering in wireframe mode */
	
	public:
		static IDXBase * s_pDXBase;
	};
#include "DxBase.inl"

	
}
#endif // DxBase_h__
