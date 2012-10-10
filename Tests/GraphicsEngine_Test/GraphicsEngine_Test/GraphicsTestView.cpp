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
#include "Vector2.h"
#include "RandomGenerator.hxx"
#include "vertexstruct.h"
#include "Color.h"
#include "Model.hxx"
#include "Camera.hxx"
#include "Sprite.hxx"
#include "Font.hxx"
#include "Sentence.hxx"

using namespace Utilities;
using namespace Graphics;
using namespace GameBase;
using namespace Base;

// ***************************************************************
cGraphicsTestView::cGraphicsTestView()
: m_pGame(NULL)
//, m_pInfoLabelControl(NULL)
, m_bFinished(false)
//, m_pVertexData(NULL)
, m_iVertexListCount(1000)
, m_pModel(NULL)
{
}

// ***************************************************************
cGraphicsTestView::~cGraphicsTestView()
{
	Cleanup();
}

void cGraphicsTestView::VOnCreateDevice(IBaseApp * pGame, const HINSTANCE hInst,
										const HWND hWnd, int iClientWidth, 
										int iClientHeight)
{
	cHumanView::VOnCreateDevice(pGame, hInst, hWnd, iClientWidth, iClientHeight);
	m_pGame = dynamic_cast<cGame *>(pGame);

	/*m_pInfoLabelControl = IBaseControl::CreateLabelControl(17, 14, 20, false,
		DEFAULT_CHARSET, "Arial", DT_LEFT, cColor::BLUE.GetColor(), 
		"Press 'c' to start test");
	m_pParentControl->VAddChildControl(m_pInfoLabelControl);
	m_pInfoLabelControl->VSetPosition(cVector3(0.f, 0.f, 0.f));*/

}

// ***************************************************************
bool cGraphicsTestView::VOnMsgProc( const Base::AppMsg & msg )
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
					//m_pParentControl->VRemoveAllChildren();
					//m_pInfoLabelControl = NULL;
				}
				if(m_pGame)
					m_pGame->GotoNextTest();
				break;

			case 'w':
				//IDXBase::GetInstance()->VToggleRenderState();
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
		case TEST_TRIANGLE:
		case TEST_TEXTURETRIANGLE:
			if(m_pModel)
			{
				m_pModel->VRender(m_pCamera);
			}
			break;

		case TEST_SPRITE:
			if(m_pSprite)
			{
				m_pSprite->VRender(m_pCamera);
			}
			break;

		case TEST_FONT:
			std::vector<ISentence*>::const_iterator iter;
			for (iter = m_vSentences.begin(); iter != m_vSentences.end(); iter++)
			{
				(*iter)->VRender(m_pCamera);
			}
			break;
		}
	}
}

//void cGraphicsTestView::Finished()
//{
//	m_bFinished = true;
//	if(m_pInfoLabelControl != NULL)
//	{
//		m_pParentControl->VRemoveChildControl(m_pInfoLabelControl);
//		m_pInfoLabelControl = NULL;
//	}
//
//	m_pInfoLabelControl = IBaseControl::CreateLabelControl(17, 14, 20, false,
//		DEFAULT_CHARSET, "Arial", DT_LEFT, cColor::BLUE.GetColor(), 
//		"Finished all Tests. Press 'c' to exit");
//	m_pParentControl->VAddChildControl(m_pInfoLabelControl);
//	m_pInfoLabelControl->VSetPosition(cVector3(0.f, 0.f, 0.f));
//}
//

