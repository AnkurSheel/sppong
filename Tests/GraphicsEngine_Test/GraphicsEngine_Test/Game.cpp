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
, m_currentTest(TEST_NONE)
{

}

// ***************************************************************
cGame::~cGame()
{
	VCleanup();
}

// ***************************************************************
void cGame:: VOnInitialization(const HINSTANCE & hInstance, const int nCmdShow,
							   const cString & strOptionsFileName)
{
	cBaseApp::VOnInitialization(hInstance, nCmdShow, strOptionsFileName);

	m_currentTest = TEST_NONE;
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
	if(m_currentTest == TEST_ALL)
	{
		PostQuitMessage(-1);
		return;
	}
	
	m_currentTest = Tests(m_currentTest + 1);
	cGraphicsTestView * pView = dynamic_cast<cGraphicsTestView *>(m_pHumanView);
	
	if(pView)
	{
		pView->TestFinished();

		switch (m_currentTest)
		{
		case TEST_ALL:
			pView->Finished();
			break;
		
		case TEST_TRIANGLE:
			pView->TestTriangle();
			break;

		case TEST_TEXTURETRIANGLE:
			pView->TestTextureTriangle();
			break;

		case TEST_SPRITE:
			pView->TestSprite();
			break;

		case TEST_FONT:
			pView->TestFont();
			break;

		case TEST_UICONTROLS:
			pView->TestUIControls();
			break;
		}
	}
}

// ***************************************************************
Tests cGame::GetCurrentTest() const
{
	return m_currentTest;
}
