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
#include "DxBase.hxx"
#include "Color.h"

using namespace Utilities;
using namespace Graphics;
using namespace GameBase;
using namespace Base;

// ***************************************************************
cGraphicsTestView::cGraphicsTestView()
: m_pGame(NULL)
, m_pInfoLabelControl(NULL)
, m_bFinished(false)
, m_vertexData(NULL)
, m_iVertexListCount(1000)
{
}

// ***************************************************************
cGraphicsTestView::~cGraphicsTestView()
{
	Cleanup();
}

void cGraphicsTestView::VOnCreateDevice(IBaseApp * pGame, const HINSTANCE hInst, const HWND hWnd, 
								 int iClientWidth, int iClientHeight)
{
	cHumanView::VOnCreateDevice(pGame, hInst, hWnd, iClientWidth, iClientHeight);
	m_pGame = dynamic_cast<cGame *>(pGame);

	m_pInfoLabelControl = IBaseControl::CreateLabelControl(17, 14, 20, false, DEFAULT_CHARSET, "Arial", DT_LEFT, cColor::BLUE.GetColor(), "Press 'c' to start test");
	m_pParentControl->VAddChildControl(m_pInfoLabelControl);
	m_pInfoLabelControl->VSetPosition(cVector3(0.f, 0.f, 0.f));

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

			case 'w':
				IDXBase::GetInstance()->VToggleRenderState();
				break;
			}
		}
	}
	return true;
}

