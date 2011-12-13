#include "stdafx.h"
#include "Game.h"
#include "BaseControl.hxx"
#include "MainWindow.hxx"
#include "Structures.h"
#include "Constants.h"

using namespace GameBase;
using namespace Graphics;

cGame::cGame()
: m_pParentControl(NULL)
{

}

cGame::~cGame()
{
	SAFE_DELETE(m_pParentControl);
}

HWND cGame::OnInit( const HINSTANCE hInstance, const int nCmdShow,const bool bFullscreen )
{
	HWND hWnd;
	cBaseApp::OnInit(hInstance, nCmdShow, bFullscreen, hWnd);

	m_pParentControl = IBaseControl::CreateWindowControl(WT_DESKTOP, "");
	m_pParentControl->SetSize(IMainWindow::TheWindow()->GetClientWindowWidth(), IMainWindow::TheWindow()->GetClientWindowHeight());
	m_pParentControl->SetPosition(D3DXVECTOR3(0.f, 0.f, 0.f));

	IBaseControl * pWindowControl = IBaseControl::CreateWindowControl(WT_STANDARD, "Test\\window.png");
	pWindowControl->SetPosition(D3DXVECTOR3(100.f, 100.f, 0.f));
	pWindowControl->SetSize(400, 400);

	IBaseControl * pLabelControl = IBaseControl::CreateLabelControl(17, 14, 20, false, DEFAULT_CHARSET, "Arial", DT_LEFT, BLUE, "Label");
	pLabelControl->SetPosition(D3DXVECTOR3(0.f, 40.f, 0.f));

	IBaseControl * pButtonControl = IBaseControl::CreateButtonControl("Test\\buttonDefault.png", "Test\\buttonPressed.png", "Button", 20, 10, 8, false, DEFAULT_CHARSET, "Arial", DT_VCENTER|DT_CENTER, WHITE);
	pButtonControl->SetSize(100, 100);
	pButtonControl->SetPosition(D3DXVECTOR3(0.f, 90.f, 0.f));

	IBaseControl * pButtonControl1 = IBaseControl::CreateButtonControl("Test\\buttonDefault.png", "Test\\buttonPressed.png");
	pButtonControl1->SetSize(30, 30);
	pButtonControl1->SetPosition(D3DXVECTOR3(150.f, 90.f, 0.f));

	IBaseControl * pTextBoxControl = IBaseControl::CreateTextBoxControl("Test\\buttonDefault.png", 10, 10, 8, false, DEFAULT_CHARSET, "Arial", DT_VCENTER|DT_LEFT, BLACK);
	pTextBoxControl->SetSize(200, 30);
	pTextBoxControl->SetPosition(D3DXVECTOR3(0.f, 200.f, 0.f));


	IBaseControl * pCheckBoxControl = IBaseControl::CreateCheckBoxControl("Test\\Checked.png", "Test\\Unchecked.png", "Check\nBox", 30, 30, 10, 20, 10, 8, false, DEFAULT_CHARSET, "Arial", DT_VCENTER|DT_CENTER, WHITE);
	pCheckBoxControl->SetPosition(D3DXVECTOR3(0.f, 250.f, 0.f));

	m_pParentControl->AddChildControl(pWindowControl);
	pWindowControl->AddChildControl(pLabelControl);
	pWindowControl->AddChildControl(pButtonControl);
	pWindowControl->AddChildControl(pButtonControl1);
	pWindowControl->AddChildControl(pTextBoxControl);
	pWindowControl->AddChildControl(pCheckBoxControl);

	return hWnd;
}

Base::cString cGame::GetGameTitle() const
{
	return "Graphic Engine Test";
}

void cGame::OnMsgProc( const Graphics::AppMsg & msg )
{
	switch(msg.m_uMsg)
	{
	case WM_MOUSEMOVE:
	case WM_LBUTTONUP:
	case WM_LBUTTONDOWN:
	case WM_KEYUP:
	case WM_KEYDOWN:
	case WM_CHAR:
		if (m_pParentControl)
		{
			m_pParentControl->PostMsg(msg);
		}
		break;
	}
}

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