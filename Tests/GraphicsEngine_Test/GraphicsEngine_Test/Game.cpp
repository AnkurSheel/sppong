#include "stdafx.h"
#include "Game.h"
#include "BaseControl.hxx"
#include "MainWindow.hxx"
#include "Structures.h"
#include "Constants.h"
#include "Logger.hxx"
#include "Vector3.h"

using namespace GameBase;
using namespace Graphics;
using namespace Utilities;
using namespace Base;
// ***************************************************************
cGame::cGame(const cString strName)
: cBaseApp(strName)
, m_pParentControl(NULL)
{

}

// ***************************************************************
cGame::~cGame()
{
	SAFE_DELETE(m_pParentControl);
}

// ***************************************************************
HWND cGame:: VOnInitialization( const HINSTANCE hInstance, const int nCmdShow,
				   const bool bFullscreen, const int iFullScreenWidth, 
				   const int iFullScreenHeight )
{
	HWND hWnd;
	cBaseApp::VOnInitialization(hInstance, nCmdShow, bFullscreen, iFullScreenWidth, iFullScreenHeight, hWnd);

	m_pParentControl = IBaseControl::CreateWindowControl(WT_DESKTOP, "", true);
	m_pParentControl->VSetSize(iFullScreenWidth, iFullScreenHeight);
	m_pParentControl->VSetPosition(cVector3(0.f, 0.f, 0.f));

	IBaseControl * pWindowControl = IBaseControl::CreateWindowControl(WT_STANDARD, "Test\\window.png", false);
	m_pParentControl->VAddChildControl(pWindowControl);
	pWindowControl->VSetPosition(cVector3(300.f, 300.f, 0.f));
	pWindowControl->VSetSize(400, 400);

	IBaseControl * pLabelControl = IBaseControl::CreateLabelControl(17, 14, 20, false, DEFAULT_CHARSET, "Mistral", DT_LEFT, BLUE, "Label  ");
	pWindowControl->VAddChildControl(pLabelControl);
	pLabelControl->VSetPosition(cVector3(0.f, 40.f, 0.f));

	IBaseControl * pButtonControl = IBaseControl::CreateButtonControl("Test\\buttonDefault.png", "Test\\buttonPressed.png", "Button", 20, 10, 8, false, DEFAULT_CHARSET, "Vladimir Script", DT_VCENTER|DT_CENTER, WHITE, false);
	pWindowControl->VAddChildControl(pButtonControl);
	pButtonControl->VSetSize(100, 100);
	pButtonControl->VSetPosition(cVector3(0.f, 90.f, 0.f));
	function<void (bool)> btnCallback;
	btnCallback = bind(&cGame::ButtonPressed, this, _1);
	pButtonControl->VRegisterCallBack(btnCallback);

	IBaseControl * pButtonControl1 = IBaseControl::CreateButtonControl("Test\\buttonDefault.png", "Test\\buttonPressed.png");
	pWindowControl->VAddChildControl(pButtonControl1);
	pButtonControl1->VSetSize(30, 30);
	pButtonControl1->VSetPosition(cVector3(150.f, 90.f, 0.f));
	function<void (bool)> btn1Callback;
	btn1Callback = bind(&cGame::Button1Pressed, this, _1);
	pButtonControl1->VRegisterCallBack(btn1Callback);

	IBaseControl * pTextBoxControl = IBaseControl::CreateTextBoxControl("Test\\buttonDefault.png", 10, 10, 8, false, DEFAULT_CHARSET, "Arial", DT_VCENTER|DT_LEFT, BLACK);
	pWindowControl->VAddChildControl(pTextBoxControl);
	pTextBoxControl->VSetSize(200, 30);
	pTextBoxControl->VSetPosition(cVector3(0.f, 200.f, 0.f));

	IBaseControl * pCheckBoxControl = IBaseControl::CreateCheckBoxControl("Test\\Checked.png", "Test\\Unchecked.png", "Check\nBox", 30, 30, 10, 20, 10, 8, false, DEFAULT_CHARSET, "Arial", DT_VCENTER|DT_CENTER, WHITE);
	pWindowControl->VAddChildControl(pCheckBoxControl);
	pCheckBoxControl->VSetPosition(cVector3(0.f, 250.f, 0.f));
	function<void (bool)> checkBoxCallback;
	checkBoxCallback = bind(&cGame::CheckBoxPressed, this, _1);
	pCheckBoxControl->VRegisterCallBack(checkBoxCallback);

	IBaseControl * pVScrollBarControl = IBaseControl::CreateVScrollBarControl("Test\\ScrollBar_BG.png",
		"Test\\ScrollBar_Thumb.png", "Test\\ScrollBar_Thumb.png", "Test\\ScrollBar_Up.png", 
		"Test\\ScrollBar_Up.png", "Test\\ScrollBar_Down.png","Test\\ScrollBar_Down.png",
		0, 50);
	pWindowControl->VAddChildControl(pVScrollBarControl);
	pVScrollBarControl->VSetPosition(cVector3(300.f, 0.f, 0.f));
	pVScrollBarControl->VSetSize(30, 300);	

	IBaseControl * pHScrollBarControl = IBaseControl::CreateHScrollBarControl("Test\\ScrollBar_BG.png",
		"Test\\ScrollBar_Thumb.png", "Test\\ScrollBar_Thumb.png", "Test\\ScrollBar_Left.png", 
		"Test\\ScrollBar_Left.png", "Test\\ScrollBar_Right.png","Test\\ScrollBar_Right.png",
		0, 50);
	pWindowControl->VAddChildControl(pHScrollBarControl);
	pHScrollBarControl->VSetPosition(cVector3(0.f, 300.f, 0.f));
	pHScrollBarControl->VSetSize(300, 30);	

	return hWnd;
}

