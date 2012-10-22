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
	struct stVertex;
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
		static IDXBase * GetInstance();
		static void Destroy();
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
		 * Initializes the DirectX device and sets it up for use. 
		 ***********************************************/
		virtual void VInitialize(const HWND & hWnd, 
			const Base::cColor & bkColor, const bool bFullScreen, 
			const bool bVsyncEnabled, const int iWidth, const int iHeight,
			const float fScreenDepth, const float fScreenNear) = 0;
		/********************************************//**
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
		/********************************************//**
		 *
		 * Turns the Z buffer on for 3D rendering
		 ***********************************************/
		virtual void VTurnZBufferOn() = 0;
		/********************************************//**
		 *
		 * Turns the Z buffer on for 2D rendering
		 ***********************************************/
		virtual void VTurnZBufferOff() = 0;
		/********************************************//**
		 *
		 * Turns Alpha Blending On
		 ***********************************************/
		virtual void VTurnOnAlphaBlending() = 0;
		/********************************************//**
		 *
		 * Turns Alpha Blending Off
		 ***********************************************/
		virtual void VTurnOffAlphaBlending() = 0;
		/********************************************//**
		 * @return The pointer to DX11 device
		 *
		 * Returns a pointer to the DirectX11 device
		 ***********************************************/
		virtual ID3D11Device *  VGetDevice() const = 0;
		/********************************************//**
		 * @return The pointer to DX11 device context
		 *
		 * Returns a pointer to the DirectX11 device context
		 ***********************************************/
		virtual ID3D11DeviceContext * VGetDeviceContext() const = 0;
		/********************************************//**
		 * @return The World Matrix
		 *
		 * Returns the world matrix
		 ***********************************************/
		virtual const D3DMATRIX & VGetWorldMatrix() const = 0;
		/********************************************//**
		 * @return The projection matrix
		 *
		 * Returns the projection matrix
		 ***********************************************/
		virtual const D3DMATRIX & VGetProjectionMatrix() const = 0;
		/********************************************//**
		 * @return The ortho matrix
		 *
		 * Returns the ortho matrix
		 ***********************************************/
		virtual const D3DMATRIX & VGetOrthoMatrix() const = 0;
		/********************************************//**
		 * @return The screen width
		 *
		 * Returns the screen width
		 ***********************************************/
		virtual int VGetScreenWidth() const = 0;
		/********************************************//**
		 * @return The screen height
		 *
		 * Returns the screen height
		 ***********************************************/
		virtual int VGetScreenHeight() const = 0;
		/********************************************//**
		 * @param[in] True if fullscreen. False otherwise
		 *
		 * Sets the full screen/windowed mode for the DirectX engine
		 ***********************************************/
		virtual void VSetFullScreenMode(const bool bIsFullScreen) = 0;
	};
}
#endif // DxBase_h__