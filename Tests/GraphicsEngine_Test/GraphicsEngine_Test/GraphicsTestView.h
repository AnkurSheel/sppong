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
}

namespace Graphics
{
	struct stVertex;
	class IModel;
	class ICamera;
}

class cGraphicsTestView 
	: public GameBase::cHumanView
{
public:
	cGraphicsTestView();
	~cGraphicsTestView();
	void VOnCreateDevice(GameBase::IBaseApp * pGame, const HINSTANCE hInst, const HWND hWnd, int iClientWidth, int iClientHeight );
	bool VOnMsgProc( const Base::AppMsg & msg );	
	//void TestUIControls();
	//void TestPointList();
	//void TestLineList();
	//void TestLineStrip();
	//void TestTriangleList();
	//void TestVertexBuffer();
	void TestIndexBuffer();
	//void Finished();
	void TestFinished();
	void Cleanup();

private:
	void VRenderPrivate();
private:
	cGame	*					m_pGame;
	//Graphics::IBaseControl *	m_pInfoLabelControl;
	bool						m_bFinished;
	//Graphics::cVertex *			m_pVertexData;
	const int					m_iVertexListCount;
	Graphics::IModel *			m_pModel;
	Graphics::ICamera *			m_pCamera;
};
#endif // GraphicsTestView_h__
