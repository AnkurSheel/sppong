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
#include "FontManager.hxx"
#include "Sentence.hxx"
#include "ObjModelLoader.hxx"

using namespace Utilities;
using namespace Graphics;
using namespace GameBase;
using namespace Base;

// ***************************************************************
cGraphicsTestView::cGraphicsTestView()
: m_pGame(NULL)
, m_bFinished(false)
, m_iVertexListCount(1000)
, m_pModel(NULL)
{
}

// ***************************************************************
cGraphicsTestView::~cGraphicsTestView()
{
	Cleanup();
}

void cGraphicsTestView::VOnCreateDevice(IBaseApp * pGame, const HINSTANCE & hInst,
										const HWND & hWnd, const int iClientWidth, 
										const int iClientHeight)
{
	cHumanView::VOnCreateDevice(pGame, hInst, hWnd, iClientWidth, iClientHeight);
	m_pGame = dynamic_cast<cGame *>(pGame);

	stLabelControlDef def;
	def.pFont = IFontManager::GetInstance()->VGetFont("arial.fnt");
	def.textColor = cColor::GRAY;
	def.strText = "Press 'c' to start test";
	def.fTextHeight = 20;
	m_pInfoLabelControl = shared_ptr<IBaseControl>(IBaseControl::CreateLabelControl(def));
	m_pAppWindowControl->VAddChildControl(m_pInfoLabelControl);
	m_pInfoLabelControl->VSetPosition(cVector2(0.f, 0.f));
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
		case TEST_MODELCOLOR:
			if(m_pModel)
			{
				m_pModel->VSetRotation(cVector3(0.0f, 
					m_pModel->VGetRotation().m_dY + DegtoRad(0.1f), 0.0f));
				m_pModel->VRender(m_pCamera);
			}
			break;

		case TEST_MODELTEXTURE:
			if(m_pModel)
			{
				//m_pModel->VSetRotation(cVector3(0.0f, 
				//	m_pModel->VGetRotation().m_dY + DegtoRad(0.1f), 0.0f));
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

// ***************************************************************
void cGraphicsTestView::Finished()
{
	m_bFinished = true;

	if(m_pInfoLabelControl != NULL)
	{
		m_pInfoLabelControl->VSetText("Finished all Tests. Press 'c' to exit");
	}
}

// *************************************************************************
void cGraphicsTestView::TestModelColor()
{
	if(m_pInfoLabelControl != NULL)
	{
		m_pInfoLabelControl->VSetText("Testing Model with color. Press 'c' to go to next test");
	}

	Log_Write_L1(ILogger::LT_ERROR, "Testing Model with color");

	m_pCamera->VSetPosition(cVector3(0.0f, 0.0f, -20.0f));
	m_pModel = IModel::CreateModel();

	shared_ptr<IObjModelLoader> pObjModelLoader = shared_ptr<IObjModelLoader>(IObjModelLoader::GetObjModelLoader());
	pObjModelLoader->VLoadModelFromFile("resources//sphere.spdo", m_pModel);
	m_pModel->VSetPosition(cVector3(6.0f, 5.0f, 1.0f));
	m_pModel->VSetScale(cVector3(2.0f, 2.0f, 1.0f));

}

// ***************************************************************
void cGraphicsTestView::TestModelTexture()
{
	if(m_pInfoLabelControl != NULL)
	{
		m_pInfoLabelControl->VSetText("Testing Model with Texture. Press 'c' to go to next test");
	}

	Log_Write_L1(ILogger::LT_ERROR, "Testing Model with Texture");

	m_pCamera->VSetPosition(cVector3(0.0f, 0.0f, -20.0f));
	m_pModel = IModel::CreateModel();

	shared_ptr<IObjModelLoader> pObjModelLoader = shared_ptr<IObjModelLoader>(IObjModelLoader::GetObjModelLoader());
	pObjModelLoader->VLoadModelFromFile("resources//cube.spdo", m_pModel);
	m_pModel->VSetScale(cVector3(2.0f, 2.0f, 2.0f));
	m_pModel->VSetRotation(cVector3(0.7f, 0.0f, 0.7f));
}

// ***************************************************************
void cGraphicsTestView::TestSprite()
{
	if(m_pInfoLabelControl != NULL)
	{
		m_pInfoLabelControl->VSetText("Testing Sprite. Press 'c' to go to next test");
	}

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
	if(m_pInfoLabelControl != NULL)
	{
		m_pInfoLabelControl->VSetText("Testing Font. Press 'c' to go to next test");
	}

	Log_Write_L1(ILogger::LT_ERROR, "Testing Font");

	m_pCamera->VSetPosition(cVector3(0.0f, 0.0f, -20.0f));

	ISentence * pSentence = ISentence::CreateSentence();
	pSentence->VInitialize(IFontManager::GetInstance()->VGetFont("arial.fnt"), "Ankur is awesome", cColor::RED);
	pSentence->VSetPosition(cVector2(100.0f, 100.0f));
	m_vSentences.push_back(pSentence);
	pSentence = ISentence::CreateSentence();
	pSentence->VInitialize(IFontManager::GetInstance()->VGetFont("arial.fnt"), "Yes he is", cColor::VIOLET);
	pSentence->VSetPosition(cVector2(400.0f, 200.0f));
	m_vSentences.push_back(pSentence);
}

// ***************************************************************
void cGraphicsTestView::TestUIControls()
{
	if(m_pInfoLabelControl != NULL)
	{
		m_pInfoLabelControl->VSetText("Testing UI Controls. Press 'c' to go to next test");
	}

	stWindowControlDef wcDef;
	wcDef.wType = WT_STANDARD;
	wcDef.strBGImageFile = "Test\\window.png";
	wcDef.bAllowMovingControls = false;

	IBaseControl * pWindowControl = IBaseControl::CreateWindowControl(wcDef);
	m_pAppWindowControl->VAddChildControl(shared_ptr<IBaseControl>(pWindowControl));
	pWindowControl->VSetPosition(cVector2(300.f, 300.f));
	pWindowControl->VSetSize(cVector2(400, 400));

	stLabelControlDef labelDef;

	labelDef.pFont = IFontManager::GetInstance()->VGetFont("arial.fnt");
	labelDef.strBGImageFile = "Test\\ScrollBar_BG.png";
	labelDef.textColor = cColor::GREEN;
	labelDef.strText = "Label";
	labelDef.fTextHeight = 30;
	IBaseControl * pLabelControl = IBaseControl::CreateLabelControl(labelDef);
	pWindowControl->VAddChildControl(shared_ptr<IBaseControl>(pLabelControl));
	pLabelControl->VSetPosition(cVector2(0.f, 70.f));

	stButtonControlDef buttonDef;
	buttonDef.iWidth = 100;
	buttonDef.iHeight = 100;
	buttonDef.strDefaultImage = "Test\\buttonDefault.png";
	buttonDef.strPressedImage = "Test\\buttonPressed.png";
	buttonDef.labelControlDef.pFont = IFontManager::GetInstance()->VGetFont("arial.fnt");
	buttonDef.labelControlDef.strText = "Button";
	buttonDef.labelControlDef.textColor = cColor::ORANGE;
	buttonDef.labelControlDef.fTextHeight = 30;
	
	IBaseControl * pButtonControl = IBaseControl::CreateButtonControl(buttonDef);
	pWindowControl->VAddChildControl(shared_ptr<IBaseControl>(pButtonControl));
	pButtonControl->VSetPosition(cVector2(0.f, 130.f));
	function<void (bool)> btnCallback;
	btnCallback = bind(&cGame::ButtonPressed, m_pGame, _1);
	pButtonControl->VRegisterCallBack(btnCallback);

	stButtonControlDef buttonDef1;
	buttonDef1.strDefaultImage = "Test\\buttonDefault.png";
	buttonDef1.strPressedImage = "Test\\buttonPressed.png";
	buttonDef1.iWidth = 15;
	buttonDef1.iHeight = 30;
	IBaseControl * pButtonControl1 = IBaseControl::CreateButtonControl(buttonDef1);
	pWindowControl->VAddChildControl(shared_ptr<IBaseControl>(pButtonControl1));
	pButtonControl1->VSetPosition(cVector2(150.f, 90.f));
	function<void (bool)> btn1Callback;
	btn1Callback = bind(&cGame::Button1Pressed, m_pGame, _1);
	pButtonControl1->VRegisterCallBack(btn1Callback);
	
	stTextBoxControlDef textControlDef;
	textControlDef.strBGImage = "Test\\TextBox.png";
	textControlDef.pFont = IFontManager::GetInstance()->VGetFont("arial.fnt");
	textControlDef.fTextHeight = 30;
	textControlDef.textColor = cColor::VIOLET;
	textControlDef.strCaretImage = "Test\\caret.png";
	textControlDef.iCaretWidth = 3;
	textControlDef.fCaretUpdateTime =0.25f;

	IBaseControl * pTextBoxControl = IBaseControl::CreateTextBoxControl(textControlDef);
	pWindowControl->VAddChildControl(shared_ptr<IBaseControl>(pTextBoxControl));
	pTextBoxControl->VSetSize(cVector2(200, 45));
	pTextBoxControl->VSetPosition(cVector2(110.0f, 200.f));
	
	stCheckBoxControlDef checkboxControlDef;
	checkboxControlDef.buttonControlDef.strDefaultImage = "Test\\Unchecked.png";
	checkboxControlDef.buttonControlDef.strPressedImage = "Test\\Checked.png";
	checkboxControlDef.labelControlDef.strText = "CheckBox";
	checkboxControlDef.labelControlDef.pFont = IFontManager::GetInstance()->VGetFont("arial.fnt");
	checkboxControlDef.labelControlDef.fTextHeight = 20;
	checkboxControlDef.labelControlDef.textColor = cColor::WHITE;
	checkboxControlDef.buttonControlDef.iHeight= 50;
	checkboxControlDef.buttonControlDef.iWidth = 30;
	checkboxControlDef.iSpaceCaption = 10;

	IBaseControl * pCheckBoxControl = IBaseControl::CreateCheckBoxControl(checkboxControlDef);
	pWindowControl->VAddChildControl(shared_ptr<IBaseControl>(pCheckBoxControl));
	pCheckBoxControl->VSetPosition(cVector2(0.f, 250.f));
	function<void (bool)> checkBoxCallback;
	checkBoxCallback = bind(&cGame::CheckBoxPressed, m_pGame, _1);
	pCheckBoxControl->VRegisterCallBack(checkBoxCallback);

	stScrollBarControlDef vScrollBarDef;
	vScrollBarDef.strBGImage = "Test\\ScrollBar_BG.png";
	vScrollBarDef.iMinPos = 10;
	vScrollBarDef.iMaxPos = 50;
	vScrollBarDef.iInitialThumbPosition = 20;
	vScrollBarDef.thumbBtnDef.strDefaultImage= "Test\\ScrollBar_Thumb.png";
	vScrollBarDef.thumbBtnDef.strPressedImage = "Test\\ScrollBar_Thumb.png";
	vScrollBarDef.TopLeftArrowDef.strDefaultImage = "Test\\ScrollBar_Up.png";
	vScrollBarDef.TopLeftArrowDef.strPressedImage = "Test\\ScrollBar_Up.png";
	vScrollBarDef.BottomRightArrowDef.strDefaultImage = "Test\\ScrollBar_Down.png";
	vScrollBarDef.BottomRightArrowDef.strPressedImage = "Test\\ScrollBar_Down.png";
	
	IBaseControl * pVScrollBarControl = IBaseControl::CreateVScrollBarControl(vScrollBarDef);
	pWindowControl->VAddChildControl(shared_ptr<IBaseControl>(pVScrollBarControl));
	pVScrollBarControl->VSetPosition(cVector2(326.f, 56.f));
	pVScrollBarControl->VSetSize(cVector2(30, 300));	

	stScrollBarControlDef hScrollBarDef;
	hScrollBarDef.strBGImage = "Test\\ScrollBar_BG.png";
	hScrollBarDef.iMinPos = 0;
	hScrollBarDef.iMaxPos = 10;
	hScrollBarDef.thumbBtnDef.strDefaultImage= "Test\\ScrollBar_Thumb.png";
	hScrollBarDef.thumbBtnDef.strPressedImage = "Test\\ScrollBar_Thumb.png";
	hScrollBarDef.TopLeftArrowDef.strDefaultImage = "Test\\ScrollBar_Left.png";
	hScrollBarDef.TopLeftArrowDef.strPressedImage = "Test\\ScrollBar_Left.png";
	hScrollBarDef.BottomRightArrowDef.strDefaultImage = "Test\\ScrollBar_Right.png";
	hScrollBarDef.BottomRightArrowDef.strPressedImage = "Test\\ScrollBar_Right.png";

	IBaseControl * pHScrollBarControl = IBaseControl::CreateHScrollBarControl(hScrollBarDef);
	pWindowControl->VAddChildControl(shared_ptr<IBaseControl>(pHScrollBarControl));
	pHScrollBarControl->VSetPosition(cVector2(20.f, 330.f));
	pHScrollBarControl->VSetSize(cVector2(200, 30));
}
// ***************************************************************
void cGraphicsTestView::Cleanup()
{
	SAFE_DELETE(m_pModel);
	std::vector<ISentence*>::iterator iter;
	for (iter = m_vSentences.begin(); iter != m_vSentences.end(); iter++)
	{
		SAFE_DELETE(*iter)
	}
	m_vSentences.clear();
	SAFE_DELETE(m_pAppWindowControl);
	IFontManager::Destroy();
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
	m_pAppWindowControl->VRemoveAllChildren();
	if(m_pInfoLabelControl)
	{
		m_pAppWindowControl->VAddChildControl(m_pInfoLabelControl);
	}
}