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

namespace Utilities
{
	class IResCache;
}

namespace Graphics
{
	class cMainWindow
		: public IMainWindow
	{
	public:
		cMainWindow() ;
		~cMainWindow() ;
		
		HWND Init( const HINSTANCE &hInstance, const int &nCmdShow, const Base::cString & lpWindowTitle,const int iFullScreenWidth, const int iFullScreenHeight, const bool bFullScreen) ;
		Utilities::IResCache * GetResourceCache() const;
		int GetClientWindowHeight();
		int GetClientWindowWidth();
		void Destroy();

	private:
		cMainWindow(const cMainWindow&){}
		cMainWindow operator =(const cMainWindow&){}
		void RegisterWin() ;
		HWND CreateMyWindow(const int &nCmdShow, const Base::cString &  lpWindowTitle, const bool bFullScreen);
		LRESULT CALLBACK WndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );	
		void OnDestroyDevice();
		void OnCreateDevice(const HINSTANCE hInst, const HWND hWnd, const bool bFullScreen);
		void GetWinRect() ;
		void MoveWin() ;
		static LRESULT CALLBACK StaticWndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );	

	private:
		HWND					m_Hwnd ;				// holds the window handle
		HINSTANCE				m_hInstance ;			// holds the application instance
		int						m_iClientWidth ;		// the width of the client area
		int						m_iClientHeight ;		// the height of the client area
		int						m_iTopPos ;				// the Y coordinate of the top left corner of the window
		int						m_iLeftPos ;			// the X coordinate of the top left corner of the window
		int						m_iFullScreenWidth ;	// the full screen width
		int						m_iFullScreenHeight ;	// the full screen height
		Utilities::IResCache *	m_pResourceCache;
	};

	static IMainWindow * s_pWindow = NULL;
}
#endif // MainWindow_h__
