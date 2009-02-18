// ***************************************************************
//  MainWindow   version:  1.0   Ankur Sheel  date: 04/28/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef mywinmainclass_h__
#define mywinmainclass_h__

#include "GraphicEngineDefines.h"

class cBaseApp ;
class cTimer;
class cInput;
class cFPS;
class cLogger;

class cMainWindow
{
protected:
	HWND			m_Hwnd ;				// holds the window handle
	HINSTANCE		m_hInstance ;			// holds the application instance
	int				m_iClientWidth ;		// the width of the client area
	int				m_iClientHeight ;		// the height of the client area
	int				m_iTopPos ;				// the Y coordinate of the top left corner of the window
	int				m_iLeftPos ;			// the X coordinate of the top left corner of the window
	cBaseApp*		m_pGameApp;				// pointer to the game app
	int				m_iFullScreenWidth ;	// the full screen width
	int				m_iFullScreenHeight ;	// the full screen height
	cTimer*			m_pGameTimer;			// pointer to a game timer
	cInput*			m_pInput;				// pointer to input class
	cFPS*			m_pFPS;
	cLogger*		m_pLogger;

	cMainWindow() ;
	cMainWindow(const cMainWindow&){}
	cMainWindow operator =(const cMainWindow&){}
	 ~cMainWindow() ;
	 void RegisterWin() ;
	 HWND CreateMyWindow(const int &nCmdShow, LPCTSTR lpWindowTitle);
	 LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );	
	 void OnRender();
	 void OnDestroyDevice();
	 void OnResetDevice();
	 void OnLostDevice();
	 void OnCreateDevice(const HINSTANCE hInst, const HWND hWnd);
	 void HandleLostDevice(HRESULT hr);
	 void GetWinRect() ;
	 void MoveWin() ;
	 void GetInput();
	static LRESULT CALLBACK StaticWndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );	
public:
	GRAPHIC_API HWND Init( const HINSTANCE &hInstance, const int &nCmdShow, LPCTSTR lpWindowTitle,const int iFullScreenWidth, const int iFullScreenHeight, cBaseApp* const pGameApp) ;
	GRAPHIC_API static cMainWindow& GetInstance() ;
	GRAPHIC_API void Run();
	GRAPHIC_API void DisplayFPS();
	GRAPHIC_API float GetElapsedTime();
	GRAPHIC_API float GetRunningTime();
	GRAPHIC_API void LockKey( const DWORD dwKey );
	GRAPHIC_API long GetAbsXMousePos();
	GRAPHIC_API long GetAbsYMousePos();

};
#endif // mywinmainclass_h__