// ***************************************************************
void cGraphicsTestView::VRenderPrivate()
{
	cHumanView::VRenderPrivate();

	if(m_pGame)
	{
		switch(m_pGame->GetCurrentTest())
		{
		case TEST_POINTLIST:
			ShowPointList(m_vertexData, m_iVertexListCount);
			break;

		case TEST_LINELIST:
			ShowLineList(m_vertexData, m_iVertexListCount/2);
			break;

		case TEST_LINESTRIP:
			ShowLineStrip(m_vertexData, m_iVertexListCount-1);
			break;

		case TEST_TRIANGLELIST:
			ShowTriangleList(m_vertexData, 4);
			break;
		}
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

	m_pInfoLabelControl = IBaseControl::CreateLabelControl(17, 14, 20, false, DEFAULT_CHARSET, "Arial", DT_LEFT, cColor::BLUE.GetColor(), "Finished all Tests. Press 'c' to exit");
	m_pParentControl->VAddChildControl(m_pInfoLabelControl);
	m_pInfoLabelControl->VSetPosition(cVector3(0.f, 0.f, 0.f));
}

void cGraphicsTestView::TestUIControls()
{
	m_pInfoLabelControl = IBaseControl::CreateLabelControl(17, 14, 20, false, DEFAULT_CHARSET, "Arial", DT_LEFT, cColor::BLUE.GetColor(), "Testing UI Controls. Press 'c' to go to next test");
	m_pParentControl->VAddChildControl(m_pInfoLabelControl);
	m_pInfoLabelControl->VSetPosition(cVector3(0.f, 0.f, 0.f));

	IBaseControl * pWindowControl = IBaseControl::CreateWindowControl(WT_STANDARD, "Test\\window.png", false);
	m_pParentControl->VAddChildControl(pWindowControl);
	pWindowControl->VSetPosition(cVector3(300.f, 300.f, 0.f));
	pWindowControl->VSetSize(400, 400);

	IBaseControl * pLabelControl = IBaseControl::CreateLabelControl(17, 14, 20, false, DEFAULT_CHARSET, "Mistral", DT_LEFT, cColor::BLUE.GetColor(), "Label  ");
	pWindowControl->VAddChildControl(pLabelControl);
	pLabelControl->VSetPosition(cVector3(0.f, 40.f, 0.f));

	IBaseControl * pButtonControl = IBaseControl::CreateButtonControl("Test\\buttonDefault.png", "Test\\buttonPressed.png", "Button", 20, 10, 8, false, DEFAULT_CHARSET, "Vladimir Script", DT_VCENTER|DT_CENTER, cColor::WHITE.GetColor(), false);
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

	IBaseControl * pTextBoxControl = IBaseControl::CreateTextBoxControl("Test\\buttonDefault.png", 10, 10, 8, false, DEFAULT_CHARSET, "Arial", DT_VCENTER|DT_LEFT, cColor::BLACK.GetColor());
	pWindowControl->VAddChildControl(pTextBoxControl);
	pTextBoxControl->VSetSize(200, 30);
	pTextBoxControl->VSetPosition(cVector3(0.f, 200.f, 0.f));

	IBaseControl * pCheckBoxControl = IBaseControl::CreateCheckBoxControl("Test\\Checked.png", "Test\\Unchecked.png", "Check\nBox", 30, 30, 10, 20, 10, 8, false, DEFAULT_CHARSET, "Arial", DT_VCENTER|DT_CENTER, cColor::WHITE.GetColor());
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

void cGraphicsTestView::TestPointList()
{
	m_pInfoLabelControl = IBaseControl::CreateLabelControl(17, 14, 20, false, DEFAULT_CHARSET, "Arial", DT_LEFT, cColor::BLUE.GetColor(), "Testing Point List. Press 'c' to go to next test");
	m_pParentControl->VAddChildControl(m_pInfoLabelControl);
	m_pInfoLabelControl->VSetPosition(cVector3(0.f, 0.f, 0.f));

	m_vertexData = DEBUG_NEW cVertex[m_iVertexListCount];
	IRandomGenerator * pRandom = IRandomGenerator::CreateRandomGenerator();
	
	for(int count=0;count<m_iVertexListCount;count++)
	{
		m_vertexData[count].m_fX = pRandom->Random(m_pParentControl->VGetWidth());
		m_vertexData[count].m_fY = pRandom->Random(m_pParentControl->VGetHeight());
		m_vertexData[count].m_fZ = 1.0f;
		m_vertexData[count].m_fRHW = 1.0f;
		m_vertexData[count].m_dwColour =D3DCOLOR_XRGB (pRandom->Random(255), pRandom->Random(255), pRandom->Random(255));
	}
	SAFE_DELETE(pRandom);
}

// ***************************************************************
void cGraphicsTestView::TestLineList()
{
	m_pInfoLabelControl = IBaseControl::CreateLabelControl(17, 14, 20, false, DEFAULT_CHARSET, "Arial", DT_LEFT, cColor::BLUE.GetColor(), "Testing Line List. Press 'c' to go to next test");
	m_pParentControl->VAddChildControl(m_pInfoLabelControl);
	m_pInfoLabelControl->VSetPosition(cVector3(0.f, 0.f, 0.f));

	m_vertexData = DEBUG_NEW cVertex[m_iVertexListCount];
	IRandomGenerator * pRandom = IRandomGenerator::CreateRandomGenerator();

	for(int count=0;count<m_iVertexListCount;count++)
	{
		m_vertexData[count].m_fX = pRandom->Random(m_pParentControl->VGetWidth());
		m_vertexData[count].m_fY = pRandom->Random(m_pParentControl->VGetHeight());
		m_vertexData[count].m_fZ = 1.0f;
		m_vertexData[count].m_fRHW = 1.0f;
		m_vertexData[count].m_dwColour =D3DCOLOR_XRGB (pRandom->Random(255), pRandom->Random(255), pRandom->Random(255));
	}
	SAFE_DELETE(pRandom);
}

// ***************************************************************
void cGraphicsTestView::TestLineStrip()
{
	m_pInfoLabelControl = IBaseControl::CreateLabelControl(17, 14, 20, false, DEFAULT_CHARSET, "Arial", DT_LEFT, cColor::BLUE.GetColor(), "Testing Line Strip. Press 'c' to go to next test");
	m_pParentControl->VAddChildControl(m_pInfoLabelControl);
	m_pInfoLabelControl->VSetPosition(cVector3(0.f, 0.f, 0.f));

	m_vertexData = DEBUG_NEW cVertex[m_iVertexListCount];

	float count_f;
	float y;
	unsigned char red,green,blue;
	for(int count=0;count<m_iVertexListCount;count++)
	{
		count_f=(float)count;
		y = sinf(count_f/10.0f);
		
		m_vertexData[count].m_fX = count_f;
		m_vertexData[count].m_fY = y * (m_pParentControl->VGetHeight()/4.0f) + (m_pParentControl->VGetHeight()/2.0f);
		m_vertexData[count].m_fZ = 1.0f;
		m_vertexData[count].m_fRHW = 1.0f;
		blue= (char)ceil((count_f/m_pParentControl->VGetWidth()) * 200.0f) +55;
		green=(char)ceil(((m_pParentControl->VGetWidth() - count_f)/m_pParentControl->VGetWidth()) * 200.0f) +55;
		red=(char) ((fabsf(y)* 200.0f) + 55.0f);
		m_vertexData[count].m_dwColour =D3DCOLOR_XRGB (red, green, blue);
	}
}

// ***************************************************************
void cGraphicsTestView::TestTriangleList()
{
	m_pInfoLabelControl = IBaseControl::CreateLabelControl(17, 14, 20, false, DEFAULT_CHARSET, "Arial", DT_LEFT, cColor::RED.GetColor(), "Testing Triangle Strip. Press 'c' to go to next test");
	m_pParentControl->VAddChildControl(m_pInfoLabelControl);
	m_pInfoLabelControl->VSetPosition(cVector3(0.f, 0.f, 0.f));

	m_vertexData = DEBUG_NEW cVertex[12];

	m_vertexData[0] = cVertex(200, 200, 1, 1, cColor::RED.GetColor());
	m_vertexData[1] = cVertex(100, 100, 1, 1, cColor::BLUE.GetColor());
	m_vertexData[2] = cVertex(300, 100, 1, 1, cColor::GREEN.GetColor());
	m_vertexData[3] = cVertex(200, 200, 1, 1, cColor::RED.GetColor());
	m_vertexData[4] = cVertex(300, 100, 1, 1, cColor::GREEN.GetColor());
	m_vertexData[5] = cVertex(300, 300, 1, 1, cColor::YELLOW.GetColor());
	m_vertexData[6] = cVertex(200, 200, 1, 1, cColor::RED.GetColor());
	m_vertexData[7] = cVertex(300, 300, 1, 1, cColor::YELLOW.GetColor());
	m_vertexData[8] = cVertex(100, 300, 1, 1, cColor::VIOLET.GetColor());
	m_vertexData[9] = cVertex(200, 200, 1, 1, cColor::RED.GetColor());
	m_vertexData[10] = cVertex(100, 300, 1, 1, cColor::VIOLET.GetColor());
	m_vertexData[11] = cVertex(100, 100, 1, 1, cColor::BLUE.GetColor());
}

// ***************************************************************
void cGraphicsTestView::Cleanup()
{
	SAFE_DELETE_ARRAY(m_vertexData);
}