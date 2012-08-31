#include "stdafx.h"
#include "Game.h"
#include "GraphicsTestView.h"

using namespace GameBase;
using namespace Graphics;
using namespace Utilities;
using namespace Base;
// ***************************************************************
cGame::cGame(const cString strName)
: cBaseApp(strName)
, m_currentTest(Tests::NONE)
{

}

// ***************************************************************
cGame::~cGame()
{
	VCleanup();
}

// ***************************************************************
void cGame:: VOnInitialization( const HINSTANCE hInstance, const int nCmdShow,
				   const bool bFullscreen, const int iFullScreenWidth, 
				   const int iFullScreenHeight, HWND & outHwnd)
{
	HWND hWnd;
	cBaseApp::VOnInitialization(hInstance, nCmdShow, bFullscreen, iFullScreenWidth, iFullScreenHeight, hWnd);

	m_currentTest = Tests::NONE;
}

void cGame::VCreateHumanView()
{
	m_pHumanView = DEBUG_NEW cGraphicsTestView();
}

// ***************************************************************
Base::cString cGame::VGetGameTitle() const
{
	return VGetName();
}
// ***************************************************************

void cGame::ButtonPressed( bool bPressed )
{
	if (bPressed)
	{
		Log_Write_L2(ILogger::LT_EVENT,  "Call Back Button Pressed");
	}
	else
	{
		Log_Write_L2(ILogger::LT_EVENT,  "Call Back Button Released");
	}
}

void cGame::Button1Pressed( bool bPressed )
{
	if (bPressed)
	{
		Log_Write_L2(ILogger::LT_EVENT,  "Call Back Button1 Pressed");
	}
	else
	{
		Log_Write_L2(ILogger::LT_EVENT,  "Call Back Button1 Released");
	}
}

void cGame::CheckBoxPressed( bool bPressed )
{
	if(bPressed)
	{
		Log_Write_L2(ILogger::LT_EVENT,  "Check Box Pressed");
	}
}

void cGame::GotoNextTest()
{
	if(m_currentTest == Tests::ALL)
	{
		PostQuitMessage(-1);
		return;
	}
	
	m_currentTest = Tests(m_currentTest + 1);
	
	if(m_currentTest == Tests::ALL)
	{
		cGraphicsTestView * pView = dynamic_cast<cGraphicsTestView *>(m_pHumanView);
		if(pView)
			pView->Finished();
	}
	else if(m_currentTest == Tests::UICONTROLS)
	{
		cGraphicsTestView * pView = dynamic_cast<cGraphicsTestView *>(m_pHumanView);
		if(pView)
			pView->TestUIControls();
	}
}