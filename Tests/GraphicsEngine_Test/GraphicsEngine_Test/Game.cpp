#include "stdafx.h"
#include "Game.h"
#include "BaseControl.hxx"
#include "MainWindow.hxx"
#include "Structures.h"
#include "Constants.h"
#include "Logger.hxx"

using namespace GameBase;
using namespace Graphics;
using namespace Utilities;

// ***************************************************************
cGame::cGame()
: m_pParentControl(NULL)
{

}

// ***************************************************************
cGame::~cGame()
{
	SAFE_DELETE(m_pParentControl);
}

// ***************************************************************
HWND cGame::OnInit( const HINSTANCE hInstance, const int nCmdShow,
				   const bool bFullscreen, const int iFullScreenWidth, 
				   const int iFullScreenHeight )
{
	HWND hWnd;
	cBaseApp::OnInit(hInstance, nCmdShow, bFullscreen, iFullScreenWidth, iFullScreenHeight, hWnd);

	m_pParentControl = IBaseControl::CreateWindowControl(WT_DESKTOP, "");
	m_pParentControl->SetSize(iFullScreenWidth, iFullScreenHeight);
	m_pParentControl->SetPosition(D3DXVECTOR3(0.f, 0.f, 0.f));

	IBaseControl * pWindowControl = IBaseControl::CreateWindowControl(WT_STANDARD, "Test\\window.png");
	m_pParentControl->AddChildControl(pWindowControl);
	pWindowControl->SetPosition(D3DXVECTOR3(300.f, 300.f, 0.f));
	pWindowControl->SetSize(400, 400);

	IBaseControl * pLabelControl = IBaseControl::CreateLabelControl(17, 14, 20, false, DEFAULT_CHARSET, "Mistral", DT_LEFT, BLUE, "Label");
	pWindowControl->AddChildControl(pLabelControl);
	pLabelControl->SetPosition(D3DXVECTOR3(0.f, 40.f, 0.f));

	IBaseControl * pButtonControl = IBaseControl::CreateButtonControl("Test\\buttonDefault.png", "Test\\buttonPressed.png", "Button", 20, 10, 8, false, DEFAULT_CHARSET, "Vladimir Script", DT_VCENTER|DT_CENTER, WHITE);
	pWindowControl->AddChildControl(pButtonControl);
	pButtonControl->SetSize(100, 100);
	pButtonControl->SetPosition(D3DXVECTOR3(0.f, 90.f, 0.f));
	function<void ()> btnCallback;
	btnCallback = bind(&cGame::ButtonPressed, this);
	pButtonControl->RegisterCallBack(btnCallback);

	IBaseControl * pButtonControl1 = IBaseControl::CreateButtonControl("Test\\buttonDefault.png", "Test\\buttonPressed.png");
	pWindowControl->AddChildControl(pButtonControl1);
	pButtonControl1->SetSize(30, 30);
	pButtonControl1->SetPosition(D3DXVECTOR3(150.f, 90.f, 0.f));
	function<void ()> btn1Callback;
	btn1Callback = bind(&cGame::Button1Pressed, this);
	pButtonControl1->RegisterCallBack(btn1Callback);

	IBaseControl * pTextBoxControl = IBaseControl::CreateTextBoxControl("Test\\buttonDefault.png", 10, 10, 8, false, DEFAULT_CHARSET, "Arial", DT_VCENTER|DT_LEFT, BLACK);
	pWindowControl->AddChildControl(pTextBoxControl);
	pTextBoxControl->SetSize(200, 30);
	pTextBoxControl->SetPosition(D3DXVECTOR3(0.f, 200.f, 0.f));

	IBaseControl * pCheckBoxControl = IBaseControl::CreateCheckBoxControl("Test\\Checked.png", "Test\\Unchecked.png", "Check\nBox", 30, 30, 10, 20, 10, 8, false, DEFAULT_CHARSET, "Arial", DT_VCENTER|DT_CENTER, WHITE);
	pWindowControl->AddChildControl(pCheckBoxControl);
	pCheckBoxControl->SetPosition(D3DXVECTOR3(0.f, 250.f, 0.f));
	function<void ()> checkBoxCallback;
	checkBoxCallback = bind(&cGame::CheckBoxPressed, this);
	pCheckBoxControl->RegisterCallBack(checkBoxCallback);

	return hWnd;
}

// ***************************************************************
Base::cString cGame::GetGameTitle() const
{
	return "Graphic Engine Test";
}

// ***************************************************************
bool cGame::OnMsgProc( const Graphics::AppMsg & msg )
{
	bool bHandled = false;
	switch(msg.m_uMsg)
	{
	case WM_CHAR:
		if (m_pParentControl)
		{
			bHandled = m_pParentControl->PostMsg(msg);
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
			bHandled = m_pParentControl->PostMsg(msg);
		}
		break;
	}
	return bHandled;
}

// ***************************************************************
void cGame::Run()
{
	AppMsg appMsg;
	appMsg.m_uMsg = WM_RENDER;
	appMsg.m_lParam = 0;
	appMsg.m_wParam = 0;

	if (m_pParentControl)
	{
		m_pParentControl->PostMsg(appMsg);
	}
}

// ***************************************************************
HRESULT cGame::OnResetDevice()
{
	AppMsg appMsg;
	appMsg.m_uMsg = WM_DEVICERESET;
	appMsg.m_lParam = 0;
	appMsg.m_wParam = 0;

	if (m_pParentControl)
	{
		m_pParentControl->PostMsg(appMsg);
	}

	return S_OK;
}

// ***************************************************************
void cGame::OnLostDevice()
{
	AppMsg appMsg;
	appMsg.m_uMsg = WM_DEVICELOST;
	appMsg.m_lParam = 0;
	appMsg.m_wParam = 0;

	if (m_pParentControl)
	{
		m_pParentControl->PostMsg(appMsg);
	}
}

void cGame::ButtonPressed() 
{
	Log_Write_L2(ILogger::LT_EVENT,  "Call Back Button Pressed");
}

void cGame::Button1Pressed() 
{
	Log_Write_L2(ILogger::LT_EVENT,  "Call Back Button1 Pressed");
}

void cGame::CheckBoxPressed() 
{
	Log_Write_L2(ILogger::LT_EVENT,  "Check Box Pressed");
}