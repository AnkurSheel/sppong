// ***************************************************************
//  MainWindow   version:  1.0   Ankur Sheel  date: 04/28/2008
//  -------------------------------------------------------------
//  Window for that application
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
//
// ***************************************************************
#ifndef MainWindow_h__
#define MainWindow_h__

#include "MainWindow.hxx"

namespace Base
{
	class cString;
}

namespace GameBase
{
    /********************************************//**
     * @brief Class Declaration for \c IMainWindow
     * interface
     ***********************************************/
	class cMainWindow
		: public IMainWindow
		, public Base::cNonCopyable
	{
	public:
		/********************************************//**
         *
         * Create an object of this class
         ***********************************************/
		static void Create();
		static void Destroy();
	private:
		cMainWindow();
		~cMainWindow();
		HWND VOnInitialization(const HINSTANCE & hInstance, const int& nCmdShow,
			IBaseApp * const pGame, const bool bFullScreen,
			const int iFullScreenWidth, const int iFullScreenHeight);
		void VToggleFullScreen();
		void VCleanup();
		/********************************************//**
		 * @param[in] hWnd – Unique handle to the window.
         * @param[in] message – Incoming message.
         * @param[in] wParam – Parameter of the message (unsigned int).
         * @param[in] lParam – Parameter of the message (long).
         *
		 * Event handler. Routes messages to appropriate instance.
		 ***********************************************/
		static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT msg,
											WPARAM wParam, LPARAM lParam);

        /********************************************//**
         *
         * Register the window
         ***********************************************/
		void RegisterWin() ;
		/********************************************//**
		 * @param[in] nCmdShow Controls how the window is to be shown
		 * @param[in] lpWindowTitle Controls how the window is to be shown
		 *
		 * Creates the window
		 ***********************************************/
		void CreateMyWindow(const int& nCmdShow,
							const Base::cString& lpWindowTitle);
		/********************************************//**
		 * @param[in] hWnd – Unique handle to the window.
         * @param[in] message – Incoming message.
         * @param[in] wParam – Parameter of the message (unsigned int).
         * @param[in] lParam – Parameter of the message (long).
         *
		 *  Application event handler.
		 ***********************************************/
		 LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam,
								LPARAM lParam );
		/********************************************//**
		 *
		 * Function called when the application is closed
		 ***********************************************/
		void OnWindowDestroyed();
        /********************************************//**
		 *
		 * Sets the settings of the default display device
		 * to the specified graphics mode.
		 ***********************************************/
		void SetDisplayResolution();
		void CalculateWindowRect();

	private:
		const DWORD			m_kdwFullScreenStyle;   /*!< The fullscreen window style format. It is set to WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE */
		const DWORD			m_kdwWindowedStyle;     /*!< The fullscreen window style format. It is set to WS_SYSMENU | WS_MINIMIZEBOX | WS_CAPTION */
		bool				m_bFullScreen;			/*!< True if in fullscreen mode */
		HWND				m_Hwnd;					/*!< Window handle */
		HINSTANCE			m_hInstance;			/*!< Application instance */
		int					m_iFullScreenWidth;		/*!< Full screen width */
		int					m_iFullScreenHeight;	/*!< Full screen height */
		IBaseApp*			m_pGame;				/*!< Pointer to the App */
		RECT				m_windowRect;			/*!< stores the window dimensions in windowed mode */
	
	public:
		static IMainWindow * s_pWindow;
	};

	
}
#endif // MainWindow_h__
