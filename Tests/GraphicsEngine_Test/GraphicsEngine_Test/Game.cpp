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
	m_pParentControl->SetHeight(IMainWindow::TheWindow()->GetClientWindowHeight());
	m_pParentControl->SetWidth(IMainWindow::TheWindow()->GetClientWindowWidth());
	m_pParentControl->SetPosition(D3DXVECTOR3(0.f, 0.f, 0.f));

	IBaseControl * pWindowControl = IBaseControl::CreateWindowControl(WT_STANDARD, "Test\\window.png");
	pWindowControl->SetPosition(D3DXVECTOR3(100.f, 100.f, 0.f));

	IBaseControl * pLabelControl = IBaseControl::CreateLabelControl(14, 14, 20, false, DEFAULT_CHARSET, "Arial", DT_LEFT, BLUE, "Label");
	pLabelControl->SetHeight(15);
	pLabelControl->SetWidth(75);
	pLabelControl->SetPosition(D3DXVECTOR3(0.f, 20.f, 0.f));

	IBaseControl * pButtonControl = IBaseControl::CreateButtonControl("Test\\buttonDefault.png", "Test\\buttonPressed.png", "Button", 4, 14, 20, false, DEFAULT_CHARSET, "Arial", DT_LEFT, GREEN);
	pButtonControl->SetPosition(D3DXVECTOR3(0.f, 30.f, 0.f));
	m_pParentControl->AddChildControl(pWindowControl);
	pWindowControl->AddChildControl(pLabelControl);
	pWindowControl->AddChildControl(pButtonControl);

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
		m_pParentControl->PostMsg(msg);
		break;;
	}
}

void cGame::Run()
{

	AppMsg appMsg;
	appMsg.m_uMsg = WM_RENDER;
	appMsg.m_lParam = 0;
	appMsg.m_wParam = 0;

	m_pParentControl->PostMsg(appMsg);
}