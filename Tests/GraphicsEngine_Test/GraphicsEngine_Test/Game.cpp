#include "stdafx.h"
#include "Game.h"
#include "BaseControl.hxx"
#include "DxBase.hxx"
#include "Structures.h"
#include "Constants.h"

using namespace GameBase;
using namespace Graphics;

cGame::cGame()
: m_pParentControl(NULL)
, m_pWindowControl(NULL)
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

	m_pParentControl = IBaseControl::CreateWindowControl(WT_DESKTOP);
	m_pWindowControl = IBaseControl::CreateWindowControl(WT_STANDARD);

	m_pParentControl->SetHeight(IDXBase::GetInstance()->GetDisplayHeight());
	m_pParentControl->SetWidth(IDXBase::GetInstance()->GetDisplayWidth());
	m_pParentControl->SetPosition(D3DXVECTOR3(0.f, 0.f, 0.f));
	m_pWindowControl->LoadCanvasFromFile("resources\\Sprites\\title.jpg");
	m_pWindowControl->SetPosition(D3DXVECTOR3(100.f, 100.f, 0.f));

	m_pParentControl->AddChildControl(m_pWindowControl);

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