// ***************************************************************
Base::cString cGame::VGetGameTitle() const
{
	return VGetName();
}

// ***************************************************************
bool cGame::VOnMsgProc( const Graphics::AppMsg & msg )
{
	bool bHandled = false;
	switch(msg.m_uMsg)
	{
	case WM_CHAR:
		if (m_pParentControl)
		{
			bHandled = m_pParentControl->VPostMsg(msg);
		}
		if(!bHandled)
		{
			switch (msg.m_wParam)
			{ 
			case VK_SPACE:
				IMainWindow::GetInstance()->VToggleFullScreen();
				Log_Write_L3(ILogger::LT_DEBUG, "Toggled FullScreen");
			}
		}
		break;
	case WM_MOUSEMOVE:
	case WM_LBUTTONUP:
	case WM_LBUTTONDOWN:
	case WM_KEYUP:
	case WM_KEYDOWN:
		if (m_pParentControl)
		{
			bHandled = m_pParentControl->VPostMsg(msg);
		}
		break;
	}
	return bHandled;
}

// ***************************************************************
void cGame::VRun()
{
	AppMsg appMsg;
	appMsg.m_uMsg = WM_RENDER;
	appMsg.m_lParam = 0;
	appMsg.m_wParam = 0;

	if (m_pParentControl)
	{
		m_pParentControl->VPostMsg(appMsg);
	}
}

// ***************************************************************
HRESULT cGame::VOnResetDevice()
{
	AppMsg appMsg;
	appMsg.m_uMsg = WM_DEVICERESET;
	appMsg.m_lParam = 0;
	appMsg.m_wParam = 0;

	if (m_pParentControl)
	{
		m_pParentControl->VPostMsg(appMsg);
	}

	return S_OK;
}

// ***************************************************************
void cGame::VOnLostDevice()
{
	AppMsg appMsg;
	appMsg.m_uMsg = WM_DEVICELOST;
	appMsg.m_lParam = 0;
	appMsg.m_wParam = 0;

	if (m_pParentControl)
	{
		m_pParentControl->VPostMsg(appMsg);
	}
}

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