// ***************************************************************
//  GraphicsTestView   version:  1.0   Ankur Sheel  date: 2012/08/31
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef GraphicsTestView_h__
#define GraphicsTestView_h__

#include "HumanView.h"

class cGame;

namespace GameBase
{
	class IBaseApp;
	class cGameElement;
}

namespace Graphics
{
	struct stVertex;
	class IModel;
	class ISprite;
	class ISentence;
}

class cGraphicsTestView 
	: public GameBase::cHumanView
{
public:
	cGraphicsTestView();
	~cGraphicsTestView();
	void VOnCreateDevice(GameBase::IBaseApp * pGame, const HINSTANCE & hInst,
		const HWND & hWnd);
	bool VOnMsgProc( const Base::AppMsg & msg );	
	void TestModelColor();
	void TestModelTexture();
	void TestSprite();
	void TestFont();
	void TestUIControls();
	void Finished();
	void TestFinished();
	void Cleanup();

private:
	void VRenderPrivate();

private:
	cGame	*							m_pGame;
	shared_ptr<Graphics::IBaseControl>	m_pInfoLabelControl;
	bool								m_bFinished;
	const int							m_iVertexListCount;
	GameBase::cGameElement *			m_pGameElement;
	shared_ptr<Graphics::ISprite>		m_pSprite;
	std::vector<Graphics::ISentence *>	m_vSentences;
};
#endif // GraphicsTestView_h__
