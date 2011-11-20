#include "stdafx.h"
#include "Game.h"

using namespace GameBase;

HWND cGame::OnInit( const HINSTANCE hInstance, const int nCmdShow,const bool bFullscreen )
{
	HWND hWnd;
	cBaseApp::OnInit(hInstance, nCmdShow, bFullscreen, hWnd);
	return hWnd;
}

Base::cString cGame::GetGameTitle() const
{
	return "Graphic Engine Test";
}

void cGame::OnMsgProc( const GameBase::AppMsg & msg )
{

}

void cGame::Run()
{

}