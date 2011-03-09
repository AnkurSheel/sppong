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
	class ITimer;
}

namespace Graphics
{
	class IInput;
	class IFPS;
}

namespace Graphics
{
	class cMainWindow
		: public IMainWindow
	{

	private:
		cMainWindow(const cMainWindow&){}
		cMainWindow operator =(const cMainWindow&){}
		void RegisterWin() ;
		HWND CreateMyWindow(const int &nCmdShow, const Base::cString &  lpWindowTitle);
		LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );	
		void OnRender();
		void OnDestroyDevice();
		void OnResetDevice();
		void OnLostDevice();
		void OnCreateDevice(const HINSTANCE hInst, const HWND hWnd);
		void HandleLostDevice(HRESULT hr);
		void GetWinRect() ;
		void MoveWin() ;
		void GetInput()  const;
		static LRESULT CALLBACK StaticWndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );	
	public:
		cMainWindow() ;
		~cMainWindow() ;
		HWND Init( const HINSTANCE &hInstance, const int &nCmdShow, const Base::cString & lpWindowTitle,const int iFullScreenWidth, const int iFullScreenHeight, IBaseApp* const pGameApp) ;
		//IMainWindow * TheWindow() ;
		void Run();
		void DisplayFPS();
		float GetElapsedTime() const;
		float GetRunningTime() const;
		void LockKey( const DWORD dwKey );
		long GetAbsXMousePos() const;
		long GetAbsYMousePos() const;
		void Destroy();
	private:
		HWND					m_Hwnd ;				// holds the window handle
		HINSTANCE				m_hInstance ;			// holds the application instance
		int						m_iClientWidth ;		// the width of the client area
		int						m_iClientHeight ;		// the height of the client area
		int						m_iTopPos ;				// the Y coordinate of the top left corner of the window
		int						m_iLeftPos ;			// the X coordinate of the top left corner of the window
		IBaseApp *				m_pGameApp;				// pointer to the game app
		int						m_iFullScreenWidth ;	// the full screen width
		int						m_iFullScreenHeight ;	// the full screen height
		Utilities::ITimer *		m_pGameTimer;			// pointer to a game timer
		Graphics::IInput *		m_pInput;				// pointer to input class
		Graphics::IFPS *		m_pFPS;
	};

	static IMainWindow * s_pWindow = NULL;
}
#endif // MainWindow_h__
