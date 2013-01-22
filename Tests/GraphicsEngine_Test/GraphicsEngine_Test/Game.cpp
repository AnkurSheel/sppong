#include "stdafx.h"
#include "Game.h"
#include "GraphicsTestView.h"
#include "ControlStructures.h"

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

void cGame::ButtonPressed(const unUIEventCallbackParam & params)
{
	Log_Write_L3(ILogger::LT_EVENT,  "Call Back Button Pressed");
}

void cGame::Button1Released(const unUIEventCallbackParam & params)
{
	Log_Write_L3(ILogger::LT_EVENT,  "Call Back Button1 Released");
}

void cGame::CheckBoxPressed(const unUIEventCallbackParam & params)
{
	Log_Write_L3(ILogger::LT_EVENT,  cString(100, "Check Box Pressed %d", params.bChecked));
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
		
		case TEST_MODELCOLOR:
			pView->TestModelColor();
			break;

		case TEST_MODELTEXTURE:
			pView->TestModelTexture();
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
