// *****************************************************************************
//  GraphicsTestView   version:  1.0   Ankur Sheel  date: 2011/08/31
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "GraphicsTestView.h"
#include "Game.h"
#include "BaseControl.hxx"
#include "Camera.hxx"
#include "Sprite.hxx"
#include "Sentence.hxx"
#include "GameElement.h"

using namespace Utilities;
using namespace Graphics;
using namespace GameBase;
using namespace Base;

// *****************************************************************************
cGraphicsTestView::cGraphicsTestView()
: m_pGame(NULL)
, m_bFinished(false)
, m_iVertexListCount(1000)
, m_pGameElement(NULL)
{
}

// *****************************************************************************
cGraphicsTestView::~cGraphicsTestView()
{
	Cleanup();
}

void cGraphicsTestView::VOnCreateDevice(IBaseApp * pGame, const HINSTANCE & hInst,
										const HWND & hWnd)
{
	cHumanView::VOnCreateDevice(pGame, hInst, hWnd);
	m_pGame = dynamic_cast<cGame *>(pGame);

	cLabelControlDef def;
	def.strFont= "arial";
	def.textColor = cColor::GRAY;
	def.strText = "Press 'c' to start test";
	def.fTextHeight = 20;
	m_pInfoLabelControl = shared_ptr<IBaseControl>(IBaseControl::CreateLabelControl(def));
	m_pAppWindowControl->VAddChildControl(m_pInfoLabelControl);
	m_pInfoLabelControl->VSetPosition(cVector2(0.f, 0.f));
}

// *****************************************************************************
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

