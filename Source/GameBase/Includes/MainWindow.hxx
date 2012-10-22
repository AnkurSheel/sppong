// ***************************************************************
//  MainWindow   version:  1.0   Ankur Sheel  date: 2011/02/16
//  -------------------------------------------------------------
//  Interface for Main Window
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef MainWindow_hxx__
#define MainWindow_hxx__

#include "GameBaseDefines.h"

namespace GameBase
{
	class IBaseApp;
}

namespace GameBase
{
/********************************************//**
 * @brief Interface to Create the Window.
 *
 * Singleton class.\n
 * Usage :
 * \li Call \c GetInstance() to use this class.
 * \li Call \c VOnDestroy() when the application quits
 ***********************************************/
	class IMainWindow
	{
	public:
		virtual ~IMainWindow() {}

		/********************************************//**
		 * @param[in] hInstance A handle to the current instance of the application
		 * @param[in] nCmdShow Controls how the window is to be shown
		 * @param[in] pGame A pointer to the the IBaseApp object
		 * @param[in] bFullScreen Indicates whether the window is created in fullscreen mode
		 * @param[in] iFullScreenWidth The width when the window is full screen
		 * @param[in] iFullScreenHeight The height when the window is full screen
		 * @return Handle to the created window
		 *
		 * Initializes, Registers and creates the window
		 ***********************************************/
		GAMEBASE_API virtual HWND VOnInitialization( const HINSTANCE & hInstance,
										const int & nCmdShow,
										IBaseApp* const pGame,
										const bool bFullScreen,
										const int iFullScreenWidth,
										const int iFullScreenHeight) = 0;

		/********************************************//**
		 *
		 * Toggles between full screen and windowed mode
		 ***********************************************/
		GAMEBASE_API virtual void VToggleFullScreen() = 0;
		/********************************************//**
		 *
		 * Returns the title bar size if in windowed mode
		 * 0 if in fullscreen mode
		 ***********************************************/
		GAMEBASE_API virtual int VGetTitleBarSize() const = 0;
		/********************************************//**
		 *
		 * Destroys the Window
		 ***********************************************/
		virtual void VCleanup() = 0;
		/********************************************//**
		 * @return Returns a pointer to the singleton object
		 *
		 * Creates and returns a pointer to a singleton object of this class
		 ***********************************************/
		GAMEBASE_API static IMainWindow * GetInstance();

		/********************************************//**
		 *
		 * Destroys the window and the singleton object
		 ***********************************************/
		GAMEBASE_API static void Destroy();
	};
}
#endif // MainWindow_hxx__
