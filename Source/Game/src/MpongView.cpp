// ***************************************************************
//  MpongView   version:  1.0   Ankur Sheel  date: 2011/05/02
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "MpongView.h"
#include "Sprite.hxx"
#include "DxBase.hxx"

using namespace Utilities;
using namespace Graphics;
using namespace GameBase;

cMPongView::cMPongView()
{
}

cMPongView::~cMPongView()
{
}

HRESULT cMPongView::OnResetDevice()
{
	HRESULT hr = cHumanView::OnResetDevice();
	if(SUCCEEDED(hr))
	{
		/*if (m_pGameApp)
		{
		m_pGameApp->OnResetDevice() ;
		}*/
	}
	return hr;
}

void cMPongView::OnLostDevice()
{
	cHumanView::OnLostDevice();
	/*if (m_pGameApp)
	{
	m_pGameApp->OnLostDevice();
	}*/
}
