// ***************************************************************
//  GraphicsTestView   version:  1.0   Ankur Sheel  date: 2011/08/31
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "GraphicsTestView.h"
#include "Game.h"
#include "BaseControl.hxx"
#include "Vector3.h"
#include "RandomGenerator.hxx"
#include "vertexstruct.h"


using namespace Utilities;
using namespace Graphics;
using namespace GameBase;
using namespace Base;

// ***************************************************************
cGraphicsTestView::cGraphicsTestView()
: m_pGame(NULL)
, m_pInfoLabelControl(NULL)
, m_bFinished(false)
{
}

// ***************************************************************
cGraphicsTestView::~cGraphicsTestView()
{
}

void cGraphicsTestView::VOnCreateDevice(IBaseApp * pGame, const HINSTANCE hInst, const HWND hWnd, 
								 int iClientWidth, int iClientHeight)
{
	cHumanView::VOnCreateDevice(pGame, hInst, hWnd, iClientWidth, iClientHeight);
	m_pGame = dynamic_cast<cGame *>(pGame);

	m_pInfoLabelControl = IBaseControl::CreateLabelControl(17, 14, 20, false, DEFAULT_CHARSET, "Arial", DT_LEFT, BLUE, "Press 'c' to start test");
	m_pParentControl->VAddChildControl(m_pInfoLabelControl);
	m_pInfoLabelControl->VSetPosition(cVector3(0.f, 0.f, 0.f));

}

// ***************************************************************
void cGraphicsTestView::VOnUpdate(TICK tickCurrent, const float fElapsedTime)
{
	cHumanView::VOnUpdate(tickCurrent, fElapsedTime);
}

// ***************************************************************
void cGraphicsTestView::VOnRender(TICK tickCurrent, float fElapsedTime)
{
	HRESULT hr;
	hr = OnBeginRender(tickCurrent);
	RenderPrivate(hr);
	if (SUCCEEDED(hr))
	{
		OnEndRender(hr);
	}
}

// ***************************************************************
bool cGraphicsTestView::VOnMsgProc( const Graphics::AppMsg & msg )
{
	if(!cHumanView::VOnMsgProc(msg))
	{
		if(msg.m_uMsg == WM_KEYDOWN)
		{
			if (msg.m_wParam == VK_ESCAPE  && !IsKeyLocked(VK_ESCAPE))
			{
				// lock the ESC key
				LockKey(VK_ESCAPE);
				PostQuitMessage(0);
			}
		}
		else if (msg.m_uMsg == WM_KEYUP)
		{
			if (msg.m_wParam == VK_ESCAPE)
			{
				UnlockKey(VK_ESCAPE);
			}
		}
		else if (msg.m_uMsg == WM_CHAR)
		{
			switch (msg.m_wParam)
			{ 
			case 'c':
				if(!m_bFinished)
				{
					m_pParentControl->VRemoveAllChildren();
					m_pInfoLabelControl = NULL;
				}
				if(m_pGame)
					m_pGame->GotoNextTest();
				break;
			}
		}
	}
	return true;
}

void cGraphicsTestView::TestUIControls()
{
	m_pInfoLabelControl = IBaseControl::CreateLabelControl(17, 14, 20, false, DEFAULT_CHARSET, "Arial", DT_LEFT, BLUE, "Testing UI Controls. Press 'c' to go to next test");
	m_pParentControl->VAddChildControl(m_pInfoLabelControl);
	m_pInfoLabelControl->VSetPosition(cVector3(0.f, 0.f, 0.f));

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
	btnCallback = bind(&cGame::ButtonPressed, m_pGame, _1);
	pButtonControl->VRegisterCallBack(btnCallback);

	IBaseControl * pButtonControl1 = IBaseControl::CreateButtonControl("Test\\buttonDefault.png", "Test\\buttonPressed.png");
	pWindowControl->VAddChildControl(pButtonControl1);
	pButtonControl1->VSetSize(30, 30);
	pButtonControl1->VSetPosition(cVector3(150.f, 90.f, 0.f));
	function<void (bool)> btn1Callback;
	btn1Callback = bind(&cGame::Button1Pressed, m_pGame, _1);
	pButtonControl1->VRegisterCallBack(btn1Callback);

	IBaseControl * pTextBoxControl = IBaseControl::CreateTextBoxControl("Test\\buttonDefault.png", 10, 10, 8, false, DEFAULT_CHARSET, "Arial", DT_VCENTER|DT_LEFT, BLACK);
	pWindowControl->VAddChildControl(pTextBoxControl);
	pTextBoxControl->VSetSize(200, 30);
	pTextBoxControl->VSetPosition(cVector3(0.f, 200.f, 0.f));

	IBaseControl * pCheckBoxControl = IBaseControl::CreateCheckBoxControl("Test\\Checked.png", "Test\\Unchecked.png", "Check\nBox", 30, 30, 10, 20, 10, 8, false, DEFAULT_CHARSET, "Arial", DT_VCENTER|DT_CENTER, WHITE);
	pWindowControl->VAddChildControl(pCheckBoxControl);
	pCheckBoxControl->VSetPosition(cVector3(0.f, 250.f, 0.f));
	function<void (bool)> checkBoxCallback;
	checkBoxCallback = bind(&cGame::CheckBoxPressed, m_pGame, _1);
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
}

void cGraphicsTestView::TestPoints()
{
	m_pInfoLabelControl = IBaseControl::CreateLabelControl(17, 14, 20, false, DEFAULT_CHARSET, "Arial", DT_LEFT, BLUE, "Testing Points. Press 'c' to go to next test");
	m_pParentControl->VAddChildControl(m_pInfoLabelControl);
	m_pInfoLabelControl->VSetPosition(cVector3(0.f, 0.f, 0.f));

	IRandomGenerator * pRandom = IRandomGenerator::CreateRandomGenerator();
	
	D3DVERTEX random_data[100];
	for(int count=0;count<100;count++)
	{
		random_data[count].m_vPosition.m_dX = pRandom->Random(100);
		random_data[count].m_vPosition.m_dY = pRandom->Random(100);
		random_data[count].m_vPosition.m_dZ = 1.0f;
		random_data[count].m_fRHW = 1.0f;
		random_data[count].m_dwColour =D3DCOLOR_XRGB (pRandom->Random(255), pRandom->Random(255), pRandom->Random(255));
	}
}

void cGraphicsTestView::Finished()
{
	m_bFinished = true;
	if(m_pInfoLabelControl != NULL)
	{
		m_pParentControl->VRemoveChildControl(m_pInfoLabelControl);
		m_pInfoLabelControl = NULL;
	}

	m_pInfoLabelControl = IBaseControl::CreateLabelControl(17, 14, 20, false, DEFAULT_CHARSET, "Arial", DT_LEFT, BLUE, "Finished all Tests. Press 'c' to exit");
	m_pParentControl->VAddChildControl(m_pInfoLabelControl);
	m_pInfoLabelControl->VSetPosition(cVector3(0.f, 0.f, 0.f));

}