// ***************************************************************
void cGraphicsTestView::TestTriangle()
{
	//m_pInfoLabelControl = IBaseControl::CreateLabelControl(17, 14, 20, false,
	//	DEFAULT_CHARSET, "Arial", DT_LEFT, cColor::BLUE.GetColor(), 
	//	"Testing IndexBuffer. Press 'c' to go to next test");
	//m_pParentControl->VAddChildControl(m_pInfoLabelControl);
	//m_pInfoLabelControl->VSetPosition(cVector3(0.f, 0.f, 0.f));

	Log_Write_L1(ILogger::LT_ERROR, "Testing Traiangle");

	stVertex * pVertexData = DEBUG_NEW stVertex[7];

	pVertexData[0] = stVertex(-1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	pVertexData[1] = stVertex(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	pVertexData[2] = stVertex(1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	pVertexData[3] = stVertex(3.0f, 3.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);
	pVertexData[4] = stVertex(3.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	pVertexData[5] = stVertex(5.0f, 3.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	pVertexData[6] = stVertex(5.0f, 5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);

	unsigned long aIndices[] = {0,1,2,
								3,4,5,
								4,6,5};

	m_pCamera->VSetPosition(cVector3(0.0f, 0.0f, -20.0f));
	m_pModel = IModel::CreateModel();
	m_pModel->VOnInitialization(pVertexData, aIndices, 7, 9, 1);
	SAFE_DELETE_ARRAY(pVertexData);
}

// ***************************************************************
void cGraphicsTestView::TestTextureTriangle()
{
	//m_pInfoLabelControl = IBaseControl::CreateLabelControl(17, 14, 20, false,
	//	DEFAULT_CHARSET, "Arial", DT_LEFT, cColor::BLUE.GetColor(), 
	//	"Testing IndexBuffer. Press 'c' to go to next test");
	//m_pParentControl->VAddChildControl(m_pInfoLabelControl);
	//m_pInfoLabelControl->VSetPosition(cVector3(0.f, 0.f, 0.f));

	Log_Write_L1(ILogger::LT_ERROR, "Testing Texture Triangle");

	stTexVertex * pVertexData = DEBUG_NEW stTexVertex[7];

	pVertexData[0] = stTexVertex(-1.0f, -1.0f, 0.0f, 0.0f, 1.0f);
	pVertexData[1] = stTexVertex(0.0f, 1.0f, 0.0f, 0.5f, 0.0f);
	pVertexData[2] = stTexVertex(1.0f, -1.0f, 0.0f, 1.0f, 1.0f);
	pVertexData[3] = stTexVertex(3.0f, 3.0f, 0.0f, 0.0f, 1.0f);
	pVertexData[4] = stTexVertex(3.0f, 5.0f, 0.0f, 0.0f, 0.0f);
	pVertexData[5] = stTexVertex(5.0f, 3.0f, 0.0f, 1.0f, 1.0f);
	pVertexData[6] = stTexVertex(5.0f, 5.0f, 0.0f, 1.0f, 0.0f);

	unsigned long aIndices[] = {0,1,2,
		3,4,5,
		4,6,5};

	m_pCamera->VSetPosition(cVector3(0.0f, 0.0f, -15.0f));
	m_pModel = IModel::CreateModel();
	m_pModel->VOnInitialization(pVertexData, aIndices, 7, 9, 1, "Test\\seafloor.dds");
	SAFE_DELETE_ARRAY(pVertexData);
}

// ***************************************************************
void cGraphicsTestView::TestSprite()
{
	//m_pInfoLabelControl = IBaseControl::CreateLabelControl(17, 14, 20, false,
	//	DEFAULT_CHARSET, "Arial", DT_LEFT, cColor::BLUE.GetColor(), 
	//	"Testing IndexBuffer. Press 'c' to go to next test");
	//m_pParentControl->VAddChildControl(m_pInfoLabelControl);
	//m_pInfoLabelControl->VSetPosition(cVector3(0.f, 0.f, 0.f));

	Log_Write_L1(ILogger::LT_ERROR, "Testing Sprite");

	m_pCamera->VSetPosition(cVector3(0.0f, 0.0f, -20.0f));
	m_pSprite = ISprite::CreateSprite();
	m_pSprite->VInitialize("Test\\seafloor.dds");
	m_pSprite->VSetPosition(cVector2(100.0f, 100.0f));
	m_pSprite->VSetSize(cVector2(256, 256.0f));
}

// ***************************************************************
void cGraphicsTestView::TestFont()
{
	//m_pInfoLabelControl = IBaseControl::CreateLabelControl(17, 14, 20, false,
	//	DEFAULT_CHARSET, "Arial", DT_LEFT, cColor::BLUE.GetColor(), 
	//	"Testing IndexBuffer. Press 'c' to go to next test");
	//m_pParentControl->VAddChildControl(m_pInfoLabelControl);
	//m_pInfoLabelControl->VSetPosition(cVector3(0.f, 0.f, 0.f));

	Log_Write_L1(ILogger::LT_ERROR, "Testing Font");

	m_pCamera->VSetPosition(cVector3(0.0f, 0.0f, -20.0f));

	m_pFont = IMyFont::CreateMyFont();
	m_pFont->VInitialize("Font\\", "licorice.fnt");
	ISentence * pSentence = ISentence::CreateSentence();
	pSentence->VInitialize(m_pFont, "Ankur is awesome", cColor::RED);
	pSentence->VSetPosition(cVector2(100.0f, 100.0f));
	m_vSentences.push_back(pSentence);
	pSentence = ISentence::CreateSentence();
	pSentence->VInitialize(m_pFont, "Yes he is", cColor::VIOLET);
	pSentence->VSetPosition(cVector2(400.0f, 200.0f));
	m_vSentences.push_back(pSentence);
}

// ***************************************************************
void cGraphicsTestView::TestUIControls()
{
	//	m_pInfoLabelControl = IBaseControl::CreateLabelControl(17, 14, 20, false,
	//		DEFAULT_CHARSET, "Arial", DT_LEFT, cColor::BLUE.GetColor(), 
	//		"Testing UI Controls. Press 'c' to go to next test");
	//	m_pParentControl->VAddChildControl(m_pInfoLabelControl);
	//	m_pInfoLabelControl->VSetPosition(cVector3(0.f, 0.f, 0.f));
	//
	IBaseControl * pWindowControl = IBaseControl::CreateWindowControl(WT_STANDARD, 
		"Test\\window.png", false);
	m_pAppWindowControl->VAddChildControl(pWindowControl);
	pWindowControl->VSetPosition(cVector2(300.f, 300.f));
	pWindowControl->VSetSize(cVector2(400, 400));
	//
	//	IBaseControl * pLabelControl = IBaseControl::CreateLabelControl(17, 14, 
	//		20, false, DEFAULT_CHARSET, "Mistral", DT_LEFT, cColor::BLUE.GetColor(),
	//		"Label  ");
	//	pWindowControl->VAddChildControl(pLabelControl);
	//	pLabelControl->VSetPosition(cVector3(0.f, 40.f, 0.f));
	//
	//	IBaseControl * pButtonControl = IBaseControl::CreateButtonControl("Test\\buttonDefault.png",
	//		"Test\\buttonPressed.png", "Button", 20, 10, 8, false, DEFAULT_CHARSET,
	//		"Vladimir Script", DT_VCENTER|DT_CENTER, cColor::WHITE.GetColor(), false);
	//	pWindowControl->VAddChildControl(pButtonControl);
	//	pButtonControl->VSetSize(100, 100);
	//	pButtonControl->VSetPosition(cVector3(0.f, 90.f, 0.f));
	//	function<void (bool)> btnCallback;
	//	btnCallback = bind(&cGame::ButtonPressed, m_pGame, _1);
	//	pButtonControl->VRegisterCallBack(btnCallback);
	//
	//	IBaseControl * pButtonControl1 = IBaseControl::CreateButtonControl("Test\\buttonDefault.png",
	//		"Test\\buttonPressed.png");
	//	pWindowControl->VAddChildControl(pButtonControl1);
	//	pButtonControl1->VSetSize(30, 30);
	//	pButtonControl1->VSetPosition(cVector3(150.f, 90.f, 0.f));
	//	function<void (bool)> btn1Callback;
	//	btn1Callback = bind(&cGame::Button1Pressed, m_pGame, _1);
	//	pButtonControl1->VRegisterCallBack(btn1Callback);
	//
	//	IBaseControl * pTextBoxControl = IBaseControl::CreateTextBoxControl("Test\\buttonDefault.png",
	//		10, 10, 8, false, DEFAULT_CHARSET, "Arial", DT_VCENTER|DT_LEFT, 
	//		cColor::BLACK.GetColor());
	//	pWindowControl->VAddChildControl(pTextBoxControl);
	//	pTextBoxControl->VSetSize(200, 30);
	//	pTextBoxControl->VSetPosition(cVector3(0.f, 200.f, 0.f));
	//
	//	IBaseControl * pCheckBoxControl = IBaseControl::CreateCheckBoxControl("Test\\Checked.png",
	//		"Test\\Unchecked.png", "Check\nBox", 30, 30, 10, 20, 10, 8, false, 
	//		DEFAULT_CHARSET, "Arial", DT_VCENTER|DT_CENTER, 
	//		cColor::WHITE.GetColor());
	//	pWindowControl->VAddChildControl(pCheckBoxControl);
	//	pCheckBoxControl->VSetPosition(cVector3(0.f, 250.f, 0.f));
	//	function<void (bool)> checkBoxCallback;
	//	checkBoxCallback = bind(&cGame::CheckBoxPressed, m_pGame, _1);
	//	pCheckBoxControl->VRegisterCallBack(checkBoxCallback);
	//
	//	IBaseControl * pVScrollBarControl = IBaseControl::CreateVScrollBarControl("Test\\ScrollBar_BG.png",
	//		"Test\\ScrollBar_Thumb.png", "Test\\ScrollBar_Thumb.png", "Test\\ScrollBar_Up.png", 
	//		"Test\\ScrollBar_Up.png", "Test\\ScrollBar_Down.png","Test\\ScrollBar_Down.png",
	//		0, 50);
	//	pWindowControl->VAddChildControl(pVScrollBarControl);
	//	pVScrollBarControl->VSetPosition(cVector3(300.f, 0.f, 0.f));
	//	pVScrollBarControl->VSetSize(30, 300);	
	//
	//	IBaseControl * pHScrollBarControl = IBaseControl::CreateHScrollBarControl("Test\\ScrollBar_BG.png",
	//		"Test\\ScrollBar_Thumb.png", "Test\\ScrollBar_Thumb.png", "Test\\ScrollBar_Left.png", 
	//		"Test\\ScrollBar_Left.png", "Test\\ScrollBar_Right.png","Test\\ScrollBar_Right.png",
	//		0, 50);
	//	pWindowControl->VAddChildControl(pHScrollBarControl);
	//	pHScrollBarControl->VSetPosition(cVector3(0.f, 300.f, 0.f));
	//	pHScrollBarControl->VSetSize(300, 30);	
}
// ***************************************************************
void cGraphicsTestView::Cleanup()
{
//	SAFE_DELETE_ARRAY(m_pVertexData);
	SAFE_DELETE(m_pModel);
	std::vector<ISentence*>::iterator iter;
	for (iter = m_vSentences.begin(); iter != m_vSentences.end(); iter++)
	{
		SAFE_DELETE(*iter)
	}
	m_vSentences.clear();
}

// ***************************************************************
void cGraphicsTestView::TestFinished()
{
	SAFE_DELETE(m_pModel);
	std::vector<ISentence*>::iterator iter;
	for (iter = m_vSentences.begin(); iter != m_vSentences.end(); iter++)
	{
		SAFE_DELETE(*iter)
	}
	m_vSentences.clear();
}
