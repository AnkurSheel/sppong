// ***************************************************************
//  MainWindow   version:  1.0   Ankur Sheel  date: 04/28/2008
//  -------------------------------------------------------------
//  
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
		cMainWindow() ;
		~cMainWindow() ;
		
		HWND Init( const HINSTANCE &hInstance, const int &nCmdShow, IBaseApp * const pGame, const bool bFullScreen) ;
		int GetClientWindowHeight() const;
		int GetClientWindowWidth() const;
		void Destroy();

	private:
		cMainWindow(const cMainWindow&);
		cMainWindow operator =(const cMainWindow&){}
		void RegisterWin() ;
		HWND CreateMyWindow(const int &nCmdShow, const Base::cString &  lpWindowTitle);
		LRESULT CALLBACK WndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );	
		void OnDestroyDevice();
		void OnCreateDevice(const HINSTANCE hInst, const HWND hWnd);
		void GetWinRect() ;
		void MoveWin() ;
		void ToggleFullScreen();
		static LRESULT CALLBACK StaticWndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );	

	private:
		const DWORD				m_dwFullScreenStyle;
		const DWORD				m_dwWindowedStyle;
		WINDOWPLACEMENT			m_wp;
		bool					m_bFullScreen;
		HWND					m_Hwnd ;				// holds the window handle
		HINSTANCE				m_hInstance ;			// holds the application instance
		UINT					m_uClientWidth ;		// the width of the client area
		UINT					m_uClientHeight ;		// the height of the client area
		UINT					m_uTopPos ;				// the Y coordinate of the top left corner of the window
		UINT					m_uLeftPos ;			// the X coordinate of the top left corner of the window
		UINT					m_uFullScreenWidth ;	// the full screen width
		UINT					m_uFullScreenHeight ;	// the full screen height
		IBaseApp *				m_pGame;
	};

	static IMainWindow * s_pWindow = NULL;

#include "MainWindow.inl"
}
#endif // MainWindow_h__
