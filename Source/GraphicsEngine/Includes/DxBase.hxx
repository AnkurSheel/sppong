// ***************************************************************
//  DxBase   version:  1.0   Ankur Sheel  date: 2011/02/16
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef DxBase_hxx__
#define DxBase_hxx__

namespace Base
{
	class cColor;
}

namespace Graphics
{
	class cVertex;
}

namespace Graphics
{
/********************************************//**
 * @brief Interface for DirectX.
 *
 * Singleton class.\n
 * Usage :
 * \li Call \c GetInstance() to use this class.
 * \li Call \c VOnDestroy() when the application quits
 ***********************************************/
	class IDXBase
	{
	public:
		virtual ~IDXBase(){}
		static IDXBase * Create();
		/********************************************//**
 		 * @param[in] hWnd A handle to the current window
		 * @param[in] bkColor The default background color of the window
		 * @param[in] bFullScreen True if the application is full screen. False if Windowed.
		 * @param[in] bVsyncEnabled True if we want Direct3D to render according to the users monitor refresh rate. false if we want to go as fast as possible.
		 * @param[in] iWidth Width of the window
		 * @param[in] iHeight Height of the window
		 * @param[in] fScreenDepth Far Depth setting for the 3D environment
		 * @param[in] fScreenNear Near Depth setting for the 3D environment
		 *
		 * 
		 ***********************************************/
		virtual void VInitialize(const HWND hWnd, 
			const Base::cColor & bkColor, const bool bFullScreen, 
			const bool bVsyncEnabled, const int iWidth, const int iHeight,
			const float fScreenDepth, const float fScreenNear) = 0;
		/********************************************//**
		 * 
		 *
		 * Begins the rendering and clears the surface
		 ***********************************************/
		virtual void VBeginRender() = 0;
		/********************************************//**
		 * 
		 *	
		 *Ends the rendering and presents the contents
		 ***********************************************/
		virtual void VEndRender() = 0;
		// * @return The pointer to IDirect3DDevice9 device
		// *
		// * Begins the rendering and clears the surface
		// ***********************************************/
		//virtual LPDIRECT3DDEVICE9 VGetDevice() const = 0;
		///********************************************//**
		// *
		// * Toggles between full screen and windowed mode
		// ***********************************************/
		//virtual void VToggleFullScreen() = 0;
		///********************************************//**
		// *
		// * Toggles the renderstate between wireframe and solid mode
		// ***********************************************/
		//virtual void VToggleRenderState() = 0;
		///********************************************//**
		// *
		// * Releases the Direct3D device and object
		// ***********************************************/
		//virtual void VCleanup() = 0;
	};
}
#endif // DxBase_h__