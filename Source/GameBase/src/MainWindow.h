// ***************************************************************
//  MainWindow   version:  1.0   Ankur Sheel  date: 04/28/2008
//  -------------------------------------------------------------
//  Window for that application
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef MainWindow_hxx__
#define MainWindow_hxx__

#include "MainWindow.hxx"

namespace Base
{
	class cString;
}

namespace GameBase
{
	class cMainWindow
		: public IMainWindow
	{
	public:
		cMainWindow();
		~cMainWindow();
		HWND Init(const HINSTANCE& hInstance, const int& nCmdShow,
					IBaseApp* const pGame, const bool bFullScreen, 
					const int iFullScreenWidth, const int iFullScreenHeight);
		void Destroy();

	private:
		void RegisterWin() ;
		void CreateMyWindow(const int& nCmdShow, 
							const Base::cString& lpWindowTitle);
		LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, 
								LPARAM lParam );	
		void OnDestroyDevice();
		void OnCreateDevice();
		void ToggleFullScreen();
		void SetDisplayResolution();
		static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT msg,
											WPARAM wParam, LPARAM lParam);	

	private:
		const DWORD			m_kdwFullScreenStyle;
		const DWORD			m_kdwWindowedStyle;		
		WINDOWPLACEMENT		m_wp;					// stores the window placement if in windowed mode
		bool				m_bFullScreen;			// is true if we are in fullscreen mode
		HWND				m_Hwnd;					// holds the window handle
		HINSTANCE			m_hInstance;			// holds the application instance
		int					m_iFullScreenWidth;		// the full screen width
		int					m_iFullScreenHeight;	// the full screen height
		IBaseApp*			m_pGame;				// pointer to the Game
	};

	static IMainWindow * s_pWindow = NULL;
}
#endif // MainWindow_h__