// *****************************************************************************
void cGraphicsTestView::VRenderPrivate()
{
	cHumanView::VRenderPrivate();

	if(m_pGame)
	{
		switch(m_pGame->GetCurrentTest())
		{
		case TEST_MODELCOLOR:
			if(m_pGameElement)
			{
				m_pGameElement->SetRotation(cVector3(0.0f, 
					m_pGameElement->GetRotation().y + DegtoRad(0.1f), 0.0f));
				m_pGameElement->Render(m_pCamera);
			}
			break;

		case TEST_MODELTEXTURE:
			if(m_pGameElement)
			{
				//m_pModel->VSetRotation(cVector3(0.0f, 
				//	m_pModel->VGetRotation().m_dY + DegtoRad(0.1f), 0.0f));
				m_pGameElement->Render(m_pCamera);
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

// *****************************************************************************
void cGraphicsTestView::Finished()
{
	m_bFinished = true;

	if(m_pInfoLabelControl != NULL)
	{
		m_pInfoLabelControl->VSetText("Finished all Tests. Press 'c' to exit");
	}
}

// ***************************************************************************************
void cGraphicsTestView::TestModelColor()
{
	if(m_pInfoLabelControl != NULL)
	{
		m_pInfoLabelControl->VSetText("Testing Model with color. Press 'c' to go to next test");
	}

	Log_Write_L1(ILogger::LT_ERROR, "Testing Model with color");

	m_pCamera->VSetPosition(cVector3(0.0f, 0.0f, -20.0f));
	
	m_pGameElement = DEBUG_NEW cGameElement();
	
	cGameElementDef def;
	def.strModelName = "sphere";
	def.vPosition = cVector3(6.0f, 5.0f, 1.0f);
	def.vScale = cVector3(2.0f, 2.0f, 1.0f);
	m_pGameElement->VInitialize(def);
}

// *****************************************************************************
void cGraphicsTestView::TestModelTexture()
{
	if(m_pInfoLabelControl != NULL)
	{
		m_pInfoLabelControl->VSetText("Testing Model with Texture. Press 'c' to go to next test");
	}

	Log_Write_L1(ILogger::LT_ERROR, "Testing Model with Texture");

	m_pCamera->VSetPosition(cVector3(0.0f, 0.0f, -20.0f));

	m_pGameElement = DEBUG_NEW cGameElement();

	cGameElementDef def;
	def.strModelName = "cube";
	def.vPosition = cVector3(2.0f, 2.0f, 2.0f);
	def.vRotation = cVector3(0.7f, 0.0f, 0.7f);
	m_pGameElement->VInitialize(def);
}

// *****************************************************************************
void cGraphicsTestView::TestSprite()
{
	if(m_pInfoLabelControl != NULL)
	{
		m_pInfoLabelControl->VSetText("Testing Sprite. Press 'c' to go to next test");
	}

	Log_Write_L1(ILogger::LT_ERROR, "Testing Sprite");

	m_pCamera->VSetPosition(cVector3(0.0f, 0.0f, -20.0f));
	m_pCamera->VSetRotation(cVector3(45.0f, 0.0f, 0));
	m_pSprite = ISprite::CreateSprite();
	m_pSprite->VInitialize("seafloor.dds");
	m_pSprite->VSetPosition(cVector2(100.0f, 100.0f));
	m_pSprite->VSetSize(cVector2(256, 256.0f));
}

// *****************************************************************************
void cGraphicsTestView::TestFont()
{
	if(m_pInfoLabelControl != NULL)
	{
		m_pInfoLabelControl->VSetText("Testing Font. Press 'c' to go to next test");
	}

	Log_Write_L1(ILogger::LT_ERROR, "Testing Font");

	m_pCamera->VSetPosition(cVector3(0.0f, 0.0f, -20.0f));

	ISentence * pSentence = ISentence::CreateSentence();
	pSentence->VInitialize("arial", "Ankur is awesome", cColor::RED);
	pSentence->VSetPosition(cVector2(100.0f, 100.0f));
	m_vSentences.push_back(pSentence);
	pSentence = ISentence::CreateSentence();
	pSentence->VInitialize("arial", "Yes he is", cColor::VIOLET);
	pSentence->VSetPosition(cVector2(400.0f, 200.0f));
	m_vSentences.push_back(pSentence);
}

// *****************************************************************************
void cGraphicsTestView::TestUIControls()
{
	if(m_pInfoLabelControl != NULL)
	{
		m_pInfoLabelControl->VSetText("Testing UI Controls. Press 'c' to go to next test");
	}

	cWindowControlDef wcDef;
	wcDef.wType = cWindowControlDef::WT_STANDARD;
	wcDef.strControlName = "TestWindow";
	wcDef.strBGImageFile = "window.png";
	wcDef.bAllowMovingControls = false;
	wcDef.vPosition =  cVector2(300.f, 200.f);
	wcDef.vSize = cVector2(400, 400);
	IBaseControl * pWindowControl = IBaseControl::CreateWindowControl(wcDef);
	m_pAppWindowControl->VAddChildControl(shared_ptr<IBaseControl>(pWindowControl));

	cLabelControlDef labelDef;
	labelDef.strFont= "arial";
	labelDef.strBGImageFile = "ScrollBar_BG.png";
	labelDef.textColor = cColor::GREEN;
	labelDef.strText = "Label";
	labelDef.fTextHeight = 30;
	labelDef.vPosition = cVector2(0.f, 70.f);
	IBaseControl * pLabelControl = IBaseControl::CreateLabelControl(labelDef);
	pWindowControl->VAddChildControl(shared_ptr<IBaseControl>(pLabelControl));

	cButtonControlDef buttonDef;
	buttonDef.vSize = cVector2(100, 100);
	buttonDef.vPosition = cVector2(0.f, 130.f);
	buttonDef.strDefaultImage = "buttonDefault.png";
	buttonDef.strPressedImage = "buttonPressed.png";
	buttonDef.labelControlDef.strFont= "arial";
	buttonDef.labelControlDef.strText = "Button";
	buttonDef.labelControlDef.textColor = cColor::ORANGE;
	buttonDef.labelControlDef.fTextHeight = 30;
	
	IBaseControl * pButtonControl = IBaseControl::CreateButtonControl(buttonDef);
	pWindowControl->VAddChildControl(shared_ptr<IBaseControl>(pButtonControl));
	UIEventCallBackFn btnCallback;
	btnCallback = bind(&cGame::ButtonPressed, m_pGame, _1);
	pButtonControl->VRegisterCallBack(UIET_BTNPRESSED, btnCallback);

	cButtonControlDef buttonDef1;
	buttonDef1.strDefaultImage = "buttonDefault.png";
	buttonDef1.strPressedImage = "buttonPressed.png";
	buttonDef1.vSize = cVector2(15, 30);
	buttonDef1.vPosition = cVector2(150.f, 90.f);
	IBaseControl * pButtonControl1 = IBaseControl::CreateButtonControl(buttonDef1);
	pWindowControl->VAddChildControl(shared_ptr<IBaseControl>(pButtonControl1));
	UIEventCallBackFn btn1Callback;
	btn1Callback = bind(&cGame::Button1Released, m_pGame, _1);
	pButtonControl1->VRegisterCallBack(UIET_BTNRELEASED, btn1Callback);
	
	cTextBoxControlDef textControlDef;
	textControlDef.strBGImage = "TextBox.png";
	textControlDef.strFont = "arial";
	textControlDef.fTextHeight = 30;
	textControlDef.textColor = cColor::VIOLET;
	textControlDef.strCaretImage = "caret.png";
	textControlDef.iCaretWidth = 3;
	textControlDef.fCaretUpdateTime =0.25f;
	textControlDef.vSize = cVector2(200, 45);
	textControlDef.vPosition = cVector2(110.0f, 200.f);
	IBaseControl * pTextBoxControl = IBaseControl::CreateTextBoxControl(textControlDef);
	pWindowControl->VAddChildControl(shared_ptr<IBaseControl>(pTextBoxControl));
	
	cCheckBoxControlDef checkboxControlDef;
	checkboxControlDef.buttonControlDef.strDefaultImage = "Unchecked.png";
	checkboxControlDef.buttonControlDef.strPressedImage = "Checked.png";
	checkboxControlDef.labelControlDef.strText = "CheckBox";
	checkboxControlDef.labelControlDef.strFont= "arial";
	checkboxControlDef.labelControlDef.fTextHeight = 20;
	checkboxControlDef.labelControlDef.textColor = cColor::WHITE;
	checkboxControlDef.buttonControlDef.vSize = cVector2(50, 30);
	checkboxControlDef.iSpaceCaption = 10;
	checkboxControlDef.vPosition = cVector2(0.f, 250.f);

	IBaseControl * pCheckBoxControl = IBaseControl::CreateCheckBoxControl(checkboxControlDef);
	pWindowControl->VAddChildControl(shared_ptr<IBaseControl>(pCheckBoxControl));
	UIEventCallBackFn checkBoxCallback;
	checkBoxCallback = bind(&cGame::CheckBoxPressed, m_pGame, _1);
	pCheckBoxControl->VRegisterCallBack(UIET_BTNRELEASED, checkBoxCallback);

	cScrollBarControlDef vScrollBarDef;
	vScrollBarDef.strBGImage = "ScrollBar_BG.png";
	vScrollBarDef.iMinPos = 10;
	vScrollBarDef.iMaxPos = 50;
	vScrollBarDef.iInitialThumbPosition = 20;
	vScrollBarDef.thumbBtnDef.strDefaultImage= "ScrollBar_Thumb.png";
	vScrollBarDef.thumbBtnDef.strPressedImage = "ScrollBar_Thumb.png";
	vScrollBarDef.TopLeftArrowDef.strDefaultImage = "ScrollBar_Up.png";
	vScrollBarDef.TopLeftArrowDef.strPressedImage = "ScrollBar_Up.png";
	vScrollBarDef.BottomRightArrowDef.strDefaultImage = "ScrollBar_Down.png";
	vScrollBarDef.BottomRightArrowDef.strPressedImage = "ScrollBar_Down.png";
	vScrollBarDef.vPosition = cVector2(326.f, 56.f);
	vScrollBarDef.vSize = cVector2(30, 300);
	IBaseControl * pVScrollBarControl = IBaseControl::CreateVScrollBarControl(vScrollBarDef);
	pWindowControl->VAddChildControl(shared_ptr<IBaseControl>(pVScrollBarControl));

	cScrollBarControlDef hScrollBarDef;
	hScrollBarDef.strBGImage = "ScrollBar_BG.png";
	hScrollBarDef.iMinPos = 0;
	hScrollBarDef.iMaxPos = 10;
	hScrollBarDef.thumbBtnDef.strDefaultImage= "ScrollBar_Thumb.png";
	hScrollBarDef.thumbBtnDef.strPressedImage = "ScrollBar_Thumb.png";
	hScrollBarDef.TopLeftArrowDef.strDefaultImage = "ScrollBar_Left.png";
	hScrollBarDef.TopLeftArrowDef.strPressedImage = "ScrollBar_Left.png";
	hScrollBarDef.BottomRightArrowDef.strDefaultImage = "ScrollBar_Right.png";
	hScrollBarDef.BottomRightArrowDef.strPressedImage = "ScrollBar_Right.png";
	hScrollBarDef.vPosition = cVector2(20.f, 330.f);
	hScrollBarDef.vSize = cVector2(200, 30);

	IBaseControl * pHScrollBarControl = IBaseControl::CreateHScrollBarControl(hScrollBarDef);
	pWindowControl->VAddChildControl(shared_ptr<IBaseControl>(pHScrollBarControl));
}
// *****************************************************************************
void cGraphicsTestView::Cleanup()
{
	SAFE_DELETE(m_pGameElement);

	std::vector<ISentence*>::iterator iter;
	for (iter = m_vSentences.begin(); iter != m_vSentences.end(); iter++)
	{
		SAFE_DELETE(*iter)
	}
	m_vSentences.clear();
	SAFE_DELETE(m_pAppWindowControl);
}

// *****************************************************************************
void cGraphicsTestView::TestFinished()
{
	SAFE_DELETE(m_pGameElement);

	std::vector<ISentence*>::iterator iter;
	for (iter = m_vSentences.begin(); iter != m_vSentences.end(); iter++)
	{
		SAFE_DELETE(*iter)
	}
	m_vSentences.clear();
	m_pAppWindowControl->VRemoveChildControl("TestWindow");
	m_pCamera->VSetRotation(cVector3::Zero());

}