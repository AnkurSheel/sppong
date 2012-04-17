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

#include "GraphicEngineDefines.h"

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
		: public Base::cNonCopyable
	{
	public:
		virtual ~IDXBase(){}
		
		/********************************************//**
		 * @param[in] hWnd A handle to the current window
		 * @param[in] bkColor The default background color of the window
		 * @param[in] bFullScreen True if the application is full screen. False if Windowed.
		 * @param[in] iWidth Width of the window
		 * @param[in] iHeight Height of the window
		 *
		 * Initializes the directX object
		 ***********************************************/
		virtual void VOnInitialization(const HWND hWnd,
							const D3DCOLOR & bkColor, 
							const bool bFullScreen,
							const int iWidth, 
							const int iHeight) = 0;
		/********************************************//**
		 * @return The success code. D3D_OK if the method succeeds.
		 *
		 * Resets the device
		 ***********************************************/
		virtual HRESULT VOnResetDevice() = 0;
		/********************************************//**
		 * @return D3D_OK if the method succeeds. D3DERR_INVALIDCALL otherwise
		 *
		 * Begins the rendering and clears the surface
		 ***********************************************/
		virtual HRESULT VBeginRender() = 0;
		/********************************************//**
		 * @param[in] hr The result from previous calls to the device
		 *	
		 *Ends the rendering and presents the contents
		 ***********************************************/
		virtual void VEndRender(const HRESULT hr) = 0;
		/********************************************//**
		 * @return S_OK if the device is ok for rendering
		 *
		 * Checks if the device is available for rendering or not
		 ***********************************************/
		virtual HRESULT VIsAvailable() const = 0;
		/********************************************//**
		 *
		 * Releases the DirectX object and deletes the singleton object
		 ***********************************************/
		virtual void VOnDestroy() = 0;
		/********************************************//**
		 * @return The pointer to IDirect3DDevice9 device
		 *
		 * Begins the rendering and clears the surface
		 ***********************************************/
		virtual LPDIRECT3DDEVICE9 VGetDevice() const = 0;
		/********************************************//**
		 *
		 * Toggles between full screen and windowed mode
		 ***********************************************/
		virtual void VToggleFullScreen() = 0;
		
		/********************************************//**
		 * @return Returns a pointer to the singleton object
		 *
		 * Creates and returns a pointer to a singleton object of this class
		 ***********************************************/
		GRAPHIC_API static IDXBase * GetInstance();
	};
}
#endif // DxBase_h__